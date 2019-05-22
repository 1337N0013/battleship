#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>
#include "BoardCell.h"
#include "Scene.h"
#include "GameScene.h"

class Board : public sf::Drawable {
   public:
    Board(GameScene::GameState& state, Scene::Context& context);
    ~Board();
    std::vector<BoardCell>& operator[](int row);

    bool input(sf::Event e);
    bool update(sf::Time deltaTime);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

   private:
    std::vector<std::vector<BoardCell>> mCells;
    GameScene::GameState& mGameState;
    
    Scene::Context& mContext;
};

#endif