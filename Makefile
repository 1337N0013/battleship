CPPFLAGS = -std=c++17 -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system

bin/main: obj/main.o obj/Engine.o obj/Button.o obj/MainMenuScene.o
	g++ -o bin/main obj/main.o obj/Engine.o obj/Button.o obj/MainMenuScene.o $(CPPFLAGS)

obj/main.o: src/main.cpp
	g++ -o obj/main.o -c src/main.cpp $(CPPFLAGS)

obj/Engine.o: src/Engine.cpp src/Engine.h
	g++ -o obj/Engine.o -c src/Engine.cpp $(CPPFLAGS)

obj/MainMenuScene.o: src/MainMenuScene.cpp src/MainMenuScene.h
	g++ -o obj/MainMenuScene.o -c src/MainMenuScene.cpp $(CPPFLAGS)

obj/Button.o: src/Button.cpp src/Button.h
	g++ -o obj/Button.o -c src/Button.cpp $(CPPFLAGS)

clean:
	rm obj/*.o bin/main