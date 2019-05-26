#include "GameScene.h"
#include <SFML/Audio.hpp>
#include <cmath>
#include <iostream>
#include "Board.h"
#include "Command.h"

GameScene::GameScene(SceneStack& stack, Context& context)
    : Scene(stack, context),
      currentGameState(context.gameSettings),
      mWindow(context.window),
      mGameBackgroundSprite(context.gameBackground),
      mPanelSprite(context.panel),
      mVictory("VICTORY!", context.font),
      mPlayerWin("PLAYER", context.font),
      mTurns("TURNS", context.font),
      mShipsLeft("SHIPS LEFT", context.font),
      mTime("TIME", context.font),
      mMainMenu("Return to Main Menu", context.font),
      mThreeStars(context.threeStars),
      mMedals{sf::Sprite(context.medal), sf::Sprite(context.medal)},
      mMedalBounceTime(sf::Time::Zero),
      mMedalBounceSpeed(5),
      mGameSceneMusic(context.gameSceneMusic),
      mVictoryMusic(context.victoryMusic),
      mPreparationButtons{Button("CONTINUE", context.font),
                          Button("CONTINUE", context.font)},
      mActionTime(sf::Time::Zero),
      mTransition("", context.font),
      mTransitionSubtitle("", context.font) {
    getContext().mainMenuMusic.stop();

    sf::Vector2f windowSize(context.window.getSize().x,
                            context.window.getSize().y);

    for (int i = 0; i < 2; i++) {
        mPreparationButtons[i].setCharacterSize(20);
        mPreparationButtons[i].setSize(300, 30);
        mPreparationButtons[i].setPosition(
            windowSize.x / 2 -
                mPreparationButtons[i].getGlobalBounds().width / 2,
            500);
        mPreparationButtons[i].onClickCommand.reset(
            new GameCommands::ChangeGameState(currentGameState,
                                              GameState::Phase::Preparation));
    }

    mTransition.setCharacterSize(65);
    mTransition.setString("PLAYER 1");
    mTransition.setPosition(
        windowSize.x / 2 - mTransition.getGlobalBounds().width / 2, 200);

    mTransitionSubtitle.setCharacterSize(20);
    mTransitionSubtitle.setString("TURN TO PLACE SHIPS.\nPLAYER 2 LOOK AWAY.");
    mTransitionSubtitle.setPosition(
        windowSize.x / 2 - mTransitionSubtitle.getGlobalBounds().width / 2,
        300);

    mGameBackgroundSprite.setOrigin(580, 386);
    mGameBackgroundSprite.setPosition(512, 384);
    mGameBackgroundSprite.setScale(1, 1);
    mGameBackgroundSprite.setColor(sf::Color(25, 25, 25));

    mPanelSprite.setPosition(798, 520);
    mPanelSprite.setScale(0.18f, 0.18f);

    mVictory.setCharacterSize(80);

    mBackground.setPosition(0, 0);
    mBackground.setSize(windowSize);
    mBackground.setFillColor(sf::Color::Black);

    mVictory.setPosition(
        windowSize.x / 2 - mVictory.getGlobalBounds().width / 2, 180);

    mPlayerWin.setCharacterSize(65);

    mTurns.setCharacterSize(25);
    mShipsLeft.setCharacterSize(25);
    mTime.setCharacterSize(25);

    mMainMenu.setCharacterSize(20);
    mMainMenu.setSize(425, 30);
    mMainMenu.setPosition(
        windowSize.x / 2 - mMainMenu.getGlobalBounds().width / 2, 625);
    mMainMenu.onClickCommand.reset(new SceneCommand::ReturnToMainMenu(*this));

    mThreeStars.setPosition(
        windowSize.x / 2 - mThreeStars.getGlobalBounds().width / 2, 50);
    mMedals[0].setPosition(50, 180);
    mMedals[1].setPosition(1024 - 50 - mMedals[1].getGlobalBounds().width, 180);

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

GameScene::~GameScene() {
    getContext().gameSceneMusic.stop();
    getContext().victoryMusic.stop();
}

bool GameScene::input(const sf::Event& e) {
    switch (e.type) {
        case sf::Event::KeyReleased: {
            if (e.key.code == sf::Keyboard::Escape) {
                if (currentGameState.currentPhase !=
                    GameState::Phase::Victory) {
                    requestScenePush(Scene::ID::Pause);
                } else {
                    requestSceneClear();
                    requestScenePush(Scene::ID::MainMenu);
                }
            }
        }
        default:
            break;
    }
    if (currentGameState.currentPhase == GameState::Phase::Victory) {
        mMainMenu.handleInput(e);
    } else if (currentGameState.currentPhase == GameState::Phase::Transition) {
        mPreparationButtons[currentGameState.getPlayer()].handleInput(e);
    } else if (currentGameState.currentPhase != GameState::Phase::Victory) {
        playerBoards[currentGameState.getPlayer()]->input(e);
    }
    return true;
}

void GameScene::draw() {
    mWindow.draw(mBackground);

    if (currentGameState.currentPhase == GameState::Phase::Transition) {
        mWindow.draw(mPreparationButtons[currentGameState.getPlayer()]);
        mWindow.draw(mTransition);
        mWindow.draw(mTransitionSubtitle);
        mWindow.draw(mThreeStars);
    } else if (currentGameState.currentPhase != GameState::Phase::Victory) {
        mWindow.draw(mGameBackgroundSprite);
        mWindow.draw(mPanelSprite);
        mWindow.draw(*playerBoards[currentGameState.getPlayer()]);
    } else if (currentGameState.currentPhase == GameState::Phase::Victory) {
        mWindow.draw(mVictory);
        mWindow.draw(mPlayerWin);
        mWindow.draw(mTurns);
        mWindow.draw(mShipsLeft);
        mWindow.draw(mTime);
        mWindow.draw(mMainMenu);
        mWindow.draw(mThreeStars);
        mWindow.draw(mMedals[0]);
        mWindow.draw(mMedals[1]);
    }
}

bool GameScene::update(sf::Time deltaTime) {
    if (currentGameState.currentPhase != GameState::Phase::Victory) {
        for (auto& board : playerBoards) {
            board->update(deltaTime);
        }
    }
    // std::cout << "PLAYER " << currentGameState.getPlayer() << "\n";

    sf::Vector2f windowSize(getContext().window.getSize().x,
                            getContext().window.getSize().y);
    if (currentGameState.currentPhase == GameState::Phase::Transition) {
        mPreparationButtons[0].update(deltaTime);
        mPreparationButtons[1].update(deltaTime);
    } else if (currentGameState.currentPhase == GameState::Phase::Preparation) {
        if (currentGameState.getTurn() == 0) {
            if (playerBoards[currentGameState.getPlayer()]
                    ->getNumberOfShips() >= currentGameState.maxShips) {
                currentGameState.incrementTurn();
                currentGameState.currentPhase = GameState::Phase::Transition;

                mTransition.setString("PLAYER 2");
                mTransition.setPosition(
                    windowSize.x / 2 - mTransition.getGlobalBounds().width / 2,
                    200);

                mTransitionSubtitle.setString(
                    "TURN TO PLACE SHIPS.\nPLAYER 1 LOOK AWAY.");
                mTransitionSubtitle.setPosition(
                    windowSize.x / 2 -
                        mTransitionSubtitle.getGlobalBounds().width / 2,
                    300);
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

            std::string playerWinText = "PLAYER " + std::to_string(winner + 1);
            mPlayerWin.setString(playerWinText);
            mPlayerWin.setPosition(
                windowSize.x / 2 - mPlayerWin.getGlobalBounds().width / 2, 270);

            std::string turnsText = "IN ";
            if (currentGameState.getTurn() == 1) {
                turnsText +=
                    std::to_string(currentGameState.getTurn()) + " TURN";
            } else {
                turnsText +=
                    std::to_string(currentGameState.getTurn()) + " TURNS";
            }
            mTurns.setString(turnsText);
            mTurns.setPosition(
                windowSize.x / 2 - mTurns.getGlobalBounds().width / 2, 400);

            std::string shipsLeftText = "WITH ";
            if (currentGameState.numberOfShips[winner] == 1) {
                shipsLeftText +=
                    std::to_string(currentGameState.numberOfShips[winner]) +
                    " SHIP LEFT";
            } else {
                shipsLeftText +=
                    std::to_string(currentGameState.numberOfShips[winner]) +
                    " SHIPS LEFT";
            }
            mShipsLeft.setString(shipsLeftText);
            mShipsLeft.setPosition(
                windowSize.x / 2 - mShipsLeft.getGlobalBounds().width / 2, 460);

            std::string timeString = "TIME: ";
            if (currentGameState.gameTime.asSeconds() < 60) {
                timeString += std::to_string(
                    (int)std::round(currentGameState.gameTime.asSeconds()));
                if ((int)std::round(currentGameState.gameTime.asSeconds()) ==
                    1) {
                    timeString += " second";
                } else {
                    timeString += " seconds";
                }
            } else {
                timeString +=
                    std::to_string((int)currentGameState.gameTime.asSeconds() /
                                   60) +
                    ":" +
                    std::to_string((int)currentGameState.gameTime.asSeconds() %
                                   60);
            }
            mTime.setString(timeString);
            mTime.setPosition(
                windowSize.x / 2 - mTime.getGlobalBounds().width / 2, 520);

            mGameSceneMusic.stop();
            getContext().victoryMusic.play();
        }
    } else if (currentGameState.currentPhase == GameState::Phase::Victory) {
        mMedalBounceTime += deltaTime;
        if (mMedalBounceTime.asSeconds() < 2) {
            for (auto& medal : mMedals) {
                medal.setPosition(
                    medal.getPosition().x,
                    medal.getPosition().y +
                        mMedalBounceSpeed * deltaTime.asSeconds());
            }
        } else {
            mMedalBounceSpeed *= -1;
            mMedalBounceTime = sf::Time::Zero;
        }

        mMainMenu.update(deltaTime);
    }

    victoryBlinkTime += deltaTime;

    if (victoryBlinkTime.asSeconds() > 0.5) {
        if (mVictory.getFillColor() == sf::Color::White) {
            mVictory.setFillColor(sf::Color::Transparent);
        } else {
            mVictory.setFillColor(sf::Color::White);
        }
        victoryBlinkTime = sf::Time::Zero;
    }

    playerWinBlinkTime += deltaTime;

    if (playerWinBlinkTime.asSeconds() > 0.5) {
        if (mPlayerWin.getFillColor() == sf::Color::White) {
            mPlayerWin.setFillColor(sf::Color::Transparent);
        } else {
            mPlayerWin.setFillColor(sf::Color::White);
        }
        playerWinBlinkTime = sf::Time::Zero;
    }
    return true;
}

GameScene::GameState::GameState(GameSettings& gameSettings)
    : maxShips(gameSettings.getNumberOfShips()) {
    numberOfShips[0] = 0;
    numberOfShips[1] = 0;
    turn = 0;
    currentPhase = Phase::Transition;
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