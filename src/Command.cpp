#include "Command.h"

namespace Command {

Command::~Command() {}

ChangeScene::~ChangeScene() {}

ChangeScene::ChangeScene(Scene& currentScene, Scene::ID sceneID)
    : mScene(currentScene), mSceneID(sceneID) {}

void ChangeScene::execute() {
    mScene.requestScenePop();
    mScene.requestScenePush(mSceneID);
}

RemoveScene::RemoveScene(Scene& currentScene) : mScene(currentScene) {}

RemoveScene::~RemoveScene() {}

void RemoveScene::execute() {
    mScene.requestScenePop();
}

}  // namespace Command