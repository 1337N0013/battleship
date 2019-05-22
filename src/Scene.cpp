#include "Scene.h"
#include "SceneStack.h"

Scene::Scene(SceneStack& stack, Context& context)
    : mStack(stack), mContext(context) {}

Scene::Context::Context(sf::RenderWindow& window, sf::Font& font, GameSettings& gameSettings, sf::Texture& background, sf::Music& mainMenuMusic)
    : window(window), font(font), gameSettings(gameSettings), background(background), mainMenuMusic(mainMenuMusic) {}

void Scene::requestScenePush(Scene::ID sceneID) { mStack.pushScene(sceneID); }
void Scene::requestScenePop() { mStack.popScene(); }
void Scene::requestSceneClear() { mStack.clearScenes(); }

Scene::Context& Scene::getContext() { return mContext; }