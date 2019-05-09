#include <SFML/Graphics.hpp>
#include "Context.h"

#ifndef SCENE_H
#define SCENE_H

class Scene {
   public:
    Scene(Context& context)
        : mWindow(context.getWindow()), mFont(context.getFont()) {
        mWidth = mWindow.getSize().x;
        mHeight = mWindow.getSize().y;
    }
    virtual ~Scene() {}
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