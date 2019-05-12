#ifndef SCENESTACK_H
#define SCENESTACK_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <unordered_map>
#include "Scene.h"

class SceneStack : private sf::NonCopyable {
   public:
    enum class Action { Push, Pop, Clear };

   public:
    explicit SceneStack(Scene::Context context);

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
        explicit PendingChange(Action action,
                               Scene::ID sceneID = Scene::ID::None);
        Action action;
        Scene::ID sceneID;
    };

   private:
    std::vector<std::unique_ptr<Scene>> mStack;
    std::vector<PendingChange> mPendingList;
    Scene::Context mContext;
    std::unordered_map<Scene::ID, std::function<std::unique_ptr<Scene>()>>
        mFactories;
};

template <typename T>
void SceneStack::registerScene(Scene::ID sceneID) {
    mFactories[sceneID] = [this]() {
        return std::unique_ptr<Scene>(new T(*this, mContext));
    };
}

#endif