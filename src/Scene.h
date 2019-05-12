#ifndef SCENE_H
#define SCENE_H

class SceneStack;

#include <SFML/Graphics.hpp>
#include "Context.h"
#include "SceneStack.h"

class Scene {
   public:
    enum class ID { None, MainMenu };

   public:
    Scene(SceneStack& stack, Context context);
    virtual ~Scene() {}
    virtual void start() = 0;
    virtual bool input(const sf::Event& e) = 0;
    virtual void draw() = 0;
    virtual bool update(sf::Time deltaTime) = 0;

   protected:
    void requestScenePush(Scene::ID sceneID);
    void requestScenePop();
    void requestSceneClear();

    Context getContext() const;

   private:
    SceneStack& mStack;
    Context mContext;
};

#endif