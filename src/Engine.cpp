#include "Engine.h"
#include <iostream>
#include "MainMenuScene.h"
#include "Scene.h"

using std::cout;

Engine::Engine()
    : mWindow(sf::VideoMode(windowWidth, windowHeight), "Battleship"),
      mFont(),
      mSceneStack(Scene::Context(mWindow, mFont)),
      mFpsCounter(),
      mFpsTime(sf::Time::Zero) {
    mWindow.setFramerateLimit(120);

    if (!mFont.loadFromFile("res/fonts/ProFont For Powerline.ttf")) {
        throw std::runtime_error("Could not load font.");
    }

    registerScenes();
    mSceneStack.pushScene(Scene::ID::MainMenu);

    mFpsCounter.setFont(mFont);
    mFpsCounter.setCharacterSize(16);
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
}

void Engine::input() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        mSceneStack.handleEvent(event);

        if (event.type == sf::Event::Closed) {
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