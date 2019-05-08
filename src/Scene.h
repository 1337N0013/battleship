#include <SFML/Graphics.hpp>

#ifndef SCENE_H
#define SCENE_H

class Scene {
   public:
    Scene(sf::RenderWindow& window);
    virtual void start();
    virtual void input(sf::Event e);
    virtual void draw();
    virtual void update();

   private:
    sf::RenderWindow& mWindow;
};

#endif