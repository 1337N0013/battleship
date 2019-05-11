#include <SFML/Graphics.hpp>
#include "Context.h"

#ifndef SCENE_H
#define SCENE_H

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
    
    SceneStack& mStack;
    Context mContext;
};

#endif