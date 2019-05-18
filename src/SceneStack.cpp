#include "SceneStack.h"
#include <iostream>
#include <assert.h>

SceneStack::SceneStack(Scene::Context context) : mContext(context) {}

std::unique_ptr<Scene> SceneStack::createScene(Scene::ID sceneID) {
    auto found = mFactories.find(sceneID);
    assert(found != mFactories.end());

    return found->second();
}

void SceneStack::handleEvent(const sf::Event& event) {
    // for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr) {
    //     if (!(*itr)->input(event)) {
    //         return;
    //     }
    // }
    if (!mStack.empty()) {
        mStack.back()->input(event);
    }

    applyPendingChanges();
}

void SceneStack::update(sf::Time deltaTime) {
    for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr) {
        if (!(*itr)->update(deltaTime)) {
            return;
        }
    }

    applyPendingChanges();
}

void SceneStack::draw() {
    for (std::unique_ptr<Scene>& scene : mStack) {
        scene->draw();
    }
}

void SceneStack::applyPendingChanges() {
    for (PendingChange change : mPendingList) {
        switch (change.action) {
            case Action::Push:
                mStack.push_back(createScene(change.sceneID));
                break;
            case Action::Pop:
                mStack.pop_back();
                break;
            case Action::Clear:
                mStack.clear();
                break;
        }
    }

    mPendingList.clear();
}

bool SceneStack::isEmpty() const {
    if (mStack.size() == 0) {
        return true;
    }
    return false;
}

SceneStack::PendingChange::PendingChange(Action action, Scene::ID sceneID)
    : action(action), sceneID(sceneID) {}

void SceneStack::pushScene(Scene::ID sceneID) {
    mPendingList.push_back(PendingChange(Action::Push, sceneID));
}

void SceneStack::popScene() {
    mPendingList.push_back(PendingChange(Action::Pop));
}

void SceneStack::clearScenes() {
    mPendingList.push_back(PendingChange(Action::Clear));
}