#ifndef COMMAND_H
#define COMMAND_H

#include "Board.h"
#include "BoardCell.h"
#include "Scene.h"
#include "SceneStack.h"

class Command {
   public:
    virtual ~Command();
    virtual void execute() = 0;
};

class EmptyCommand : public Command {
   public:
    EmptyCommand();
    ~EmptyCommand();
    void execute();
};

namespace SceneCommand {

class ChangeScene : public Command {
   public:
    ChangeScene(Scene& currentScene, Scene::ID sceneID);
    ~ChangeScene();
    void execute();

   private:
    Scene& mScene;
    Scene::ID mSceneID;

    sf::SoundBuffer mSoundBuffer;
    sf::Sound mSound;
};

class RemoveScene : public Command {
   public:
    RemoveScene(Scene& currentScene);
    ~RemoveScene();
    void execute();

   private:
    Scene& mScene;
};

class ChangeAndRemoveScene : public Command {
   public:
    ChangeAndRemoveScene(Scene& currentScene, Scene::ID sceneID);
    ~ChangeAndRemoveScene();
    void execute();

   private:
    Scene& mScene;
    Scene::ID mSceneID;

    sf::SoundBuffer mSoundBuffer;
    sf::Sound mSound;
};

class ReturnToMainMenu : public Command {
   public:
    ReturnToMainMenu(Scene& currentScene);
    ~ReturnToMainMenu();
    void execute();

   private:
    Scene& mScene;
};

}  // namespace SceneCommand

namespace SettingsCommand {

class IncreaseShips : public Command {
   public:
    IncreaseShips(Scene::Context& context);
    ~IncreaseShips();
    void execute();

   private:
    Scene::Context& mContext;
};

class DecreaseShips : public Command {
   public:
    DecreaseShips(Scene::Context& context);
    ~DecreaseShips();
    void execute();

   private:
    Scene::Context& mContext;
};

class IncreaseBoard : public Command {
   public:
    IncreaseBoard(Scene::Context& context);
    ~IncreaseBoard();
    void execute();

   private:
    Scene::Context& mContext;
};

class DecreaseBoard : public Command {
   public:
    DecreaseBoard(Scene::Context& context);
    ~DecreaseBoard();
    void execute();

   private:
    Scene::Context& mContext;
};

}  // namespace SettingsCommand

namespace GameCommands {

class PlaceShip : public Command {
   public:
    PlaceShip(GameScene::GameState& state, BoardCell& cell, sf::SoundBuffer& sound);
    PlaceShip(GameScene::GameState& state, Board board, sf::Vector2u coord, sf::SoundBuffer& sound);
    PlaceShip(GameScene::GameState& state, Board board, unsigned int x,
              unsigned int y, sf::SoundBuffer& sound);
    ~PlaceShip();
    void execute();

   private:
    GameScene::GameState& mGameState;
    BoardCell& mCell;
    // JOSIAH WAS HERE
    sf::SoundBuffer& mConfirm;
    sf::Sound mConfirmSFX;
};

class Attack : public Command {
   public:
    Attack(GameScene::GameState& state, BoardCell& cell, Scene::Context& context);
    Attack(GameScene::GameState& state, Board board, sf::Vector2u coord, Scene::Context& context);
    Attack(GameScene::GameState& state, Board board, unsigned int x,
           unsigned int y, Scene::Context& context);
    ~Attack();
    void execute();

   private:
    GameScene::GameState& mGameState;
    BoardCell& mCell;
    Scene::Context& mContext;
    sf::Sound mSFX;
};

class ChangeGameState : public Command {
   public:
    ChangeGameState(GameScene::GameState&, GameScene::GameState::Phase);
    ~ChangeGameState();
    void execute();

   private:
    GameScene::GameState& mState;
    GameScene::GameState::Phase mPhase;
};

}  // namespace GameCommands

#endif