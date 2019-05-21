CC = g++
CPP_PREFLAGS = -std=c++17
LINK_FLAGS = -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system

bin/main: obj/main.o obj/Engine.o obj/Scene.o obj/SceneStack.o obj/Command.o obj/GameSettings.o obj/Button.o obj/MainMenuScene.o obj/GameScene.o obj/SettingsScene.o obj/PauseScene.o obj/Board.o obj/BoardCell.o
	$(CC) $(CPP_PREFLAGS) -o bin/main obj/main.o obj/Engine.o obj/Scene.o obj/SceneStack.o obj/Command.o obj/GameSettings.o obj/Button.o obj/MainMenuScene.o obj/GameScene.o obj/SettingsScene.o obj/PauseScene.o obj/Board.o obj/BoardCell.o $(LINK_FLAGS)

obj/main.o: src/main.cpp
	$(CC) $(CPP_PREFLAGS) -o obj/main.o -c src/main.cpp $(LINK_FLAGS)

obj/Engine.o: src/Engine.cpp src/Engine.h
	$(CC) $(CPP_PREFLAGS) -o obj/Engine.o -c src/Engine.cpp $(LINK_FLAGS)

obj/Scene.o: src/Scene.cpp src/Scene.h
	$(CC) $(CPP_PREFLAGS) -o obj/Scene.o -c src/Scene.cpp $(CCPPFLAGS)

obj/SceneStack.o: src/SceneStack.cpp src/SceneStack.h
	$(CC) $(CPP_PREFLAGS) -o obj/SceneStack.o -c src/SceneStack.cpp $(LINK_FLAGS)

obj/Command.o: src/Command.cpp src/Command.h
	$(CC) $(CPP_PREFLAGS) -o obj/Command.o -c src/Command.cpp $(LINK_FLAGS)

obj/GameSettings.o: src/GameSettings.cpp src/GameSettings.h
	$(CC) $(CPP_PREFLAGS) -o obj/GameSettings.o -c src/GameSettings.cpp $(LINK_FLAGS)

obj/MainMenuScene.o: src/MainMenuScene.cpp src/MainMenuScene.h
	$(CC) $(CPP_PREFLAGS) -o obj/MainMenuScene.o -c src/MainMenuScene.cpp $(LINK_FLAGS)

obj/GameScene.o: src/GameScene.cpp src/GameScene.h
	$(CC) $(CPP_PREFLAGS) -o obj/GameScene.o -c src/GameScene.cpp $(LINK_FLAGS)

obj/SettingsScene.o: src/SettingsScene.cpp src/SettingsScene.h
	$(CC) $(CPP_PREFLAGS) -o obj/SettingsScene.o -c src/SettingsScene.cpp $(LINK_FLAGS)

obj/PauseScene.o: src/PauseScene.cpp src/PauseScene.h
	$(CC) $(CPP_PREFLAGS) -o obj/PauseScene.o -c src/PauseScene.cpp $(LINK_FLAGS)

obj/Button.o: src/Button.cpp src/Button.h
	$(CC) $(CPP_PREFLAGS) -o obj/Button.o -c src/Button.cpp $(LINK_FLAGS)

obj/Board.o: src/Board.cpp src/Board.h
	$(CC) $(CPP_PREFLAGS) -o obj/Board.o -c src/Board.cpp $(LINK_FLAGS)

obj/BoardCell.o: src/BoardCell.cpp src/BoardCell.h
	$(CC) $(CPP_PREFLAGS) -o obj/BoardCell.o -c src/BoardCell.cpp $(LINK_FLAGS)

clean:
	rm obj/*.o bin/main