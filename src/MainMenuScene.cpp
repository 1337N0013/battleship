#include "Command.h"
#include "MainMenuScene.h"
#include <iostream>

MainMenuScene::MainMenuScene(SceneStack& stack, Context& context)
    : Scene(stack, context),
      mFont(context.font),
      mWindow(context.window),
      mWindowSize(mWindow.getSize()),
      playButton(mWindowSize.x / 2 - 150, mWindowSize.y / 2 + 165, 300, 30,
                 std::string("Play"), context.font),
      exitButton(0, 0, 300, 30, std::string("Exit"), context.font),
      mBackgroundSprite(context.background),
      mMainMenuMusic(context.mainMenuMusic) {
    exitButton.setPosition(playButton.getPosition().x,
                           playButton.getPosition().y + 50);

    title.setFont(mFont);
    title.setCharacterSize(35);
    title.setString("INSERT COIN: 0");
    title.setPosition(mWindowSize.x / 2 - title.getLocalBounds().width / 2,
                      100);
    titleBlinkTime = sf::Time::Zero;

    playButton.onClickCommand.reset(
        new SceneCommand::ChangeScene(*this, Scene::ID::Settings));
    exitButton.onClickCommand.reset(new SceneCommand::RemoveScene(*this));

    mBackgroundSprite.setOrigin(999.5f, 561.5f);
    mBackgroundSprite.setPosition(512, 384);
    mBackgroundSprite.setScale(0.69f, 0.69f);

    mMainMenuMusic.setPosition(0, 1, 10);
    mMainMenuMusic.setPitch(1);
    mMainMenuMusic.setVolume(15);
    mMainMenuMusic.setLoop(true);
    mMainMenuMusic.play();    
}

MainMenuScene::~MainMenuScene() {
    mMainMenuMusic.stop();
}

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
    mWindow.draw(mBackgroundSprite);
    mWindow.draw(title);
    mWindow.draw(playButton);
    mWindow.draw(exitButton);
}

bool MainMenuScene::update(sf::Time deltaTime) {
    playButton.update(deltaTime);
    exitButton.update(deltaTime);
    titleBlinkTime += deltaTime;
    
    if(titleBlinkTime.asSeconds() > 0.5)
    {
        if (title.getFillColor() == sf::Color::White)
        {
            title.setFillColor(sf::Color::Transparent);
        }
        else
        {
            title.setFillColor(sf::Color::White);
        }
        titleBlinkTime = sf::Time::Zero;
    }
    return true;
}