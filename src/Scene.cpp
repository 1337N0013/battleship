#include "Scene.h"
#include "SceneStack.h"

Scene::Scene(SceneStack& stack, Context& context)
    : mStack(stack), mContext(context) {}

Scene::Context::Context(sf::RenderWindow& window, sf::Font& font,
                        GameSettings& gameSettings, sf::Texture& background,
                        sf::Texture& gameBackground, 
                        sf::Texture& bolt, sf::Texture& dial, 
                        sf::Texture& knob, sf::Texture& greenLed,
                        sf::Texture& redLed, sf::Texture& radio,
                        sf::Music& mainMenuMusic, sf::Music& gameSceneMusic,
                        sf::Music& victoryMusic, sf::Texture& threeStars,
                        sf::Texture& medal)
    : window(window),
      font(font),
      gameSettings(gameSettings),
      background(background),
      gameBackground(gameBackground),
      bolt(bolt), dial(dial), knob(knob),
      redLed(redLed), greenLed(greenLed),
      radio(radio),
      mainMenuMusic(mainMenuMusic),
      gameSceneMusic(gameSceneMusic),
      victoryMusic(victoryMusic),
      threeStars(threeStars),
      medal(medal) {}

void Scene::requestScenePush(Scene::ID sceneID) { mStack.pushScene(sceneID); }
void Scene::requestScenePop() { mStack.popScene(); }
void Scene::requestSceneClear() { mStack.clearScenes(); }

Scene::Context& Scene::getContext() { return mContext; }