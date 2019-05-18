#include "GameSettings.h"

unsigned int GameSettings::getNumberOfShips() { return mNumberOfShips; }

void GameSettings::setNumberOfShips(unsigned int n) { mNumberOfShips = n; }

sf::Vector2u GameSettings::getBoardSize() { return mBoardSize; }

void GameSettings::setBoardSize(sf::Vector2u size) { mBoardSize = size; }

void GameSettings::setBoardSize(unsigned int width, unsigned int height) {
    mBoardSize = sf::Vector2u(width, height);
}