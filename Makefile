CC = g++
CPP_PREFLAGS = -std=c++17
LINK_FLAGS = -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system

bin/main: obj/main.o obj/Engine.o obj/Scene.o obj/SceneStack.o obj/Command.o obj/Button.o obj/MainMenuScene.o
	$(CC) $(CPP_PREFLAGS) -o bin/main obj/main.o obj/Engine.o obj/Scene.o obj/SceneStack.o obj/Command.o obj/Button.o obj/MainMenuScene.o $(LINK_FLAGS)

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

obj/MainMenuScene.o: src/MainMenuScene.cpp src/MainMenuScene.h
	$(CC) $(CPP_PREFLAGS) -o obj/MainMenuScene.o -c src/MainMenuScene.cpp $(LINK_FLAGS)

obj/Button.o: src/Button.cpp src/Button.h
	$(CC) $(CPP_PREFLAGS) -o obj/Button.o -c src/Button.cpp $(LINK_FLAGS)

clean:
	rm obj/*.o bin/main