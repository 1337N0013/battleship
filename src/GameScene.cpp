#include "GameScene.h"
#include <SFML/Audio.hpp>
#include <iostream>
#include "Board.h"
#include "Command.h"
#include <cmath>

GameScene::GameScene(SceneStack& stack, Context& context)
    : Scene(stack, context),
      currentGameState(context.gameSettings),
      mWindow(context.window),
      mVictory("VICTORY!", context.font),
      mStats("STATS", context.font),
      mMainMenu("Return to Main Menu", context.font),
      mGameSceneMusic(context.gameSceneMusic),
      mVictoryMusic(context.victoryMusic) {
    getContext().mainMenuMusic.stop();

    sf::Vector2f windowSize(context.window.getSize().x,
                            context.window.getSize().y);

    mVictory.setPosition(
        windowSize.x / 2 - mVictory.getGlobalBounds().width / 2, 200);

    mStats.setCharacterSize(20);

    mMainMenu.setCharacterSize(20);
    mMainMenu.setSize(425, 30);
    mMainMenu.setPosition(
        windowSize.x / 2 - mMainMenu.getGlobalBounds().width / 2, 400);
    mMainMenu.onClickCommand.reset(new SceneCommand::ReturnToMainMenu(*this));

    mBackground.setPosition(0, 0);
    mBackground.setSize(windowSize);
    mBackground.setFillColor(sf::Color::Black);

    mGameSceneMusic.setPosition(0, 1, 10);
    mGameSceneMusic.setPitch(1);
    mGameSceneMusic.setVolume(15);
    mGameSceneMusic.setLoop(true);
    mGameSceneMusic.play();

    mVictoryMusic.setPosition(0, 1, 10);
    mVictoryMusic.setPitch(1);
    mVictoryMusic.setVolume(15);
    mVictoryMusic.setLoop(true);

    playerBoards[0].reset(new Board(currentGameState, context));
    playerBoards[1].reset(new Board(currentGameState, context));
}

GameScene::~GameScene() { getContext().victoryMusic.stop(); }

bool GameScene::input(const sf::Event& e) {
    switch (e.type) {
        case sf::Event::KeyReleased: {
            if (e.key.code == sf::Keyboard::Escape && currentGameState.currentPhase != GameState::Phase::Victory) {
                requestScenePush(Scene::ID::Pause);
            }
        }
        default:
            break;
    }
    if (currentGameState.currentPhase != GameState::Phase::Victory) {
        playerBoards[currentGameState.getPlayer()]->input(e);
    } else {
        mMainMenu.handleInput(e);
    }
    return true;
}

void GameScene::draw() {
    mWindow.draw(mBackground);
    if (currentGameState.currentPhase != GameState::Phase::Victory) {
        mWindow.draw(*playerBoards[currentGameState.getPlayer()]);
    } else {
        mWindow.draw(mVictory);
        mWindow.draw(mStats);
        mWindow.draw(mMainMenu);
    }
}

bool GameScene::update(sf::Time deltaTime) {
    if (currentGameState.currentPhase != GameState::Phase::Victory) {
        playerBoards[currentGameState.getPlayer()]->update(deltaTime);
    }
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
        currentGameState.gameTime += deltaTime;
        int winner;
        if (playerBoards[0]->getNumberOfShips() == 0) {
            winner = 1;
        } else if (playerBoards[1]->getNumberOfShips() == 0) {
            winner = 0;
        } else {
            winner = -1;
        }
        if (winner != -1) {
            currentGameState.currentPhase = GameState::Phase::Victory;
            std::cout << "PLAYER " << winner + 1 << " WINS\n";
            std::cout << "VICTORY PHASE\n";

            std::string timeString = "TIME: ";
            if (currentGameState.gameTime.asSeconds() < 60) {
                timeString += std::to_string((int)std::round(
                                  currentGameState.gameTime.asSeconds())) +
                              " seconds";
            } else {
                timeString +=
                    std::to_string((int)currentGameState.gameTime.asSeconds() /
                                   60) +
                    ":" +
                    std::to_string((int)currentGameState.gameTime.asSeconds() %
                                   60);
            }
            
            mStats.setString(timeString);
            sf::Vector2f windowSize(getContext().window.getSize().x,
                                    getContext().window.getSize().y);
            mStats.setPosition(
                windowSize.x / 2 - mStats.getGlobalBounds().width / 2, 300);
            
            mGameSceneMusic.stop();
            getContext().victoryMusic.play();
        }
    } else if (currentGameState.currentPhase == GameState::Phase::Victory) {
        mMainMenu.update(deltaTime);
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