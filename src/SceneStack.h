#include <SFML/Graphics.hpp>
#include "Context.h"
#include "Scene.h"
#include "SceneIdentifiers.h"

#ifndef SCENESTACK_H
#define SCENESTACK_H

class SceneStack : private sf::NonCopyable {
   public:
    enum class Action { Push, Pop, Clear };

   public:
    explicit SceneStack(Context context);

    template <typename T>
    void registerScene(Scenes::ID sceneID);

    void update(sf::Time deltaTime);
    void draw();
    void handleEvent(const sf::Event& event);

    void pushScene(Scenes::ID sceneID);
    void popScene();
    void clearScenes();

   private:
    std::unique_ptr<Scene> createScene(Scenes::ID sceneID);
    void applyPendingChanges();

   private:
    struct PendingChange {
        Action action;
        Scenes::ID sceneID;
    };

   private:
    std::vector<std::unique_ptr<Scene>> mStack;
    std::vector<PendingChange> mPendingList;
    Context mContext;
    std::map<Scenes::ID, std::function<std::unique_ptr<Scene>>> mFactories;
};

#endif