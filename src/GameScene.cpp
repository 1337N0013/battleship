#include "GameScene.h"

GameScene::GameScene(SceneStack& stack, Context context) : Scene(stack, context), mTestText("Hello", context.font) {
    mTestText.setPosition(100, 100);
}

GameScene::~GameScene() {}

bool GameScene::input(const sf::Event& e) {
    if (e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::Escape) {
        requestScenePop();
    }
    return true;
}

void GameScene::draw() {
    // mWindow.draw(mTestText);
    getContext().window.draw(mTestText);
}

bool GameScene::update(sf::Time deltaTime) {
    return true;
}