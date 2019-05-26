#include "Scene.h"
#include "SceneStack.h"

Scene::Scene(SceneStack& stack, Context& context)
    : mStack(stack), mContext(context) {}

Scene::Context::Context(sf::RenderWindow& window, sf::Font& font,
                        GameSettings& gameSettings, sf::Texture& background,
                        sf::Texture& gameBackground, sf::Texture& panel,
                        sf::Music& mainMenuMusic, sf::Music& gameSceneMusic,
                        sf::Music& victoryMusic, sf::Texture& threeStars,
                        sf::Texture& medal)
    : window(window),
      font(font),
      gameSettings(gameSettings),
      background(background),
      gameBackground(gameBackground),
      panel(panel),
      mainMenuMusic(mainMenuMusic),
      gameSceneMusic(gameSceneMusic),
      victoryMusic(victoryMusic),
      threeStars(threeStars),
      medal(medal) {}

void Scene::requestScenePush(Scene::ID sceneID) { mStack.pushScene(sceneID); }
void Scene::requestScenePop() { mStack.popScene(); }
void Scene::requestSceneClear() { mStack.clearScenes(); }

Scene::Context& Scene::getContext() { return mContext; }