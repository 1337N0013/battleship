#include "BoardCell.h"
#include "Command.h"

BoardCell::BoardCell(sf::Vector2u coord, BoardCell::State state,
                     Scene::Context& context)
    : Button("", context.font),
      mContext(context),
      mCurrentState(state),
      mCoord(coord),
      wasCoordSet(false),
      mShipTexture(context.ship),
      mHitTexture(context.hit),
      mMissTexture(context.miss) {}

BoardCell::BoardCell(unsigned int x, unsigned int y, BoardCell::State state,
                     Scene::Context& context)
    : BoardCell(sf::Vector2u(x, y), state, context) {}

BoardCell::BoardCell(sf::Vector2u coord, Scene::Context& context)
    : BoardCell(coord, BoardCell::State::Inactive, context) {}

BoardCell::BoardCell(unsigned int x, unsigned int y, Scene::Context& context)
    : BoardCell(sf::Vector2u(x, y), BoardCell::State::Inactive, context) {}

BoardCell::BoardCell(const BoardCell& bc)
    : Button("", bc.mContext.font),
      mContext(bc.mContext),
      mCurrentState(bc.mCurrentState),
      mCoord(bc.mCoord),
      wasCoordSet(false),
      mShipTexture(bc.mContext.ship),
      mHitTexture(bc.mContext.hit),
      mMissTexture(bc.mContext.miss) {}

void BoardCell::setState(BoardCell::State state) { mCurrentState = state; }

BoardCell::State BoardCell::getState() { return mCurrentState; }

// void BoardCell::setCoord(sf::Vector2u coord) {
//     if (wasCoordSet) {
//         std::cout << "Board cell was already set";
//         return;
//     }
//     mCoord = coord;
//     wasCoordSet = true;
// }

// void BoardCell::setCoord(unsigned int x, unsigned int y) {
//     setCoord(sf::Vector2u(x, y));
// }

sf::Vector2u BoardCell::getCoord() { return mCoord; }

bool BoardCell::input(sf::Event e) {
    if (mCurrentState == State::Inactive || mCurrentState == State::Hit ||
        mCurrentState == State::Miss) {
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