#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Scenes.h"

#ifndef ENGINE_H
#define ENGINE_H

constexpr unsigned int windowWidth = 800, windowHeight = 600;

class Engine {
    sf::RenderWindow m_window;
    bool windowFocus;

    sf::Font font;
    std::unique_ptr<MainMenuScene> mainMenuScene;

    void input();
    void update(sf::Time deltaTime);
    void draw();

   public:
    Engine();
    void start();
};

#endif