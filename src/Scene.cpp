#include "Scene.h"
#include "SceneStack.h"

Scene::Scene(SceneStack& stack, Context context)
    : mStack(stack), mContext(context) {}

void Scene::requestScenePush(Scene::ID sceneID) { mStack.pushScene(sceneID); }
void Scene::requestScenePop() { mStack.popScene(); }
void Scene::requestSceneClear() { mStack.clearScenes(); }

Context Scene::getContext() const { return mContext; }