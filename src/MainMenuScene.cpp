#include "MainMenuScene.h"
#include "Button.h"

MainMenuScene::MainMenuScene(SceneStack& stack, Context context) : Scene(stack, context) {}

MainMenuScene::~MainMenuScene() {}

void MainMenuScene::start() {
    fpsCounter.setFont(mFont);
    fpsCounter.setCharacterSize(16);
    fpsCounter.setString("INIT");
    fpsCounter.setPosition(0, 0);
    fpsCounter.setFillColor(sf::Color::Green);

    title.setFont(mFont);
    title.setCharacterSize(35);
    title.setString("Battleship");
    title.setPosition(mWindowSize.x / 2 - title.getLocalBounds().width / 2, 100);

    btn.create(mWindowSize.x / 2 - 150, mWindowSize.y / 2 - 15, 300, 30,
               std::string("Hello"), mFont);
    btn2.create(0, 0, 100, 100, std::string("yuh"), mFont);
}

void MainMenuScene::input(const sf::Event& e) {
    switch (e.type) {
        case sf::Event::Closed: {
            mWindow.close();
            break;
        }
        case sf::Event::KeyPressed: {
            if (e.key.code == sf::Keyboard::Escape) {
                mWindow.close();
            }
            break;
        }
        default:
            break;
    }
    btn.handleInput(e);
    btn2.handleInput(e);
}

void MainMenuScene::draw() {
    mWindow.clear(sf::Color::Black);

    mWindow.draw(title);
    mWindow.draw(btn);
    mWindow.draw(btn2);
    mWindow.draw(fpsCounter);

    mWindow.display();
}

void MainMenuScene::update(sf::Time deltaTime) {
    fpsTime += deltaTime;
    if (fpsTime.asSeconds() > 1) {
        fpsCounter.setString(std::to_string(1 / deltaTime.asSeconds()));
        fpsTime = sf::Time::Zero;
    }

    btn.update(deltaTime);
    btn2.update(deltaTime);
}