#include "Command.h"
#include "SettingsScene.h"

SettingsScene::SettingsScene(SceneStack& stack, Context& context)
    : Scene(stack, context),
      mSettingsText("Settings", context.font),
      mNumberOfShipsText("", context.font),
      mBoardSizeText("", context.font),
      mIncreaseShips("+", context.font),
      mDecreaseShips("-", context.font),
      mIncreaseBoard("+", context.font),
      mDecreaseBoard("-", context.font),
      mHit(context.hit),
      mMiss(context.miss),
      mHitText("- HIT", context.font), 
      mMissText("- MISS", context.font),
      mLegendText("LENGEND:", context.font),
      playButton(100, context.window.getSize().y-100-30, 300, 30, "Play", context.font) {
    mBackground.setPosition(0, 0);
    sf::Vector2f windowSize(context.window.getSize().x,
                            context.window.getSize().y);
    mBackground.setSize(windowSize);
    mBackground.setFillColor(sf::Color::Black);

    mSettingsText.setCharacterSize(20);
    mSettingsText.setPosition(100, 100);

    sf::Vector2f buttonSize(45, 45);

    mNumberOfShipsText.setCharacterSize(20);
    mNumberOfShipsText.setPosition(100, 200);

    mDecreaseShips.setCharacterSize(20);
    mDecreaseShips.setPosition(500, 190);
    mDecreaseShips.setSize(buttonSize);
    mDecreaseShips.onClickCommand.reset(new SettingsCommand::DecreaseShips(context));

    mIncreaseShips.setCharacterSize(20);
    mIncreaseShips.setPosition(550, 190);
    mIncreaseShips.setSize(buttonSize);
    mIncreaseShips.onClickCommand.reset(new SettingsCommand::IncreaseShips(context));

    mBoardSizeText.setCharacterSize(20);
    mBoardSizeText.setPosition(100, 250);

    mDecreaseBoard.setCharacterSize(20);
    mDecreaseBoard.setPosition(500, 240);
    mDecreaseBoard.setSize(buttonSize);
    mDecreaseBoard.onClickCommand.reset(new SettingsCommand::DecreaseBoard(context));

    mIncreaseBoard.setCharacterSize(20);
    mIncreaseBoard.setPosition(550, 240);
    mIncreaseBoard.setSize(buttonSize);
    mIncreaseBoard.onClickCommand.reset(new SettingsCommand::IncreaseBoard(context));

    mLegendText.setPosition(100,350);
    mLegendText.setCharacterSize(20);

    mHit.setPosition(100,420);
    mHit.setScale(0.04f, 0.04f);
    mHitText.setPosition(180,430);
    mHitText.setCharacterSize(20);

    mMiss.setPosition(100,520);
    mMiss.setScale(0.04f, 0.04f);   
    mMissText.setPosition(180,530);
    mMissText.setCharacterSize(20);

    playButton.setCharacterSize(20);
    playButton.onClickCommand.reset(
        new SceneCommand::ChangeAndRemoveScene(*this, Scene::ID::Game));
}

SettingsScene::~SettingsScene() {}

bool SettingsScene::input(const sf::Event& e) {
    switch (e.type) {
        case sf::Event::KeyPressed: {
            if (e.key.code == sf::Keyboard::Up) {
                mIncreaseShips.setState(Button::State::Pressed);
            } else if (e.key.code == sf::Keyboard::Down) {
                mDecreaseShips.setState(Button::State::Pressed);
            } else if (e.key.code == sf::Keyboard::Right) {
                mIncreaseBoard.setState(Button::State::Pressed);
            } else if (e.key.code == sf::Keyboard::Left) {
                mDecreaseBoard.setState(Button::State::Pressed);
            }
            break;
        }
        case sf::Event::KeyReleased: {
            if (e.key.code == sf::Keyboard::Escape) {
                requestScenePop();
            } else if (e.key.code == sf::Keyboard::Up) {
                SettingsCommand::IncreaseShips(getContext()).execute();
                mIncreaseShips.setState(Button::State::Released);
            } else if (e.key.code == sf::Keyboard::Down) {
                SettingsCommand::DecreaseShips(getContext()).execute();
                mDecreaseShips.setState(Button::State::Released);
            } else if (e.key.code == sf::Keyboard::Right) {
                SettingsCommand::IncreaseBoard(getContext()).execute();
                mIncreaseBoard.setState(Button::State::Released);
            } else if (e.key.code == sf::Keyboard::Left) {
                SettingsCommand::DecreaseBoard(getContext()).execute();
                mDecreaseBoard.setState(Button::State::Released);
            }
        }
        default:
            break;
    }
    mDecreaseShips.handleInput(e);
    mIncreaseShips.handleInput(e);

    mDecreaseBoard.handleInput(e);
    mIncreaseBoard.handleInput(e);

    playButton.handleInput(e);

    return false;
}

void SettingsScene::draw() {
    getContext().window.draw(mBackground);
    getContext().window.draw(mSettingsText);

    getContext().window.draw(mNumberOfShipsText);
    getContext().window.draw(mDecreaseShips);
    getContext().window.draw(mIncreaseShips);

    getContext().window.draw(mBoardSizeText);
    getContext().window.draw(mDecreaseBoard);
    getContext().window.draw(mIncreaseBoard);

    getContext().window.draw(playButton);

    getContext().window.draw(mLegendText);
    getContext().window.draw(mHit);
    getContext().window.draw(mMiss);
    getContext().window.draw(mHitText);
    getContext().window.draw(mMissText);
}

bool SettingsScene::update(sf::Time deltaTime) {
    unsigned int tiles = getContext().gameSettings.getBoardSize().x *
                               getContext().gameSettings.getBoardSize().y;
    if (getContext().gameSettings.getNumberOfShips() > tiles / 2) {
        getContext().gameSettings.setNumberOfShips(tiles/2);
    }

    mNumberOfShipsText.setString(
        std::string("Number of ships: ") +
        std::to_string(getContext().gameSettings.getNumberOfShips()));
    mBoardSizeText.setString(
        std::string("Board size: ") +
        std::to_string(getContext().gameSettings.getBoardSize().x) +
        std::string(" x ") +
        std::to_string(getContext().gameSettings.getBoardSize().y));

    mDecreaseShips.update(deltaTime);
    mIncreaseShips.update(deltaTime);

    mDecreaseBoard.update(deltaTime);
    mIncreaseBoard.update(deltaTime);

    playButton.update(deltaTime);

    return false;
}