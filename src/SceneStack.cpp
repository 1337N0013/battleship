#include "SceneStack.h"

template <typename T>
void SceneStack::registerScene(Scenes::ID sceneID) {
    mFactories[stateID] = [this]() {
        return std::unique_ptr<Scene>(new T(*this, mContext));
    }
}