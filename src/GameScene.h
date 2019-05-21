#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Board.h"
#include "Scene.h"
#include "GameSettings.h"

class GameScene : public Scene {
   public:
    GameScene(SceneStack& stack, Context& context);
    ~GameScene();

    bool input(const sf::Event& e);
    void draw();
    bool update(sf::Time deltaTime);

   private:
    struct GameState {
        unsigned int numberOfShips[2];
        bool turn;
    };

   private:
    // struct PlayerBoards {
    //     PlayerBoards(GameSettings& gameSettings);

    //     std::vector<std::vector<Board::CellState>> player1;
    //     std::vector<std::vector<Board::CellState>> player2;
    // };

    Board player1Board;
    Board player2Board;

    // PlayerBoards mPlayerBoards;

    // std::vector<std::vector<Board::CellState>> mPlayer1Board;
    // std::vector<std::vector<Board::CellState>> mPlayer2Board;

    sf::RenderWindow& mWindow;
    sf::RectangleShape mBackground;
    sf::Text mTestText;
};

#endif