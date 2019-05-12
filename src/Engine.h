#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Context.h"
#include "SceneStack.h"

constexpr unsigned int windowWidth = 800, windowHeight = 600;

class Engine {
    sf::RenderWindow m_window;

    sf::Font font;
    std::unique_ptr<Context> gameContext;

    std::unique_ptr<SceneStack> mSceneStack;

    void input();
    void update(sf::Time deltaTime);
    void draw();

   public:
    Engine();
    void start();
    void registerScenes();
};

#endif