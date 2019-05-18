#ifndef COMMAND_H
#define COMMAND_H

#include "Scene.h"
#include "SceneStack.h"

namespace Command {

class Command {
   public:
    virtual ~Command();
    virtual void execute() = 0;
};

class ChangeScene : public Command {
   public:
    ChangeScene(Scene& currentScene, Scene::ID sceneID);
    ~ChangeScene();
    void execute();

   private:
    Scene& mScene;
    Scene::ID mSceneID;
};

class RemoveScene : public Command {
   public:
    RemoveScene(Scene& currentScene);
    ~RemoveScene();
    void execute();

   private:
    Scene& mScene;
};

}  // namespace Command

#endif