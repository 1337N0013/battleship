#ifndef SETTINGSSCENE_H
#define SETTINGSSCENE_H

#include "Button.h"
#include "Scene.h"

class SettingsScene : public Scene {
   public:
    SettingsScene(SceneStack& stack, Context& context);
    ~SettingsScene();
    bool input(const sf::Event& e);
    void draw();
    bool update(sf::Time deltaTime);

   private:
    sf::RectangleShape mBackground;
    sf::Text mSettingsText;

    sf::Text mNumberOfShipsText;
    Button mIncreaseShips;
    Button mDecreaseShips;

    sf::Text mBoardSizeText;
    Button mIncreaseBoard;
    Button mDecreaseBoard;

    sf::Sprite mHit;
    sf::Text mHitText;
    sf::Sprite mMiss;
    sf::Text mMissText;
    sf::Text mLegendText;

    Button playButton;
};

#endif