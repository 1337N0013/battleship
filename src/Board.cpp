#include "Board.h"
#include <iostream>

Board::Board(Scene::Context& context)
    : mContents(10, std::vector<CellState>(10)), mContext(context) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            std::cout << i << ", " << j << std::endl;
            mContents[i][j] = Board::CellState::Inactive;
        }
    }
}

Board::~Board() {}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const {}