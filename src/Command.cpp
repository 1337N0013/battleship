#include "Command.h"
#include <iostream>
#include "Button.h"

Command::~Command() {}

EmptyCommand::EmptyCommand() {}

EmptyCommand::~EmptyCommand() {}

void EmptyCommand::execute() {}

namespace SceneCommand {

ChangeScene::ChangeScene(Scene& currentScene, Scene::ID sceneID)
    : mScene(currentScene), mSceneID(sceneID), mSound(mSoundBuffer) {
    mSoundBuffer.loadFromFile("res/audio/sfx/confirm.ogg");
}
ChangeScene::~ChangeScene() {}
void ChangeScene::execute() {
    mSound.play();
    mScene.requestScenePush(mSceneID);
}

RemoveScene::RemoveScene(Scene& currentScene) : mScene(currentScene) {}
RemoveScene::~RemoveScene() {}
void RemoveScene::execute() { mScene.requestScenePop(); }

ChangeAndRemoveScene::ChangeAndRemoveScene(Scene& currentScene,
                                           Scene::ID sceneID)
    : mScene(currentScene), mSceneID(sceneID), mSound(mSoundBuffer) {
    mSoundBuffer.loadFromFile("res/audio/sfx/confirm.ogg");
}
ChangeAndRemoveScene::~ChangeAndRemoveScene() {}
void ChangeAndRemoveScene::execute() {
    mSound.play();
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

PlaceShip::PlaceShip(GameScene::GameState& state, BoardCell& cell,
                     sf::SoundBuffer& sound)
    : mGameState(state), mCell(cell), mConfirm(sound), mConfirmSFX(mConfirm) {}
PlaceShip::PlaceShip(GameScene::GameState& state, Board board,
                     sf::Vector2u coord, sf::SoundBuffer& sound)
    : mGameState(state), mCell(board[coord.x][coord.y]), mConfirm(sound) {}
PlaceShip::PlaceShip(GameScene::GameState& state, Board board, unsigned int x,
                     unsigned int y, sf::SoundBuffer& sound)
    : mGameState(state), mCell(board[x][y]), mConfirm(sound) {}
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

Attack::Attack(GameScene::GameState& state, BoardCell& cell,
               Scene::Context& context)
    : mGameState(state), mCell(cell), mContext(context) {}
Attack::Attack(GameScene::GameState& state, Board board, sf::Vector2u coord,
               Scene::Context& context)
    : mGameState(state), mCell(board[coord.x][coord.y]), mContext(context) {}
Attack::Attack(GameScene::GameState& state, Board board, unsigned int x,
               unsigned int y, Scene::Context& context)
    : mGameState(state), mCell(board[x][y]), mContext(context) {}
Attack::~Attack() {}
void Attack::execute() {
    if (mCell.getState() == BoardCell::State::Ship &&
        mGameState.numberOfShips[mGameState.getPlayer()] > 0) {
        mGameState.numberOfShips[mGameState.getPlayer()]--;
        std::cout << "PLAYER " << mGameState.getPlayer() + 1 << " HIT ("
                  << mCell.getCoord().x << ", " << mCell.getCoord().y << ")\n";

        mSFX.setBuffer(mContext.explode);
        mSFX.play();

        mCell.setState(BoardCell::State::Hit);
        mCell.setState(Button::State::Hovered);
        mGameState.incrementTurn();
    } else if (mCell.getState() == BoardCell::State::None) {
        std::cout << "PLAYER " << mGameState.getPlayer() + 1 << " MISSED AT ("
                  << mCell.getCoord().x << ", " << mCell.getCoord().y << ")\n";
        std::cout << "SHIPS: "
                  << mGameState.numberOfShips[mGameState.getPlayer()]
                  << " OUT OF " << mGameState.maxShips << "\n";

        // JOSIAH WAS HERE
        mSFX.setBuffer(mContext.splash);
        mSFX.play();

        mCell.setState(BoardCell::State::Miss);
        mCell.setState(Button::State::Hovered);
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