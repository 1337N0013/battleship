#ifndef BOARDCELL_H
#define BOARDCELL_H

#include <SFML/Graphics.hpp>
#include "Button.h"

class BoardCell : public Button {
    public:
    BoardCell(Scene::Context& context);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif