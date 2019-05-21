#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>

class Board : public sf::Drawable {
   public:
    enum class CellState { None, Ship, Hit, Miss };  // i guess i never miss yah

   public:
    Board(std::vector<std::vector<CellState>>);

   private:
};

#endif