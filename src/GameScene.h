#ifndef GAMESCENE_H
#define GAMESCENE_H

// #include "Board.h"
#include "GameSettings.h"
#include "Scene.h"

class Board;

class GameScene : public Scene {
   public:
    struct GameState {
        GameState(GameSettings& gameSettings);

        unsigned int getTurn();
        unsigned int getPlayer();
        void incrementTurn();
        void resetTurnsToZero();

        enum class Phase { Preparation, Battle };
        Phase currentPhase;
        unsigned int numberOfShips[2];
        unsigned int maxShips;

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
    // struct PlayerBoards {
    //     PlayerBoards(GameSettings& gameSettings);

    //     std::vector<std::vector<Board::CellState>> player1;
    //     std::vector<std::vector<Board::CellState>> player2;
    // };

    std::unique_ptr<Board> playerBoards[2];

    // PlayerBoards mPlayerBoards;

    // std::vector<std::vector<Board::CellState>> mPlayer1Board;
    // std::vector<std::vector<Board::CellState>> mPlayer2Board;

    sf::RenderWindow& mWindow;
    sf::RectangleShape mBackground;
    sf::Text mTestText;
};

#endif