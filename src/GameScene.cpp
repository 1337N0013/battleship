#include "GameScene.h"

GameScene::GameScene(SceneStack& stack, Context context) : Scene(stack, context), mWindow(context.window), mTestText("Hello", context.font) {
    mBackground.setPosition(0, 0);
    sf::Vector2f windowSize(context.window.getSize().x, context.window.getSize().y);
    mBackground.setSize(windowSize);
    mBackground.setFillColor(sf::Color::Black);
    
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
    mWindow.draw(mBackground);
    mWindow.draw(mTestText);
}

bool GameScene::update(sf::Time deltaTime) {
    return true;
}