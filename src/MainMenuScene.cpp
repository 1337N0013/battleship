#include "MainMenuScene.h"
#include <iostream>
#include "Button.h"

MainMenuScene::MainMenuScene(SceneStack& stack, Context context)
    : Scene(stack, context),
      mFont(context.font),
      mWindow(context.window),
      mWindowSize(mWindow.getSize()),
      playButton(mWindowSize.x / 2 - 150, mWindowSize.y / 2 - 15, 300, 30,
          std::string("Play"), context),
      exitButton(0, 0, 300, 30, std::string("Exit"), context),
      playButtonCommand(*this, Scene::ID::Game),
      exitButtonCommand(*this) {
    exitButton.setPosition(playButton.getPosition().x, playButton.getPosition().y + 50);
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
    playButton.handleInput(e);
    exitButton.handleInput(e);
    return true;
}

void MainMenuScene::draw() {
    mWindow.draw(title);
    mWindow.draw(playButton);
    mWindow.draw(exitButton);
}

bool MainMenuScene::update(sf::Time deltaTime) {
    if (playButton.update(deltaTime)) {
        playButtonCommand.execute();
    }
    if (exitButton.update(deltaTime)) {
        exitButtonCommand.execute();
    }
    return true;
}