#include "Engine.h"
#include <iostream>

using std::cout;

Engine::Engine() {
    m_window.create(sf::VideoMode(windowWidth, windowHeight), "Battleship");
    m_window.setFramerateLimit(60);

    if (!font.loadFromFile(FONT_PATH)) {
        cout << FONT_FAILURE;
    }
    fpsCounter.setFont(font);
    fpsCounter.setCharacterSize(16);
    fpsCounter.setString("INIT");
    fpsCounter.setPosition(0, 0);
    fpsCounter.setFillColor(sf::Color::Green);
    fpsTime = sf::Time::Zero;
    title.setFont(font);
    title.setCharacterSize(35);
    title.setString("Battleship");
    title.setPosition(windowWidth / 2 - title.getLocalBounds().width / 2, 100);

    btn.create(windowWidth / 2 - 150, windowHeight / 2 - 15, 300, 30,
               std::string("Hello"));
    btn2.create(0, 0, 100, 100, std::string("yuh"));

    windowFocus = false;
}

void Engine::start() {
    sf::Clock clock;

    while (m_window.isOpen()) {
        sf::Time dt = clock.restart();

        input();
        update(dt);
        draw();
    }
}

void Engine::input() {
    // event handling
    sf::Event event;
    while (m_window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed: {
                m_window.close();
                break;
            }
            case sf::Event::KeyPressed: {
                if (event.key.code == sf::Keyboard::Escape) {
                    m_window.close();
                }
                break;
            }
            default:
                break;
        }
        btn.handleInput(event);
        btn2.handleInput(event);
    }

    // realtime handling
    // if (windowFocus) {

    // }
}

void Engine::update(sf::Time deltaTime) {
    fpsTime += deltaTime;
    if (fpsTime.asSeconds() > 1) {
        fpsCounter.setString(std::to_string(1 / deltaTime.asSeconds()));
        fpsTime = sf::Time::Zero;
    }

    btn.update(deltaTime);
    btn2.update(deltaTime);
}

void Engine::draw() {
    m_window.clear(sf::Color::Black);

    m_window.draw(title);
    m_window.draw(btn);
    m_window.draw(btn2);
    m_window.draw(fpsCounter);

    m_window.display();
}