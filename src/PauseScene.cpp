#include "PauseScene.h"

PauseScene::PauseScene(SceneStack& stack, Context& context)
    : Scene(stack, context),
      mPauseText("Paused", context.font),
      mExitButton("Exit", context.font) {
    mPauseText.setPosition(100, 100);

    mExitButton.setPosition(100, 450);
    mExitButton.setSize(300, 50);
}

PauseScene::~PauseScene() {}

bool PauseScene::input(const sf::Event& e) {
    mExitButton.handleInput(e);
    return true;
}

void PauseScene::draw() {
    getContext().window.draw(mPauseText);
    getContext().window.draw(mExitButton);
}

bool PauseScene::update(sf::Time deltaTime) {
    mExitButton.update(deltaTime);
    return true;
}