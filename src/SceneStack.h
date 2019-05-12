#ifndef SCENESTACK_H
#define SCENESTACK_H

#include <SFML/Graphics.hpp>
#include <functional>
#include "Context.h"
#include "Scene.h"

class SceneStack : private sf::NonCopyable {
   public:
    enum class Action { Push, Pop, Clear };

   public:
    explicit SceneStack(Context context);

    template <typename T>
    void registerScene(Scene::ID sceneID);

    void update(sf::Time deltaTime);
    void draw();
    void handleEvent(const sf::Event& event);

    void pushScene(Scene::ID sceneID);
    void popScene();
    void clearScenes();

    bool isEmpty() const;

   private:
    std::unique_ptr<Scene> createScene(Scene::ID sceneID);
    void applyPendingChanges();

   private:
    struct PendingChange {
        Action action;
        Scene::ID sceneID;
    };

   private:
    std::vector<std::unique_ptr<Scene>> mStack;
    std::vector<PendingChange> mPendingList;
    Context mContext;
    std::map<Scene::ID, std::function<std::unique_ptr<Scene>>> mFactories;
};

#endif