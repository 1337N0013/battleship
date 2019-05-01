#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Button.h"
#include "Fonts.h"

#ifndef ENGINE_H
#define ENGINE_H

constexpr unsigned int windowWidth = 800, windowHeight = 600;

class Engine {
    sf::RenderWindow m_window;
    bool windowFocus;

    sf::Font titleFont;
    sf::Text title;
    Button btn;
    Button btn2;

    void input();
    void update(sf::Time deltaTime);
    void draw();

   public:
    Engine();
    void start();
};

#endif