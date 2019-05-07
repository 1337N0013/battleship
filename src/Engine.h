#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Button.h"
#include "FontManager.h"

#ifndef ENGINE_H
#define ENGINE_H

constexpr unsigned int windowWidth = 800, windowHeight = 600;

class Engine {
    sf::RenderWindow m_window;
    bool windowFocus;

    sf::Font font;
    sf::Text fpsCounter;
    sf::Text title;
    sf::Time fpsTime;
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