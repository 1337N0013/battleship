CPPFLAGS = -std=c++17 -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio

bin/main: obj/main.o obj/Engine.o obj/Button.o obj/MainMenuScene.o
	g++ $(CPPFLAGS) -o bin/main obj/main.o obj/Engine.o obj/Button.o obj/MainMenuScene.o

obj/main.o: src/main.cpp
	g++ $(CPPFLAGS) -o obj/main.o -c src/main.cpp

obj/Engine.o: src/Engine.cpp src/Engine.h
	g++ $(CPPFLAGS) -o obj/Engine.o -c src/Engine.cpp

obj/MainMenuScene.o: src/MainMenuScene.cpp src/MainMenuScene.h
	g++ $(CPPFLAGS) -o obj/MainMenuScene.o -c src/MainMenuScene.cpp

obj/Button.o: src/Button.cpp src/Button.h
	g++ $(CPPFLAGS) -o obj/Button.o -c src/Button.cpp

clean:
	rm obj/*.o bin/main