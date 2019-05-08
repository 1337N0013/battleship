#include "Engine.h"
#include "Scene.h"
#include <iostream>

using std::cout;

Engine::Engine() {
    m_window.create(sf::VideoMode(windowWidth, windowHeight), "Battleship");
    m_window.setFramerateLimit(60);

    if (!font.loadFromFile("res/fonts/ProFont For Powerline.ttf")) {
        throw std::runtime_error("Could not load font.");
    }
    mainMenuScene.reset(new MainMenuScene(m_window, windowWidth, windowHeight, font));

    windowFocus = false;
}

void Engine::start() {
    sf::Clock clock;

    mainMenuScene->start();
    while (m_window.isOpen()) {
        sf::Time dt = clock.restart();

        input();
        update(dt);
        draw();
    }
}

void Engine::input() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        mainMenuScene->input(event);
    }

    // realtime handling
    // if (windowFocus) {

    // }
}

void Engine::update(sf::Time deltaTime) {
    mainMenuScene->update(deltaTime);
}

void Engine::draw() {
    mainMenuScene->draw();
}