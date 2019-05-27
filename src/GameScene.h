#ifndef GAMESCENE_H
#define GAMESCENE_H

// #include "Board.h"
#include "Button.h"
#include "GameSettings.h"
#include "Scene.h"

class Board;

class GameScene : public Scene {
   public:
    struct GameState {
        GameState(GameSettings& gameSettings);

        unsigned int getTurn();
        unsigned int getPlayer();
        void incrementTurn();
        void resetTurnsToZero();

        enum class Phase { Transition, Preparation, Battle, Victory };
        Phase currentPhase;
        unsigned int numberOfShips[2];
        unsigned int maxShips;
        sf::Time gameTime;

       private:
        int turn;
    };

   public:
    GameScene(SceneStack& stack, Context& context);
    ~GameScene();

    bool input(const sf::Event& e);
    void draw();
    bool update(sf::Time deltaTime);

    GameState currentGameState;

   private:
    std::unique_ptr<Board> playerBoards[2];

    sf::Sprite mGameBackgroundSprite;
    sf::Sprite mGreenLed;
    sf::Sprite mRedLed;
    sf::Sprite mYellowLed;
    sf::Sprite mGrille;
    sf::Text mVictory;
    sf::Text mPlayerWin;
    sf::Text mTurns;
    sf::Text mShipsLeft;
    sf::Text mTime;
    Button mMainMenu;

    sf::Sprite mThreeStars;
    sf::Sprite mMedals[2];
    sf::Time mMedalBounceTime;
    int mMedalBounceSpeed;

    sf::RenderWindow& mWindow;
    sf::RectangleShape mBackground;
    sf::Music& mGameSceneMusic;
    sf::Music& mVictoryMusic;
    sf::Time victoryBlinkTime;
    sf::Time mActionTime;

    Button mPreparationButtons[2];
    sf::Text mTransition;
    sf::Text mTransitionSubtitle;

    sf::Text mWhosTurnText;
    sf::Text mGameClockText;
    sf::Text mTurnCounterText;
    sf::Text mYourShipsText;
    sf::Text mEnemyShipsText;
    sf::Text mWhosTurnValueText;
    sf::Text mGameClockValueText;
    sf::Text mTurnCounterValueText;
    sf::Text mYourShipsValueText;
    sf::Text mEnemyShipsValueText;


    // JOSIAH AND THOMAS WERE HERE
    sf::RectangleShape mWhosTurn, mGameClock, mTurnCounter, mYourShips,
        mEnemyShips;

    //(770, 40, 984, 100);
};

#endif