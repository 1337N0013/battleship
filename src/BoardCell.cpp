#include "BoardCell.h"

BoardCell::BoardCell(Scene::Context& context)
    : Button("", context.font),
      mContext(context),
      mCurrentState(State::Inactive) {}

BoardCell::BoardCell(const BoardCell& bc)
    : Button("", bc.mContext.font),
      mContext(bc.mContext),
      mCurrentState(bc.mCurrentState) {}

void BoardCell::setState(BoardCell::State state) { mCurrentState = state; }

BoardCell::State BoardCell::getState() { return mCurrentState; }

bool BoardCell::input(sf::Event e) {
    if (mCurrentState == State::Inactive) {
        return false;
    }
    Button::handleInput(e);
    return true;
}

bool BoardCell::update(sf::Time deltaTime) {
    if (mCurrentState == State::Inactive) {
        return false;
    }
    Button::update(deltaTime);
    return true;
}

void BoardCell::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    Button::draw(target, states);
}