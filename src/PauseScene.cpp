#include "Command.h"
#include "PauseScene.h"

PauseScene::PauseScene(SceneStack& stack, Context& context)
    : Scene(stack, context),  
      mPauseText("Paused", context.font),
      mContinueButton("Continue", context.font),
      mExitButton("Quit", context.font),
      mHit(context.hit), mMiss(context.miss),
      mHitText("- HIT", context.font), mMissText("- MISS", context.font),
      mLegendText("LENGEND:", context.font) {
    mBackground.setSize(sf::Vector2f(context.window.getSize().x, context.window.getSize().y));
    mBackground.setFillColor(sf::Color(0, 0, 0, 200));

    mPauseText.setCharacterSize(20);
    mPauseText.setPosition(100, 100);

    sf::Vector2f buttonSize(300, 30);

    mExitButton.setCharacterSize(20);
    mExitButton.setPosition(100, context.window.getSize().y - 100 - 30);
    mExitButton.setSize(buttonSize);
    mExitButton.onClickCommand.reset(new SceneCommand::ReturnToMainMenu(*this));

    mContinueButton.setCharacterSize(20);
    mContinueButton.setPosition(100, mExitButton.getPosition().y-50);
    mContinueButton.setSize(buttonSize);
    mContinueButton.onClickCommand.reset(new SceneCommand::RemoveScene(*this));

    mLegendText.setPosition(600,100);
    mLegendText.setCharacterSize(20);

    mHit.setPosition(600,150);
    mHit.setScale(0.05f, 0.05f);
    mHitText.setPosition(700,165);
    mHitText.setCharacterSize(30);

    mMiss.setPosition(600,250);
    mMiss.setScale(0.05f, 0.05f);   
    mMissText.setPosition(700,265);
    mMissText.setCharacterSize(30); 
}

PauseScene::~PauseScene() {}

bool PauseScene::input(const sf::Event& e) {
    switch(e.type) {
        case sf::Event::KeyReleased: {
            if (e.key.code == sf::Keyboard::Escape) {
                requestScenePop();
            }
            break;
        }
        default:
            break;
    }
    mContinueButton.handleInput(e);
    mExitButton.handleInput(e);
    return false;
}

void PauseScene::draw() {
    getContext().window.draw(mBackground);
    getContext().window.draw(mPauseText);
    getContext().window.draw(mContinueButton);
    getContext().window.draw(mExitButton);
    getContext().window.draw(mLegendText);
    getContext().window.draw(mHit);
    getContext().window.draw(mMiss);
    getContext().window.draw(mHitText);
    getContext().window.draw(mMissText);
}

bool PauseScene::update(sf::Time deltaTime) {
    mContinueButton.update(deltaTime);
    mExitButton.update(deltaTime);
    return false;
}