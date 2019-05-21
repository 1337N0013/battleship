#include "BoardCell.h"

BoardCell::BoardCell(Scene::Context& context) : Button("", context.font) {}

void BoardCell::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    Button::draw(target, states);
}