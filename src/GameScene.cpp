#include "GameScene.h"
#include <iostream>

GameScene::GameScene(SceneStack& stack, Context& context)
    : Scene(stack, context),
      mWindow(context.window),
      mTestText("Hello", context.font),
      mPlayerBoards(context.gameSettings) {
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
    return true;
}

void GameScene::draw() {
    // mWindow.draw(mTestText);
    mWindow.draw(mBackground);
    mWindow.draw(mTestText);
}

bool GameScene::update(sf::Time deltaTime) { return true; }

GameScene::PlayerBoards::PlayerBoards(GameSettings& gameSettings)
    : player1(gameSettings.getBoardSize().x,
              std::vector<Board::CellState>(gameSettings.getBoardSize().x)),
      player2(gameSettings.getBoardSize().x,
              std::vector<Board::CellState>(gameSettings.getBoardSize().x)) {
    std::cout<<"Here"<<std::endl;
    for (int i = 0; i < player1.size(); i++) {
        for (int j = 0; j < player1[i].size(); j++) {
            std::cout << i << ", " << j << std::endl;
        }
    }
}