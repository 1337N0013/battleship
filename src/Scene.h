#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics.hpp>
#include "SceneStack.h"
#include "Context.h"

class Scene {
   public:
    Scene(SceneStack& stack, Context context)
        : mStack(stack), mContext(context) {}
    virtual ~Scene() {}
    virtual void start() = 0;
    virtual void input(const sf::Event& e) = 0;
    virtual void draw() = 0;
    virtual void update(sf::Time deltaTime) = 0;

   protected:
    Context getContext() const { return mContext; }

   private:
    SceneStack& mStack;
    Context mContext;
};

#endif