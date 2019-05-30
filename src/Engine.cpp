#include "Engine.h"
#include <iostream>
#include "GameScene.h"
#include "MainMenuScene.h"
#include "PauseScene.h"
#include "Scene.h"
#include "SettingsScene.h"

using std::cout;

Engine::Engine()
    : mWindow(sf::VideoMode(windowWidth, windowHeight), "Battleship",
              sf::Style::Titlebar | sf::Style::Close),
      mFont(),
      mGameSettings(),
      mSceneStack(Scene::Context(
          mWindow, mFont, mSevenSegment, mGameSettings, mBackground,
          mGameBackground, mGreenLed, mRedLed, mYellowLed, mGrille, mShip, mHit,
          mMiss, mConfirm, mExplode, mSplash, mMainMenuMusic, mGameSceneMusic,
          mVictoryMusic, mThreeStars, mMedal)),
      mFpsCounter(),
      mFpsTime(sf::Time::Zero) {
    mWindow.setFramerateLimit(120);

    if (!mFont.loadFromFile("res/fonts/ARCADE_N.TTF")) {
        throw std::runtime_error("Could not load font.");
    }

    if (!mSevenSegment.loadFromFile("res/fonts/7 Segment.ttf")) {
        throw std::runtime_error("Could not load font.");
    }

    if (!mBackground.loadFromFile("res/img/title/bg.png",
                                  sf::IntRect(0, 0, 1999, 1123))) {
        throw std::runtime_error("Could not load res/img/title/bg.png");
    }

    if (!mGameBackground.loadFromFile("res/img/platform/metal_bg.png",
                                      sf::IntRect(0, 0, 1999, 1123))) {
        throw std::runtime_error(
            "Could not load res/img/platform/metal_bg.png");
    }

    if (!mGreenLed.loadFromFile("res/img/platform/led_green.png")) {
        throw std::runtime_error(
            "Could not load res/img/platform/led_green.png");
    }

    if (!mRedLed.loadFromFile("res/img/platform/led_red.png")) {
        throw std::runtime_error("Could not load res/img/platform/led_red.png");
    }

    if (!mYellowLed.loadFromFile("res/img/platform/led_yellow.png")) {
        throw std::runtime_error(
            "Could not load res/img/platform/led_yellow.png");
    }

    if (!mGrille.loadFromFile("res/img/platform/grille.png")) {
        throw std::runtime_error("Could not load res/img/platform/grille.png");
    }

    if (!mShip.loadFromFile("res/img/platform/ship.png")) {
        throw std::runtime_error("Could not load res/img/platform/ship.png");
    }

    if (!mHit.loadFromFile("res/img/platform/hit.png")) {
        throw std::runtime_error("Could not load res/img/platform/hit.png");
    }

    if (!mMiss.loadFromFile("res/img/platform/miss.png")) {
        throw std::runtime_error("Could not load res/img/platform/miss.png");
    }

    if (!mConfirm.loadFromFile("res/audio/sfx/confirm.ogg")) {
        throw std::runtime_error("Could not load res/audio/sfx/confirm.ogg");
    }

    if (!mExplode.loadFromFile("res/audio/sfx/explode.ogg")) {
        throw std::runtime_error("Could not load res/audio/sfx/explode.ogg");
    }

    if (!mSplash.loadFromFile("res/audio/sfx/splash.ogg")) {
        throw std::runtime_error("Could not load res/audio/sfx/splash.ogg");
    }

    if (!mThreeStars.loadFromFile("res/img/victory/3stars.png")) {
        throw std::runtime_error("Could not load res/img/victory/3stars.png");
    }

    if (!mMedal.loadFromFile("res/img/victory/medal.png")) {
        throw std::runtime_error("Could not load res/img/victory/medal.png");
    }

    /* if(!mConfirm.loadFromFile("res/audio/sfx/confirm.ogg")){
        throw std::runtime_error("Could not load res/audio/confirm.ogg");
    };

    if(!mSplash.loadFromFile("res/audio/sfx/splash.ogg")){
        throw std::runtime_error("Could not load res/audio/splash.ogg");
    };

    if(!mExplode.loadFromFile("res/audio/sfx/explode.ogg")){
        throw std::runtime_error("Could not load res/audio/explode.ogg");
    }; */

    if (!mMainMenuMusic.openFromFile("res/audio/main.ogg")) {
        throw std::runtime_error("Could not load res/audio/main.ogg");
    };

    if (!mGameSceneMusic.openFromFile("res/audio/game1.ogg")) {
        throw std::runtime_error("Could not load res/audio/game1.ogg");
    }

    if (!mVictoryMusic.openFromFile("res/audio/victory.ogg")) {
        throw std::runtime_error("Could not load res/audio/victory.ogg");
    }

    mGameSettings.setBoardSize(5, 5);
    mGameSettings.setNumberOfShips(5);

    registerScenes();
    mSceneStack.pushScene(Scene::ID::MainMenu);

    mFpsCounter.setFont(mFont);
    mFpsCounter.setCharacterSize(10);
    mFpsCounter.setString("INIT");
    mFpsCounter.setPosition(0, 0);
    mFpsCounter.setFillColor(sf::Color::Green);
}

void Engine::start() {
    sf::Clock clock;
    while (mWindow.isOpen()) {
        sf::Time dt = clock.restart();

        input();
        update(dt);
        draw();

        if (mSceneStack.isEmpty()) {
            mWindow.close();
        }
    }
}

void Engine::registerScenes() {
    mSceneStack.registerScene<MainMenuScene>(Scene::ID::MainMenu);
    mSceneStack.registerScene<GameScene>(Scene::ID::Game);
    mSceneStack.registerScene<SettingsScene>(Scene::ID::Settings);
    mSceneStack.registerScene<PauseScene>(Scene::ID::Pause);
}

void Engine::input() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        mSceneStack.handleEvent(event);

        if (event.type == sf::Event::Closed) {
            mSceneStack.clearScenes();
            mWindow.close();
        }
    }

    // realtime handling
    // if (windowFocus) {

    // }
}

void Engine::update(sf::Time deltaTime) {
    mSceneStack.update(deltaTime);

    mFpsTime += deltaTime;
    if (mFpsTime.asSeconds() > 1) {
        mFpsCounter.setString(std::to_string(1 / deltaTime.asSeconds()));
        mFpsTime = sf::Time::Zero;
    }
}

void Engine::draw() {
    mWindow.clear();

    mSceneStack.draw();

    mWindow.draw(mFpsCounter);

    mWindow.display();
}