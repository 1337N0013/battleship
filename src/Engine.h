#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Context.h"
#include "MainMenuScene.h"
#include "SceneStack.h"

constexpr unsigned int windowWidth = 800, windowHeight = 600;

class Engine {
    sf::RenderWindow m_window;
    bool windowFocus;

    sf::Font font;

    std::unique_ptr<SceneStack> mSceneStack;
    std::unique_ptr<MainMenuScene> mainMenuScene;

    std::unique_ptr<Context> gameContext;

    void input();
    void update(sf::Time deltaTime);
    void draw();

   public:
    Engine();
    void start();
};

#endif