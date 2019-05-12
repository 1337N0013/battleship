#include "Engine.h"
#include <iostream>
#include "Scene.h"

using std::cout;

Engine::Engine() {
    m_window.create(sf::VideoMode(windowWidth, windowHeight), "Battleship");
    m_window.setFramerateLimit(60);

    if (!font.loadFromFile("res/fonts/ProFont For Powerline.ttf")) {
        throw std::runtime_error("Could not load font.");
    }

    gameContext.reset(new Context(m_window, font));
    mSceneStack.reset(new SceneStack(*gameContext));

    windowFocus = false;
}

void Engine::start() {
    mSceneStack->pushScene(Scene::ID::MainMenu);

    sf::Clock clock;
    while (m_window.isOpen()) {
        sf::Time dt = clock.restart();

        input();
        update(dt);
        draw();

        if (mSceneStack->isEmpty()) {
            m_window.close();
        }
    }
}

void Engine::registerScenes() {
    mSceneStack->registerScene<MainMenuScene>(Scene::ID::MainMenu);
}

void Engine::input() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        mSceneStack->handleEvent(event);
    }

    // realtime handling
    // if (windowFocus) {

    // }
}

void Engine::update(sf::Time deltaTime) {
    mSceneStack->update(deltaTime);
}

void Engine::draw() {
    mSceneStack->draw();
}