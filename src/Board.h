#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "BoardCell.h"

class Board : public sf::Drawable {
   public:
    enum class CellState { None, Ship, Hit, Miss, Inactive };  // i guess i never miss yah

   public:
    Board(Scene::Context& context);
    ~Board();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

   private:
    Scene::Context& mContext;
    std::vector<std::vector<CellState>> mData;

    std::vector<std::vector<BoardCell>> mCells;
};

#endif