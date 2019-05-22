#include "Board.h"
#include "GameScene.h"
#include <iostream>

GameScene::GameScene(SceneStack& stack, Context& context)
    : Scene(stack, context),
      mWindow(context.window),
      mTestText("Hello", context.font),
      player1Board(new Board(currentGameState, context)),
      player2Board(new Board(currentGameState, context)) {
    mBackground.setPosition(0, 0);
    sf::Vector2f windowSize(context.window.getSize().x,
                            context.window.getSize().y);
    mBackground.setSize(windowSize);
    mBackground.setFillColor(sf::Color::Black);

    mTestText.setPosition(100, 100);
}

GameScene::~GameScene() {}

bool GameScene::input(const sf::Event& e) {
    switch (e.type) {
        case sf::Event::KeyReleased: {
            if (e.key.code == sf::Keyboard::Escape) {
                requestScenePush(Scene::ID::Pause);
            }
        }
        default:
            break;
    }
    player1Board->input(e);
    return true;
}

void GameScene::draw() {
    mWindow.draw(mBackground);
    mWindow.draw(mTestText);
    mWindow.draw(*player1Board);
}

bool GameScene::update(sf::Time deltaTime) {
    player1Board->update(deltaTime);
    return true;
}

GameScene::GameState::GameState() {
    numberOfShips[0] = 0;
    numberOfShips[1] = 0;
    turn = 0;
    currentPhase = Phase::Preparation;
}