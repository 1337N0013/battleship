#include "GameScene.h"
#include <SFML/Audio.hpp>
#include <iostream>
#include "Board.h"

GameScene::GameScene(SceneStack& stack, Context& context)
    : Scene(stack, context),
      mWindow(context.window),
      mTestText("Hello", context.font),
      currentGameState(context.gameSettings),
      mGameSceneMusic(context.gameSceneMusic) {
    getContext().mainMenuMusic.stop();

    mBackground.setPosition(0, 0);
    sf::Vector2f windowSize(context.window.getSize().x,
                            context.window.getSize().y);
    mBackground.setSize(windowSize);
    mBackground.setFillColor(sf::Color::Black);

    mGameSceneMusic.setPosition(0, 1, 10);
    mGameSceneMusic.setPitch(1);
    mGameSceneMusic.setVolume(15);
    mGameSceneMusic.setLoop(true);
    mGameSceneMusic.play();

    mTestText.setPosition(100, 100);

    playerBoards[0].reset(new Board(currentGameState, context));
    playerBoards[1].reset(new Board(currentGameState, context));
}

GameScene::~GameScene() { mGameSceneMusic.stop(); }

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
    playerBoards[currentGameState.getPlayer()]->input(e);
    return true;
}

void GameScene::draw() {
    mWindow.draw(mBackground);
    mWindow.draw(mTestText);
    mWindow.draw(*playerBoards[currentGameState.getPlayer()]);
}

bool GameScene::update(sf::Time deltaTime) {
    playerBoards[currentGameState.getPlayer()]->update(deltaTime);
    // std::cout << "PLAYER " << currentGameState.getPlayer() << "\n";

    if (currentGameState.currentPhase == GameState::Phase::Preparation) {
        if (currentGameState.getTurn() == 0) {
            if (playerBoards[currentGameState.getPlayer()]
                    ->getNumberOfShips() >= currentGameState.maxShips) {
                currentGameState.incrementTurn();
            }
        } else {
            if (playerBoards[currentGameState.getPlayer()]
                    ->getNumberOfShips() >= currentGameState.maxShips) {
                currentGameState.currentPhase = GameState::Phase::Battle;
                currentGameState.resetTurnsToZero();

                // reset all buttons to attack
                for (int i = 0; i < 2; i++) {
                    playerBoards[i]->setBattlePhase();
                }
                std::cout << "in battle phase\n";
            }
        }
    } else if (currentGameState.currentPhase == GameState::Phase::Battle) {
        int winner;
        if (playerBoards[0]->getNumberOfShips() == 0) {
            winner = 1;
        } else if (playerBoards[1]->getNumberOfShips() == 0) {
            winner = 0;
        } else {
            winner = -1;
        }
        if (winner != -1) {
            std::cout << "PLAYER " << winner + 1 << " WINS\n";
            requestSceneClear();
            requestScenePush(Scene::ID::MainMenu);
        }
    }

    return true;
}

GameScene::GameState::GameState(GameSettings& gameSettings)
    : maxShips(gameSettings.getNumberOfShips()) {
    numberOfShips[0] = 0;
    numberOfShips[1] = 0;
    turn = 0;
    currentPhase = Phase::Preparation;
}

unsigned int GameScene::GameState::getTurn() { return turn; }
unsigned int GameScene::GameState::getPlayer() {
    if (currentPhase == GameScene::GameState::Phase::Preparation) {
        return turn % 2;
    } else {
        return !(turn % 2);
    }
}
void GameScene::GameState::incrementTurn() { turn++; }

void GameScene::GameState::resetTurnsToZero() { turn = 0; }