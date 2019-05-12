#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics.hpp>
#include "Context.h"

class SceneStack;

class Scene {
   public:
    enum class ID { MainMenu };

   public:
    Scene(SceneStack& stack, Context context)
        : mStack(stack), mContext(context) {}
    virtual ~Scene() {}
    virtual void start() = 0;
    virtual bool input(const sf::Event& e) = 0;
    virtual void draw() = 0;
    virtual bool update(sf::Time deltaTime) = 0;

   protected:
    void requestScenePush(Scene::ID sceneID);
    void requestScenePop();
    void requestSceneClear();

    Context getContext() const { return mContext; }

   private:
    SceneStack& mStack;
    Context mContext;
};

#endif