#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Scene.h"
#include "SceneStack.h"

class MainMenuScene : public Scene {
   public:
    MainMenuScene(SceneStack& stack, Scene::Context context);
    ~MainMenuScene();
    void start();
    bool input(const sf::Event& e);
    void draw();
    bool update(sf::Time deltaTime);

   private:
    sf::Font mFont = Scene::getContext().getFont();
    sf::RenderWindow& mWindow = Scene::getContext().getWindow();
    sf::Vector2u mWindowSize = mWindow.getSize();

    sf::Text fpsCounter;
    sf::Time fpsTime = sf::Time::Zero;
    sf::Text title;
    Button btn, btn2;
};

#endif