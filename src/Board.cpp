#include "Board.h"
#include <iostream>

Board::Board(Scene::Context& context)
    : mData(10, std::vector<CellState>(10)),
      mContext(context),
      mCells(10, std::vector<sf::RectangleShape>(10)) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            std::cout << i << ", " << j << std::endl;
            mData[i][j] = Board::CellState::Inactive;

            mCells[i][j].setSize(sf::Vector2f(69, 69));
            mCells[i][j].setPosition(69 * i + 40, 69 * j + 40);
            mCells[i][j].setOutlineThickness(2);
            mCells[i][j].setOutlineColor(sf::Color::Black);

            const int boardSize = context.gameSettings.getBoardSize().x;
            int xOffset = (10 / 2 - boardSize / 2);
            int yOffset = xOffset;
            if (boardSize % 2 != 0) {
                yOffset--;
            }
            if (i >= xOffset && i < xOffset + boardSize && j >= yOffset &&
                j < yOffset + boardSize) {
                mCells[i][j].setFillColor(sf::Color::Blue);
            } else {
                mCells[i][j].setFillColor(sf::Color::Red);
            }
        }
    }
}

Board::~Board() {}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (auto row : mCells) {
        for (auto cell : row) {
            target.draw(cell, states);
        }
    }
}