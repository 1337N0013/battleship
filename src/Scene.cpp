#include "Scene.h"
#include "SceneStack.h"

Scene::Scene(SceneStack& stack, Context context)
    : mStack(stack), mContext(context) {}

Scene::Context::Context(sf::RenderWindow& window, sf::Font& font)
    : window(window), font(font) {}

void Scene::requestScenePush(Scene::ID sceneID) { mStack.pushScene(sceneID); }
void Scene::requestScenePop() { mStack.popScene(); }
void Scene::requestSceneClear() { mStack.clearScenes(); }

Scene::Context Scene::getContext() const { return mContext; }