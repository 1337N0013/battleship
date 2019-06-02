#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>
#include "BoardCell.h"
#include "GameScene.h"
#include "Scene.h"

class Board : public sf::Drawable {
   public:
    Board(GameScene::GameState& state, Scene::Context& context);
    ~Board();
    std::vector<BoardCell>& operator[](int row);

    unsigned int getNumberOfShips();
    void setBattlePhase();

    bool input(sf::Event e);
    bool update(sf::Time deltaTime);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

   private:
    std::vector<std::vector<BoardCell>> mCells;
    GameScene::GameState& mGameState;

    sf::Text mLetters[10];
    sf::Text mNumbers[10];

    Scene::Context& mContext;
};

#endif