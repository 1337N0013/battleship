#include "Command.h"

namespace Command {

Command::~Command() {}

ChangeState::~ChangeState() {}

ChangeState::ChangeState(Scene& currentScene, Scene::ID sceneID)
    : mScene(currentScene), mSceneID(sceneID) {}

void ChangeState::execute() {
    mScene.requestScenePop();
    mScene.requestScenePush(mSceneID);
}

}  // namespace Command