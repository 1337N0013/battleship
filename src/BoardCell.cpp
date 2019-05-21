#include "BoardCell.h"

BoardCell::BoardCell(Scene::Context& context)
    : Button("", context.font),
      mContext(context),
      mCurrentState(State::Inactive) {}

BoardCell::BoardCell(const BoardCell& bc)
    : Button("", bc.mContext.font),
      mContext(bc.mContext),
      mCurrentState(bc.mCurrentState) {}

void BoardCell::input(sf::Event e) { handleInput(e); }

void BoardCell::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    Button::draw(target, states);
}