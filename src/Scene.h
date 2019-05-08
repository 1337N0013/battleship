#include <SFML/Graphics.hpp>

#ifndef SCENE_H
#define SCENE_H

class Scene {
   public:
    Scene(sf::RenderWindow& window, unsigned int width, unsigned int height, sf::Font& font);
    ~Scene();
    virtual void start() = 0;
    virtual void input(sf::Event e) = 0;
    virtual void draw() = 0;
    virtual void update(sf::Time deltaTime) = 0;

   protected:
    sf::RenderWindow& mWindow;
    unsigned int mWidth;
    unsigned int mHeight;
    sf::Font& mFont;
};

#endif