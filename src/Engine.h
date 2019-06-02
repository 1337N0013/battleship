#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GameSettings.h"
#include "SceneStack.h"

constexpr unsigned int windowWidth = 1024, windowHeight = 768;

class Engine {
    sf::RenderWindow mWindow;
    SceneStack mSceneStack;
    GameSettings mGameSettings;
    sf::Font mFont;
    sf::Font mSevenSegment;
    sf::Texture mBackground;
    sf::Texture mGameBackground;
    sf::Texture mGreenLed;
    sf::Texture mRedLed;
    sf::Texture mYellowLed;
    sf::Texture mGrille;
    sf::Texture mThreeStars;
    sf::Texture mMedal;
    sf::Texture mShip;
    sf::Texture mHit;
    sf::Texture mMiss;
    sf::SoundBuffer mConfirm;
    sf::SoundBuffer mExplode;
    sf::SoundBuffer mSplash;
    sf::Music mMainMenuMusic;
    sf::Music mGameSceneMusic;
    sf::Music mVictoryMusic;

    sf::Text mFpsCounter;
    sf::Time mFpsTime;

    void input();
    void update(sf::Time deltaTime);
    void draw();

   public:
    Engine();
    void start();
    void registerScenes();
};

#endif