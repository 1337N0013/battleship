#include "GameScene.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "Board.h"
#include "Command.h"

GameScene::GameScene(SceneStack& stack, Context& context)
    : Scene(stack, context),
      currentGameState(context.gameSettings),
      mWindow(context.window),
      mGameBackgroundSprite(context.gameBackground),
      mGreenLed(context.greenLed),
      mRedLed(context.redLed),
      mYellowLed(context.yellowLed),
      mGrille(context.grille),
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
      mTransitionSubtitle("", context.font),
      // JOSIAH AND THOMAS WERE HERE
      mWhosTurnText("PLAYER", context.sevenSegment),
      mGameClockText("TIME:", context.sevenSegment),
      mTurnCounterText("TURN:", context.sevenSegment),
      mYourShipsText("PLAYER 1\n SHIPS:", context.sevenSegment),
      mEnemyShipsText("PLAYER 2\n SHIPS:", context.sevenSegment),
      mWhosTurnValueText("", context.sevenSegment),
      mGameClockValueText("", context.sevenSegment),
      mTurnCounterValueText("", context.sevenSegment),
      mYourShipsValueText("", context.sevenSegment),
      mEnemyShipsValueText("", context.sevenSegment),
      mConfirmSound(mConfirmSoundBuffer) {
    getContext().mainMenuMusic.stop();

    mConfirmSoundBuffer.loadFromFile("res/audio/sfx/confirm.ogg");
    mConfirmSound.setPitch(1.2);

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

    mGreenLed.setPosition(770, 535);
    mGreenLed.setScale(0.2f, 0.2f);

    mYellowLed.setPosition(845, 535);
    mYellowLed.setScale(0.2f, 0.2f);

    mRedLed.setPosition(920, 535);
    mRedLed.setScale(0.2f, 0.2f);

    mGrille.setPosition(772, 615);
    mGrille.setScale(0.4f, 0.4f);
    mGrille.setColor(sf::Color(160, 160, 160));

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

    // JOSIAH AND THOMAS WERE HERE
    mWhosTurn.setSize(sf::Vector2f(210, 60));
    mWhosTurn.setPosition(770, 40);
    mWhosTurn.setFillColor(sf::Color::Black);
    mWhosTurn.setOutlineColor(sf::Color(114, 114, 114));
    mWhosTurn.setOutlineThickness(3);

    mWhosTurnText.setCharacterSize(45);
    mWhosTurnText.setPosition(780, 40);
    mWhosTurnText.setFillColor(sf::Color::Green);
    mWhosTurnText.setStyle(sf::Text::Bold);

    mWhosTurnValueText.setCharacterSize(45);
    mWhosTurnValueText.setPosition(940, 40);
    mWhosTurnValueText.setFillColor(sf::Color::Green);
    mWhosTurnValueText.setStyle(sf::Text::Bold);

    // JOSIAH AND THOMAS WERE STILL HERE
    mGameClock.setSize(sf::Vector2f(210, 60));
    mGameClock.setPosition(770, 120);
    mGameClock.setFillColor(sf::Color::Black);
    mGameClock.setOutlineColor(sf::Color(114, 114, 114));
    mGameClock.setOutlineThickness(3);

    mGameClockText.setCharacterSize(45);
    mGameClockText.setPosition(770, 120);
    mGameClockText.setFillColor(sf::Color::Green);
    mGameClockText.setStyle(sf::Text::Bold);

    mGameClockValueText.setCharacterSize(45);
    mGameClockValueText.setPosition(870, 120);
    mGameClockValueText.setFillColor(sf::Color::Green);
    mGameClockValueText.setStyle(sf::Text::Bold);

    // JOSIAH AND THOMAS WERE STILL HERE
    mTurnCounter.setSize(sf::Vector2f(130, 130));
    mTurnCounter.setPosition(812, 200);
    mTurnCounter.setFillColor(sf::Color::Black);
    mTurnCounter.setOutlineColor(sf::Color(114, 114, 114));
    mTurnCounter.setOutlineThickness(3);

    mTurnCounterText.setCharacterSize(45);
    mTurnCounterText.setPosition(820, 200);
    mTurnCounterText.setFillColor(sf::Color::Green);
    mTurnCounterText.setStyle(sf::Text::Bold);

    mTurnCounterValueText.setCharacterSize(60);
    mTurnCounterValueText.setPosition(848, 250);
    mTurnCounterValueText.setFillColor(sf::Color::Green);
    mTurnCounterValueText.setStyle(sf::Text::Bold);

    // JOSIAH AND THOMAS WERE STILL HERE
    mYourShips.setSize(sf::Vector2f(95, 150));
    mYourShips.setPosition(770, 350);
    mYourShips.setFillColor(sf::Color::Black);
    mYourShips.setOutlineColor(sf::Color(114, 114, 114));
    mYourShips.setOutlineThickness(3);

    mYourShipsText.setCharacterSize(22);
    mYourShipsText.setPosition(773, 350);
    mYourShipsText.setFillColor(sf::Color::Green);
    mYourShipsText.setStyle(sf::Text::Bold);

    mYourShipsValueText.setCharacterSize(80);
    mYourShipsValueText.setPosition(775, 390);
    mYourShipsValueText.setFillColor(sf::Color::Green);
    mYourShipsValueText.setStyle(sf::Text::Bold);

    // JOSIAH AND THOMAS WERE STILL HERE
    mEnemyShips.setSize(sf::Vector2f(95, 150));
    mEnemyShips.setPosition(885, 350);
    mEnemyShips.setFillColor(sf::Color::Black);
    mEnemyShips.setOutlineColor(sf::Color(114, 114, 114));
    mEnemyShips.setOutlineThickness(3);

    mEnemyShipsText.setCharacterSize(22);
    mEnemyShipsText.setPosition(885.5f, 350);
    mEnemyShipsText.setFillColor(sf::Color::Green);
    mEnemyShipsText.setStyle(sf::Text::Bold);

    mEnemyShipsValueText.setCharacterSize(80);
    mEnemyShipsValueText.setPosition(888.5f, 390);
    mEnemyShipsValueText.setFillColor(sf::Color::Green);
    mEnemyShipsValueText.setStyle(sf::Text::Bold);

    playerBoards[0].reset(new Board(currentGameState, context));
    playerBoards[1].reset(new Board(currentGameState, context));
}

