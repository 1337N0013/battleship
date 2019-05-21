#ifndef COMMAND_H
#define COMMAND_H

#include "Scene.h"
#include "SceneStack.h"

class Command {
   public:
    virtual ~Command();
    virtual void execute() = 0;
};

class EmptyCommand : public Command {
   public:
    EmptyCommand();
    ~EmptyCommand();
    void execute();
};

namespace SceneCommand {

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

class ChangeAndRemoveScene : public Command {
   public:
    ChangeAndRemoveScene(Scene& currentScene, Scene::ID sceneID);
    ~ChangeAndRemoveScene();
    void execute();

   private:
    Scene& mScene;
    Scene::ID mSceneID;
};

class ReturnToMainMenu : public Command {
   public:
    ReturnToMainMenu(Scene& currentScene);
    ~ReturnToMainMenu();
    void execute();

   private:
    Scene& mScene;
};

}  // namespace SceneCommand

namespace SettingsCommand {

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

}  // namespace SettingsCommand

#endif