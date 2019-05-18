#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"

class GameScene : public Scene {
   public:
    GameScene(SceneStack& stack, Context context);
    ~GameScene();

    bool input(const sf::Event& e);
    void draw();
    bool update(sf::Time deltaTime);
};

#endif