GameScene::~GameScene() {
    // This if statement is important since the music (probably) gets destroyed
    // first when the window is closed versus changing the scene. We let the
    // computer handle the destruction of the music naturally by adding this if
    // statement.
    if (mWindow.isOpen()) {
        getContext().gameSceneMusic.stop();
        getContext().victoryMusic.stop();
    }
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
        if (currentGameState.getTurn() < 2) {
            mPreparationButtons[currentGameState.getPlayer()].handleInput(e);
        }
    } else if (currentGameState.currentPhase != GameState::Phase::Victory) {
        playerBoards[currentGameState.getPlayer()]->input(e);
    }
    return true;
}

void GameScene::draw() {
    mWindow.draw(mBackground);

    if (currentGameState.currentPhase == GameState::Phase::Transition) {
        if (currentGameState.getTurn() < 2) {
            mWindow.draw(mPreparationButtons[currentGameState.getPlayer()]);
        }
        mWindow.draw(mTransition);
        mWindow.draw(mTransitionSubtitle);
        mWindow.draw(mThreeStars);
    } else if (currentGameState.currentPhase != GameState::Phase::Victory) {
        mWindow.draw(mGameBackgroundSprite);
        mWindow.draw(mWhosTurn);
        mWindow.draw(mGameClock);
        mWindow.draw(mTurnCounter);
        mWindow.draw(mYourShips);
        mWindow.draw(mEnemyShips);
        mWindow.draw(mWhosTurnText);
        mWindow.draw(mGameClockText);
        mWindow.draw(mTurnCounterText);
        mWindow.draw(mYourShipsText);
        mWindow.draw(mEnemyShipsText);
        mWindow.draw(mWhosTurnValueText);
        mWindow.draw(mGameClockValueText);
        mWindow.draw(mTurnCounterValueText);
        mWindow.draw(mYourShipsValueText);
        mWindow.draw(mEnemyShipsValueText);
        mWindow.draw(mGreenLed);
        mWindow.draw(mYellowLed);
        mWindow.draw(mRedLed);
        mWindow.draw(mGrille);
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
        if (currentGameState.getTurn() == 2) {
            mActionTime += deltaTime;

            if (mActionTime.asSeconds() > 2) {
                // reset all buttons to attack
                for (int i = 0; i < 2; i++) {
                    playerBoards[i]->setBattlePhase();
                }
                currentGameState.currentPhase = GameState::Phase::Battle;
                std::cout << "in battle phase\n";
                currentGameState.resetTurnsToZero();
                mConfirmSound.play();
            }
        }
        mPreparationButtons[0].update(deltaTime);
        mPreparationButtons[1].update(deltaTime);
    } else if (currentGameState.currentPhase == GameState::Phase::Preparation) {
        if (currentGameState.getTurn() == 0) {
            mWhosTurnValueText.setString("1");
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
        } else if (currentGameState.getTurn() == 1) {
            mWhosTurnText.setFillColor(sf::Color::Red);
            mWhosTurnValueText.setFillColor(sf::Color::Red);
            mWhosTurnValueText.setString("2");
            mGameClockText.setFillColor(sf::Color::Red);
            mGameClockValueText.setFillColor(sf::Color::Red);
            mTurnCounterText.setFillColor(sf::Color::Red);
            mTurnCounterValueText.setFillColor(sf::Color::Red);
            mYourShipsText.setFillColor(sf::Color::Red);
            mYourShipsValueText.setFillColor(sf::Color::Red);
            mEnemyShipsText.setFillColor(sf::Color::Red);
            mEnemyShipsValueText.setFillColor(sf::Color::Red);

            if (playerBoards[currentGameState.getPlayer()]
                    ->getNumberOfShips() >= currentGameState.maxShips) {
                currentGameState.incrementTurn();
                currentGameState.currentPhase = GameState::Phase::Transition;

                mTransition.setCharacterSize(110);
                mTransition.setString("BATTLE!");  // Try to add BATTLE
                mTransition.setPosition(
                    windowSize.x / 2 - mTransition.getGlobalBounds().width / 2,
                    windowSize.y / 2 -
                        mTransition.getGlobalBounds().height / 2);

                mTransitionSubtitle.setFillColor(sf::Color::Transparent);
            }
        }
    } else if (currentGameState.currentPhase == GameState::Phase::Battle) {
        currentGameState.gameTime += deltaTime;

        if (currentGameState.getPlayer() == 0) {
            mWhosTurnValueText.setString("2");
            mWhosTurnText.setFillColor(sf::Color::Red);
            mWhosTurnValueText.setFillColor(sf::Color::Red);
            mGameClockText.setFillColor(sf::Color::Red);
            mGameClockValueText.setFillColor(sf::Color::Red);
            mTurnCounterText.setFillColor(sf::Color::Red);
            mTurnCounterValueText.setFillColor(sf::Color::Red);
            mYourShipsText.setFillColor(sf::Color::Red);
            mYourShipsValueText.setFillColor(sf::Color::Red);
            mEnemyShipsText.setFillColor(sf::Color::Red);
            mEnemyShipsValueText.setFillColor(sf::Color::Red);

        } else if (currentGameState.getPlayer() == 1) {
            mWhosTurnValueText.setString("1");
            mWhosTurnText.setFillColor(sf::Color::Green);
            mWhosTurnValueText.setFillColor(sf::Color::Green);
            mGameClockText.setFillColor(sf::Color::Green);
            mGameClockValueText.setFillColor(sf::Color::Green);
            mTurnCounterText.setFillColor(sf::Color::Green);
            mTurnCounterValueText.setFillColor(sf::Color::Green);
            mYourShipsText.setFillColor(sf::Color::Green);
            mYourShipsValueText.setFillColor(sf::Color::Green);
            mEnemyShipsText.setFillColor(sf::Color::Green);
            mEnemyShipsValueText.setFillColor(sf::Color::Green);
        }

        std::string currentTurn;
        if (currentGameState.getTurn() + 1 < 10) {
            currentTurn += "0";
        }
        currentTurn += std::to_string(currentGameState.getTurn() + 1);
        mTurnCounterValueText.setString(currentTurn);

        std::string player1Ships;
        if (currentGameState.numberOfShips[0] < 10) {
            player1Ships += "0";
        }
        player1Ships += std::to_string(currentGameState.numberOfShips[0]);
        mYourShipsValueText.setString(player1Ships);

        std::string player2Ships;
        if (currentGameState.numberOfShips[1] < 10) {
            player2Ships += "0";
        }
        player2Ships += std::to_string(currentGameState.numberOfShips[1]);
        mEnemyShipsValueText.setString(player2Ships);

        std::string gameClock;
        gameClock +=
            std::to_string((int)currentGameState.gameTime.asSeconds() / 60);
        gameClock += ":";
        if ((int)currentGameState.gameTime.asSeconds() % 60 < 10) {
            gameClock += "0";
            gameClock +=
                std::to_string((int)currentGameState.gameTime.asSeconds() % 60);
        } else {
            gameClock +=
                std::to_string((int)currentGameState.gameTime.asSeconds() % 60);
        }
        mGameClockValueText.setString(gameClock);

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
        if (mPlayerWin.getFillColor() == sf::Color::White) {
            mPlayerWin.setFillColor(sf::Color::Transparent);
        } else {
            mPlayerWin.setFillColor(sf::Color::White);
        }
        victoryBlinkTime = sf::Time::Zero;
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