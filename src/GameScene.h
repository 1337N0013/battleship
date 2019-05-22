#ifndef GAMESCENE_H
#define GAMESCENE_H

// #include "Board.h"
#include "Scene.h"
#include "GameSettings.h"

class Board;

class GameScene : public Scene {
   public:
    struct GameState {
        GameState();
        enum class Phase { Preparation, Battle };
        unsigned int numberOfShips[2];
        bool turn;
        Phase currentPhase;
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

    std::unique_ptr<Board> player1Board;
    std::unique_ptr<Board> player2Board;

    // PlayerBoards mPlayerBoards;

    // std::vector<std::vector<Board::CellState>> mPlayer1Board;
    // std::vector<std::vector<Board::CellState>> mPlayer2Board;

    sf::RenderWindow& mWindow;
    sf::RectangleShape mBackground;
    sf::Text mTestText;
};

#endif