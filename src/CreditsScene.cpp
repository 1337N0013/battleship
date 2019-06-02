#include "CreditsScene.h"
#include "Command.h"

CreditsScene::CreditsScene(SceneStack& stack, Context context)
    : Scene(stack, context),
      mWindow(context.window),
      mBackground(sf::Vector2f(context.window.getSize())),
      mCredits("Credits", context.font),
      mCreditsList("", context.font),
      mReturnToMainMenu("Return to Main Menu", context.font) {
    mBackground.setFillColor(sf::Color::Black);

    mCreditsList.setCharacterSize(12);
    mCreditsList.setString(
        "In partial completion for the requirements of CMSC 21\n"
        "AS 2018-2019\n\n"
        "Developed by:\n"
        "Thomas Jonathan Garcia\n"
        "Carl Josiah Ocampo\n"
        "Grant-Ivan Yap\n\n"
        "Victory (8bit Version) by Two Steps From Hell. (2017). Navneeth "
        "Sridharan.\nRetrieved May 22, 2019, from youtu.be/cTNxAZvcXwo\n\n"
        "8 Bit Hideout.  (2014). HeatlyBros.\nRetrieved May 22, 2019, from "
        "youtu.be/W-3kQA61iHA\n\n"
        "Dark Alley. (2018). HeatlyBros.\nRetrieved May 22, 2019, from "
        "youtu.be/Qa1D5pibGnE\n\n"
        "A 8-bit Futuristic Theme. (2018). Pixel Beats.\nRetrieved May 22, "
        "2019, from youtu.be/UYAiMr-4QxY\n\n"
        "Game Time Hip Hop!. (2015). HeatlyBros.\nRetrieved May 22, 2019, from "
        "youtu.be/XcZuJAjYfKo\n\n"
        "The Final Countdown (8 Bit Remix Cover Version). (2016). 8 Bit "
        "Universe.\nRetrieved May 22, 2019, from youtu.be/znSI2-sL40E\n\n"
        "Hero Dance Party. (2019). TeknoAXE’s Royalty Free Music.\nRetrieved "
        "May 22, 2019, from youtu.be/opXYXqekK14\n\n"
        "Game Art and Sounds from:\n"
        "opengameart.org\n"
        "VectorStock.com\n"
        "8BitImages.com\n"
        "LmitedAustralia.com\n");
    mCreditsList.setPosition(
        mWindow.getSize().x / 2 - mCreditsList.getGlobalBounds().width / 2,
        100);

    mCredits.setPosition(mCreditsList.getPosition().x, 50);

    mReturnToMainMenu.setSize(425, 30);
    mReturnToMainMenu.setCharacterSize(20);
    mReturnToMainMenu.setPosition(
        mWindow.getSize().x - mCredits.getPosition().x -
            mReturnToMainMenu.getGlobalBounds().width,
        mWindow.getSize().y - mCredits.getPosition().y -
            mReturnToMainMenu.getGlobalBounds().height);
    mReturnToMainMenu.onClickCommand.reset(new SceneCommand::RemoveScene(*this, context.confirm));
}

CreditsScene::~CreditsScene() {}

bool CreditsScene::input(const sf::Event& e) {
    switch (e.type) {
        case sf::Event::KeyReleased: {
            if (e.key.code == sf::Keyboard::Escape) {
                requestScenePop();
                break;
            }
            default:
                break;
        }
    }
    mReturnToMainMenu.handleInput(e);
    return false;
}

bool CreditsScene::update(sf::Time deltaTime) {
    mReturnToMainMenu.update(deltaTime);
    return false;
}

void CreditsScene::draw() {
    mWindow.draw(mBackground);
    mWindow.draw(mCredits);
    mWindow.draw(mCreditsList);
    mWindow.draw(mReturnToMainMenu);
}