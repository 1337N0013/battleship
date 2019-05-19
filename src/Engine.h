#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "SceneStack.h"
#include "GameSettings.h"

constexpr unsigned int windowWidth = 1024, windowHeight = 768;

class Engine {
    sf::RenderWindow mWindow;
    sf::Font mFont;
    GameSettings mGameSettings;
    SceneStack mSceneStack;

    sf::Text mFpsCounter;
    sf::Time mFpsTime;

    void input();
    void update(sf::Time deltaTime);
    void draw();

   public:
    Engine();
    void start();
    void registerScenes();
};

#endif