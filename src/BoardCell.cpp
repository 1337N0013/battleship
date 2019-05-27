#include "BoardCell.h"
#include "Command.h"

BoardCell::BoardCell(sf::Vector2u coord, BoardCell::State state,
                     Scene::Context& context, GameScene::GameState& gameState)
    : Button("", context.font),
      mContext(context),
      mGameState(gameState),
      mCurrentState(state),
      mCoord(coord),
      wasCoordSet(false),
      mShipTexture(context.ship),
      mHitTexture(context.hit),
      mMissTexture(context.miss) {}

BoardCell::BoardCell(unsigned int x, unsigned int y, BoardCell::State state,
                     Scene::Context& context, GameScene::GameState& gameState)
    : BoardCell(sf::Vector2u(x, y), state, context, gameState) {}

BoardCell::BoardCell(sf::Vector2u coord, Scene::Context& context,
                     GameScene::GameState& gameState)
    : BoardCell(coord, BoardCell::State::Inactive, context, gameState) {}

BoardCell::BoardCell(unsigned int x, unsigned int y, Scene::Context& context,
                     GameScene::GameState& gameState)
    : BoardCell(sf::Vector2u(x, y), BoardCell::State::Inactive, context,
                gameState) {}

BoardCell::BoardCell(const BoardCell& bc)
    : Button("", bc.mContext.font),
      mContext(bc.mContext),
      mGameState(bc.mGameState),
      mCurrentState(bc.mCurrentState),
      mCoord(bc.mCoord),
      wasCoordSet(false),
      mShipTexture(bc.mContext.ship),
      mHitTexture(bc.mContext.hit),
      mMissTexture(bc.mContext.miss) {}

void BoardCell::setState(BoardCell::State state) { mCurrentState = state; }

void BoardCell::setState(Button::State state) { Button::setState(state); }

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
    mStateSprite.setColor(sf::Color::White);
    if (mCurrentState == State::Ship) {
        if (mGameState.currentPhase == GameScene::GameState::Phase::Battle) {
            mStateSprite.setColor(sf::Color::Transparent);
        } else {
            mStateSprite.setTexture(mShipTexture, true);
        }
    } else if (mCurrentState == State::Hit) {
        mStateSprite.setTexture(mHitTexture, true);
    } else if (mCurrentState == State::Miss) {
        mStateSprite.setTexture(mMissTexture, true);
    } else if (mCurrentState == State::Inactive) {
        return false;
    }
    mStateSprite.setOrigin(mStateSprite.getLocalBounds().width / 2,
                           mStateSprite.getLocalBounds().height / 2);
    // mStateSprite.setPosition(
    //     Button::getGlobalBounds().width / 2 + Button::getPosition().x,
    //     Button::getGlobalBounds().height / 2 + Button::getPosition().y);
    mStateSprite.setPosition(
        Button::getPosition().x + Button::getGlobalBounds().width / 2,
        Button::getPosition().y + Button::getGlobalBounds().height / 2);
    mStateSprite.setScale(.05, .05);
    Button::update(deltaTime);
    return true;
}

void BoardCell::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    Button::draw(target, states);
    target.draw(mStateSprite, states);
}