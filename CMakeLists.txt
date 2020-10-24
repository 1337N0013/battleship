cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_SOURCE_DIR "src")

set(PROJECT_SOURCE_DIR "..")
set(INCLUDE_DIRS "lib/SFML-2.5.1/include")
set(SFML_DIR "lib/SFML-2.5.1/lib/cmake/SFML")

project(battleship)

add_executable(
    battleship
    ${CMAKE_SOURCE_DIR}/main.cpp
    ${CMAKE_SOURCE_DIR}/Board.cpp
    ${CMAKE_SOURCE_DIR}/BoardCell.cpp
    ${CMAKE_SOURCE_DIR}/Button.cpp
    ${CMAKE_SOURCE_DIR}/Command.cpp
    ${CMAKE_SOURCE_DIR}/CreditsScene.cpp
    ${CMAKE_SOURCE_DIR}/Engine.cpp
    ${CMAKE_SOURCE_DIR}/GameScene.cpp
    ${CMAKE_SOURCE_DIR}/GameSettings.cpp
    ${CMAKE_SOURCE_DIR}/MainMenuScene.cpp
    ${CMAKE_SOURCE_DIR}/PauseScene.cpp
    ${CMAKE_SOURCE_DIR}/Scene.cpp
    ${CMAKE_SOURCE_DIR}/SceneStack.cpp
    ${CMAKE_SOURCE_DIR}/SettingsScene.cpp
)

set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML CONFIG COMPONENTS audio graphics window system)
if (SFML_FOUND)
    include_directories(${INCLUDE_DIRS})
    target_link_libraries(battleship sfml-audio sfml-graphics sfml-window sfml-system)

    # Add `res/` folder for fonts, audio.
    add_custom_command(
        TARGET battleship POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/res"
        "$<TARGET_FILE_DIR:battleship>/res"
    )

    # Add openal32.dll for Windows
    if (WIN32)
        add_custom_command(
            TARGET battleship POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${PROJECT_SOURCE_DIR}/lib/SFML-2.5.1/bin/openal32.dll"
            $<TARGET_FILE_DIR:battleship>
        )
    endif (WIN32)
else (SFML_FOUND)
    message(WARNING "SFML library not found in `lib/`")
endif (SFML_FOUND)
