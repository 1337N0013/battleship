#include "MainMenuScene.h"
#include "Button.h"

MainMenuScene::MainMenuScene(SceneStack& stack, Context context)
    : Scene(stack, context) {}

MainMenuScene::~MainMenuScene() {}

void MainMenuScene::start() {
    title.setFont(mFont);
    title.setCharacterSize(35);
    title.setString("Battleship");
    title.setPosition(mWindowSize.x / 2 - title.getLocalBounds().width / 2,
                      100);

    btn.create(mWindowSize.x / 2 - 150, mWindowSize.y / 2 - 15, 300, 30,
               std::string("Hello"), mFont);
    btn2.create(0, 0, 100, 100, std::string("yuh"), mFont);
}

bool MainMenuScene::input(const sf::Event& e) {
    switch (e.type) {
        case sf::Event::Closed: {
            mWindow.close();
            return false;
        }
        case sf::Event::KeyPressed: {
            if (e.key.code == sf::Keyboard::Escape) {
                requestScenePop();
            }
            break;
        }
        default:
            break;
    }
    btn.handleInput(e);
    btn2.handleInput(e);
    return true;
}

void MainMenuScene::draw() {
    mWindow.clear(sf::Color::Black);

    mWindow.draw(title);
    mWindow.draw(btn);
    mWindow.draw(btn2);
    mWindow.draw(fpsCounter);

    mWindow.display();
}

bool MainMenuScene::update(sf::Time deltaTime) {
    btn.update(deltaTime);
    btn2.update(deltaTime);
    return true;
}