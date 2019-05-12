#include "SceneStack.h"

template <typename T>
void SceneStack::registerScene(Scene::ID sceneID) {
    mFactories[stateID] = [this]() {
        return std::unique_ptr<Scene>(new T(*this, mContext));
    }
}

std::unique_ptr<Scene> SceneStack::createScene(Scene::ID sceneID) {
    auto found = mFactories.find(sceneID);
    assert (found != mFactories.end());

    return found->second();
}

void SceneStack::handleEvent(const sf::Event& event) {
    for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr) {
        if (!(*itr)->input(event)) {
            return;
        }
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
    for (auto itr = mStack.begin(); itr != mStack.end(); ++itr) {
        (*itr)->draw();
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
    if (mStack.size == 0) {
        return true;
    }
    return false;
}