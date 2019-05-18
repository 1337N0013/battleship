#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

#include <SFML/Graphics.hpp>

class GameSettings {
   public:
    unsigned int getNumberOfShips();
    void setNumberOfShips(unsigned int n);

    sf::Vector2u getBoardSize();
    void setBoardSize(sf::Vector2u size);
    void setBoardSize(unsigned int width, unsigned int height);

   private:
    unsigned int mNumberOfShips;
    sf::Vector2u mBoardSize;
};

#endif