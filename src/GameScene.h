#ifndef GAMESCENE_H
#define GAMESCENE_H

// #include "Board.h"
#include "GameSettings.h"
#include "Scene.h"
#include "Button.h"

class Board;

class GameScene : public Scene {
   public:
    struct GameState {
        GameState(GameSettings& gameSettings);

        unsigned int getTurn();
        unsigned int getPlayer();
        void incrementTurn();
        void resetTurnsToZero();

        enum class Phase { Preparation, Battle, Victory };
        Phase currentPhase;
        unsigned int numberOfShips[2];
        unsigned int maxShips;
        sf::Time gameTime;

       private:
        int turn;
    };

   public:
    GameScene(SceneStack& stack, Context& context);
    ~GameScene();

    bool input(const sf::Event& e);
    void draw();
    bool update(sf::Time deltaTime);

    GameState currentGameState;

   private:
    std::unique_ptr<Board> playerBoards[2];

    sf::Text mVictory;
    sf::Text mStats;
    Button mMainMenu;

    sf::RenderWindow& mWindow;
    sf::RectangleShape mBackground;
    sf::Music& mGameSceneMusic;
    sf::Music& mVictoryMusic;
};

#endif