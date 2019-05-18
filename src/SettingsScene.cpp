#include "SettingsScene.h"

SettingsScene::SettingsScene(SceneStack& stack, Context context)
    : Scene(stack, context), mSettingsText("Settings", context.font), playButton(100, 300, 300, 50, "Play", context) {
    mBackground.setPosition(0, 0);
    sf::Vector2f windowSize(context.window.getSize().x,
                            context.window.getSize().y);
    mBackground.setSize(windowSize);
    mBackground.setFillColor(sf::Color::Black);
    mSettingsText.setPosition(100, 100);

    playButton.onClickCommand.reset(new Command::ChangeScene(*this, Scene::ID::Game));
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
    getContext().window.draw(playButton);
}

bool SettingsScene::update(sf::Time deltaTime) {
    playButton.update(deltaTime);

    return true;
}