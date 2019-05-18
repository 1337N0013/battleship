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

class ChangeState : public Command {
   public:
    ChangeState(SceneStack& sceneStack, Scene::ID sceneID);
    void execute();

   private:
    SceneStack& mStack;
    Scene::ID mSceneID;
};
}  // namespace Command

#endif COMMAND_H