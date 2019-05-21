#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>

class Board : public sf::Drawable {
   public:
    //
   private:
    enum class CellState { None, Hit, Miss };
};

#endif