#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

#include <SFML/Graphics.hpp>

class GameSettings {
   public:
    unsigned int getNumberOfShips() { return mNumberOfShips; }
    void setNumberOfShips(unsigned int n) { mNumberOfShips = n; }

    sf::Vector2u getBoardSize() { return mBoardSize; }
    void setBoardSize(sf::Vector2u size) { mBoardSize = size; }
    void setBoardSize(unsigned int width, unsigned int height) {
        mBoardSize = sf::Vector2u(width, height);
    }

   private:
    unsigned int mNumberOfShips;
    sf::Vector2u mBoardSize;
};

#endif