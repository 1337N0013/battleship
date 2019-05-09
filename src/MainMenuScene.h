#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "Button.h"

#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H

class MainMenuScene : public Scene{
   public:
    MainMenuScene(Context& context);
    ~MainMenuScene();
    void start();
    void input(sf::Event e);
    void draw();
    void update(sf::Time deltaTime);

   private:
    sf::Text fpsCounter;
    sf::Time fpsTime = sf::Time::Zero;
    sf::Text title;
    Button btn, btn2;
};

#endif