#include "GameScene.h"

GameScene::GameScene(SceneStack& stack, Context context) : Scene(stack, context) {}

GameScene::~GameScene() {}

bool GameScene::input(const sf::Event& e) {
    if (e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::Escape) {
        requestScenePop();
    }
    return true;
}

void GameScene::draw() {
    //
}

bool GameScene::update(sf::Time deltaTime) {
    return true;
}