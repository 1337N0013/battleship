#ifndef PAUSESCENE_H
#define PAUSESCENE_H

#include "Scene.h"
#include "Button.h"

class PauseScene : public Scene {
   public:
    PauseScene(SceneStack& stack, Context& context);
    ~PauseScene();
    bool input(const sf::Event& e);
    void draw();
    bool update(sf::Time deltaTime);

   private:
    sf::Text mPauseText;
    Button mExitButton;
};

#endif