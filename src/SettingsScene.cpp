#include "SettingsScene.h"

SettingsScene::SettingsScene(SceneStack& stack, Context context)
    : Scene(stack, context),
      mSettingsText("Settings", context.font),
      mNumberOfShipsText("hello", context.font),
      mBoardSizeText("BOARD SIZE", context.font),
      playButton(100, 500, 300, 30, "Play", context) {
    mBackground.setPosition(0, 0);
    sf::Vector2f windowSize(context.window.getSize().x,
                            context.window.getSize().y);
    mBackground.setSize(windowSize);
    mBackground.setFillColor(sf::Color::Black);

    mSettingsText.setPosition(100, 100);
    mNumberOfShipsText.setPosition(100, 200);
    mNumberOfShipsText.setString(
        std::string("Number of ships: ") +
        std::to_string(context.gameSettings.getNumberOfShips()));
    mBoardSizeText.setPosition(100, 250);
    mBoardSizeText.setString(
        std::string("Board size: ") +
        std::to_string(context.gameSettings.getBoardSize().x) +
        std::string(" x ") +
        std::to_string(context.gameSettings.getBoardSize().y));

    playButton.onClickCommand.reset(
        new Command::ChangeScene(*this, Scene::ID::Game));
}

SettingsScene::~SettingsScene() {}

bool SettingsScene::input(const sf::Event& e) {
    switch (e.type) {
        case sf::Event::KeyReleased: {
            if (e.key.code == sf::Keyboard::Escape) {
                requestScenePop();
            }
        }
        default:
            break;
    }
    playButton.handleInput(e);

    return true;
}

void SettingsScene::draw() {
    getContext().window.draw(mBackground);

    getContext().window.draw(mSettingsText);
    getContext().window.draw(mNumberOfShipsText);
    getContext().window.draw(mBoardSizeText);

    getContext().window.draw(playButton);
}

bool SettingsScene::update(sf::Time deltaTime) {
    playButton.update(deltaTime);

    return true;
}