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

class IncreaseShips : public Command {
   public:
    IncreaseShips(Scene::Context& context);
    ~IncreaseShips();
    void execute();

   private:
    Scene::Context& mContext;
};

class DecreaseShips : public Command {
   public:
    DecreaseShips(Scene::Context& context);
    ~DecreaseShips();
    void execute();

   private:
    Scene::Context& mContext;
};

class IncreaseBoard : public Command {
public:
    IncreaseBoard(Scene::Context& context);
    ~IncreaseBoard();
    void execute();

private:
    Scene::Context& mContext;
};

class DecreaseBoard : public Command {
   public:
    DecreaseBoard(Scene::Context& context);
    ~DecreaseBoard();
    void execute();

   private:
    Scene::Context& mContext;
};

}  // namespace Command

#endif