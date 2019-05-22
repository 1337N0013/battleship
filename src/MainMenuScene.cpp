#include "Command.h"
#include "MainMenuScene.h"
#include <iostream>

MainMenuScene::MainMenuScene(SceneStack& stack, Context& context)
    : Scene(stack, context),
      mFont(context.font),
      mWindow(context.window),
      mWindowSize(mWindow.getSize()),
      playButton(mWindowSize.x / 2 - 150, mWindowSize.y / 2 - 15, 300, 30,
                 std::string("Play"), context.font),
      exitButton(0, 0, 300, 30, std::string("Exit"), context.font),
      mSpriteBG(context.background) {
    exitButton.setPosition(playButton.getPosition().x,
                           playButton.getPosition().y + 50);

    title.setFont(mFont);
    title.setCharacterSize(35);
    title.setString("Battleship");
    title.setPosition(mWindowSize.x / 2 - title.getLocalBounds().width / 2,
                      100);

    playButton.onClickCommand.reset(
        new SceneCommand::ChangeScene(*this, Scene::ID::Settings));
    exitButton.onClickCommand.reset(new SceneCommand::RemoveScene(*this));

    mSpriteBG.setPosition(0, 0);
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
    mWindow.draw(mSpriteBG);
    mWindow.draw(title);
    mWindow.draw(playButton);
    mWindow.draw(exitButton);
}

bool MainMenuScene::update(sf::Time deltaTime) {
    playButton.update(deltaTime);
    exitButton.update(deltaTime);
    return true;
}