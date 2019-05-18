#include "Command.h"

namespace Command {
ChangeState::ChangeState(SceneStack& sceneStack, Scene::ID sceneID)
    : mStack(sceneStack), mSceneID(sceneID) {}

void ChangeState::execute() {
    mStack.popScene();
    mStack.pushScene(mSceneID);
}
}  // namespace Command