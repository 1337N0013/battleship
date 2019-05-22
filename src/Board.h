#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>
#include "BoardCell.h"
#include "Scene.h"

class Board : public sf::Drawable {
   public:
    Board(Scene::Context& context);
    ~Board();
    std::vector<BoardCell>& operator[](int row);

    bool input(sf::Event e);
    bool update(sf::Time deltaTime);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

   private:
    Scene::Context& mContext;

    std::vector<std::vector<BoardCell>> mCells;
};

#endif