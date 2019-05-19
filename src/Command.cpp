#include "Command.h"

Command::~Command() {}

namespace SceneCommand {

ChangeScene::~ChangeScene() {}
ChangeScene::ChangeScene(Scene& currentScene, Scene::ID sceneID)
    : mScene(currentScene), mSceneID(sceneID) {}
void ChangeScene::execute() { mScene.requestScenePush(mSceneID); }

RemoveScene::RemoveScene(Scene& currentScene) : mScene(currentScene) {}
RemoveScene::~RemoveScene() {}
void RemoveScene::execute() { mScene.requestScenePop(); }

ChangeAndRemoveScene::ChangeAndRemoveScene(Scene& currentScene,
                                           Scene::ID sceneID)
    : mScene(currentScene), mSceneID(sceneID) {}
ChangeAndRemoveScene::~ChangeAndRemoveScene() {}
void ChangeAndRemoveScene::execute() {
    mScene.requestScenePop();
    mScene.requestScenePush(mSceneID);
}

ReturnToMainMenu::ReturnToMainMenu(Scene& currentScene)
    : mScene(currentScene) {}
ReturnToMainMenu::~ReturnToMainMenu() {}
void ReturnToMainMenu::execute() {
    mScene.requestSceneClear();
    mScene.requestScenePush(Scene::ID::MainMenu);
}

}  // namespace SceneCommand

namespace SettingsCommand {

IncreaseShips::IncreaseShips(Scene::Context& context) : mContext(context) {}
IncreaseShips::~IncreaseShips() {}
void IncreaseShips::execute() {
    unsigned int ships = mContext.gameSettings.getNumberOfShips();
    const unsigned int tiles = mContext.gameSettings.getBoardSize().x *
                               mContext.gameSettings.getBoardSize().y;
    if (tiles / 2 == ships) {
        return;
    }
    mContext.gameSettings.setNumberOfShips(ships + 1);
}

DecreaseShips::DecreaseShips(Scene::Context& context) : mContext(context) {}
DecreaseShips::~DecreaseShips() {}
void DecreaseShips::execute() {
    const unsigned int ships = mContext.gameSettings.getNumberOfShips();
    if (ships == 1) {
        return;
    }
    mContext.gameSettings.setNumberOfShips(ships - 1);
}

IncreaseBoard::IncreaseBoard(Scene::Context& context) : mContext(context) {}
IncreaseBoard::~IncreaseBoard() {}
void IncreaseBoard::execute() {
    sf::Vector2u size = mContext.gameSettings.getBoardSize();
    size.x++;
    size.y++;
    mContext.gameSettings.setBoardSize(size);
}

DecreaseBoard::DecreaseBoard(Scene::Context& context) : mContext(context) {}
DecreaseBoard::~DecreaseBoard() {}
void DecreaseBoard::execute() {
    sf::Vector2u size = mContext.gameSettings.getBoardSize();
    if (size.x == 2 || size.y == 2) {
        return;
    }
    size.x--;
    size.y--;
    mContext.gameSettings.setBoardSize(size);
}

}  // namespace SettingsCommand