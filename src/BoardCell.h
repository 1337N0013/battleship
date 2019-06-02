#ifndef BOARDCELL_H
#define BOARDCELL_H

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "GameScene.h"

class BoardCell : public Button {
   public:
    enum class State {
        None,
        Ship,
        Hit,
        Miss,
        Inactive
    };  // i guess i never miss yah

   public:
    BoardCell(sf::Vector2u coord, BoardCell::State state,
              Scene::Context& context, GameScene::GameState& gameState);
    BoardCell(unsigned int x, unsigned int y, BoardCell::State state,
              Scene::Context& context, GameScene::GameState& gameState);
    BoardCell(sf::Vector2u coord, Scene::Context& context,
              GameScene::GameState& gameState);
    BoardCell(unsigned int x, unsigned int y, Scene::Context& context,
              GameScene::GameState& gameState);

    void setState(State state);
    void setState(Button::State state);
    State getState();

    // void setCoord(sf::Vector2u coord);
    // void setCoord(unsigned int x, unsigned int y);
    sf::Vector2u getCoord();

    bool input(sf::Event e);
    bool update(sf::Time deltaTime);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

   private:
    BoardCell::State mCurrentState;
    GameScene::GameState& mGameState;

    sf::Vector2u mCoord;
    bool wasCoordSet;

    sf::Texture& mShipTexture;
    sf::Texture& mHitTexture;
    sf::Texture& mMissTexture;

    sf::Sprite mStateSprite;

    Scene::Context& mContext;
};

#endif