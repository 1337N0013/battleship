#include "MainMenuScene.h"
#include <iostream>
#include "Button.h"

MainMenuScene::MainMenuScene(SceneStack& stack, Context context)
    : Scene(stack, context),
      mFont(context.font),
      mWindow(context.window),
      mWindowSize(mWindow.getSize()),
      btn(mWindowSize.x / 2 - 150, mWindowSize.y / 2 - 15, 300, 30,
          std::string("Hello"), mFont),
      btn2(0, 0, 100, 100, std::string("yuh"), mFont) {
    title.setFont(mFont);
    title.setCharacterSize(35);
    title.setString("Battleship");
    title.setPosition(mWindowSize.x / 2 - title.getLocalBounds().width / 2,
                      100);
}

MainMenuScene::~MainMenuScene() {}

bool MainMenuScene::input(const sf::Event& e) {
    switch (e.type) {
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
    mWindow.draw(title);
    mWindow.draw(btn);
    mWindow.draw(btn2);
}

bool MainMenuScene::update(sf::Time deltaTime) {
    btn.update(deltaTime);
    btn2.update(deltaTime);
    return true;
}