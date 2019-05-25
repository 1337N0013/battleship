#include "Command.h"
#include "PauseScene.h"

PauseScene::PauseScene(SceneStack& stack, Context& context)
    : Scene(stack, context),
      mPauseText("Paused", context.font),
      mContinueButton("Continue", context.font),
      mExitButton("Quit", context.font) {
    mBackground.setSize(sf::Vector2f(context.window.getSize().x, context.window.getSize().y));
    mBackground.setFillColor(sf::Color(0, 0, 0, 200));

    mPauseText.setCharacterSize(20);
    mPauseText.setPosition(100, 100);

    sf::Vector2f buttonSize(300, 30);

    mExitButton.setCharacterSize(20);
    mExitButton.setPosition(100, context.window.getSize().y - 100 - 30);
    mExitButton.setSize(buttonSize);
    mExitButton.onClickCommand.reset(new SceneCommand::ReturnToMainMenu(*this));

    mContinueButton.setCharacterSize(20);
    mContinueButton.setPosition(100, mExitButton.getPosition().y-50);
    mContinueButton.setSize(buttonSize);
    mContinueButton.onClickCommand.reset(new SceneCommand::RemoveScene(*this));
}

PauseScene::~PauseScene() {}

bool PauseScene::input(const sf::Event& e) {
    switch(e.type) {
        case sf::Event::KeyReleased: {
            if (e.key.code == sf::Keyboard::Escape) {
                requestScenePop();
            }
            break;
        }
        default:
            break;
    }
    mContinueButton.handleInput(e);
    mExitButton.handleInput(e);
    return false;
}

void PauseScene::draw() {
    getContext().window.draw(mBackground);
    getContext().window.draw(mPauseText);
    getContext().window.draw(mContinueButton);
    getContext().window.draw(mExitButton);
}

bool PauseScene::update(sf::Time deltaTime) {
    mContinueButton.update(deltaTime);
    mExitButton.update(deltaTime);
    return false;
}