#ifndef BOARDCELL_H
#define BOARDCELL_H

#include <SFML/Graphics.hpp>
#include "Button.h"

class BoardCell : public Button {
    public:
    BoardCell(Scene::Context& context);
    BoardCell(const BoardCell&);

    void input(sf::Event e);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
    Scene::Context& mContext;
};

#endif