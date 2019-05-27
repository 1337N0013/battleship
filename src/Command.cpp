#include "Command.h"
#include <iostream>

Command::~Command() {}

EmptyCommand::EmptyCommand() {}

EmptyCommand::~EmptyCommand() {}

void EmptyCommand::execute() {}

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
    if (size.x >= 10 || size.y >= 10) {
        return;
    }
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

namespace GameCommands {

PlaceShip::PlaceShip(GameScene::GameState& state, BoardCell& cell)
    : mGameState(state), mCell(cell), mConfirmSFX(mConfirm) {
    mConfirm.loadFromFile("res/audio/sfx/confirm.ogg");
    mConfirmSFX.setPitch(1);
    mConfirmSFX.setVolume(100);
}
PlaceShip::PlaceShip(GameScene::GameState& state, Board board,
                     sf::Vector2u coord)
    : mGameState(state), mCell(board[coord.x][coord.y]) {}
PlaceShip::PlaceShip(GameScene::GameState& state, Board board, unsigned int x,
                     unsigned int y)
    : mGameState(state), mCell(board[x][y]) {}
PlaceShip::~PlaceShip() {}
void PlaceShip::execute() {
    if (mCell.getState() == BoardCell::State::None &&
        mGameState.numberOfShips[mGameState.getPlayer()] <
            mGameState.maxShips) {
        mGameState.numberOfShips[mGameState.getPlayer()]++;
        std::cout << "PLAYER " << mGameState.getPlayer() + 1
                  << " PLACED SHIP AT (" << mCell.getCoord().x << ", "
                  << mCell.getCoord().y << ")\n";
        // JOSIAH WAS HERE
        mConfirmSFX.play();
        mCell.setState(BoardCell::State::Ship);
    }
    std::cout << "AT (" << mCell.getCoord().x << ", " << mCell.getCoord().y
              << ")\n";
    std::cout << "SHIPS: " << mGameState.numberOfShips[mGameState.getPlayer()]
              << " OUT OF " << mGameState.maxShips << "\n";
}

Attack::Attack(GameScene::GameState& state, BoardCell& cell)
    : mGameState(state),
      mCell(cell),
      mSplashSFX(mSplash),
      mExplodeSFX(mExplode) {
    // JOSIAH WAS HERE
    mSplash.loadFromFile("res/audio/sfx/splash.ogg");
    mSplashSFX.setPitch(1);
    mSplashSFX.setVolume(100);
    mExplode.loadFromFile("res/audio/sfx/explode.ogg");
    mExplodeSFX.setPitch(1);
    mExplodeSFX.setVolume(100);
}
Attack::Attack(GameScene::GameState& state, Board board, sf::Vector2u coord)
    : mGameState(state), mCell(board[coord.x][coord.y]) {}
Attack::Attack(GameScene::GameState& state, Board board, unsigned int x,
               unsigned int y)
    : mGameState(state), mCell(board[x][y]) {}
Attack::~Attack() {}
void Attack::execute() {
    if (mCell.getState() == BoardCell::State::Ship &&
        mGameState.numberOfShips[mGameState.getPlayer()] > 0) {
        mGameState.numberOfShips[mGameState.getPlayer()]--;
        std::cout << "PLAYER " << mGameState.getPlayer() + 1 << " HIT ("
                  << mCell.getCoord().x << ", " << mCell.getCoord().y << ")\n";
        mExplodeSFX.play();
        mCell.setState(BoardCell::State::Hit);
        mGameState.incrementTurn();
    } else if (mCell.getState() == BoardCell::State::None) {
        std::cout << "PLAYER " << mGameState.getPlayer() + 1 << " MISSED AT ("
                  << mCell.getCoord().x << ", " << mCell.getCoord().y << ")\n";
        std::cout << "SHIPS: "
                  << mGameState.numberOfShips[mGameState.getPlayer()]
                  << " OUT OF " << mGameState.maxShips << "\n";
        // JOSIAH WAS HERE
        mSplashSFX.play();
        mCell.setState(BoardCell::State::Miss);
        mGameState.incrementTurn();
    }
    std::cout << "TURN IS NOW " << mGameState.getTurn() << "\n";
}

ChangeGameState::ChangeGameState(GameScene::GameState& gameState,
                                 GameScene::GameState::Phase phase)
    : mState(gameState), mPhase(phase) {}
ChangeGameState::~ChangeGameState() {}
void ChangeGameState::execute() { mState.currentPhase = mPhase; }

}  // namespace GameCommands