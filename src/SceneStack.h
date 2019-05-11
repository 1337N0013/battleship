#include <SFML/Graphics.hpp>
#include "Context.h"

#ifndef SCENESTACK_H
#define SCENESTACK_H

class SceneStack : private sf::NonCopyable {
    public:
    enum class Action {
        Push,
        Pop,
        Clear
    };

    public:
    explicit SceneStack(Context context);

    template <typename T>
    void registerState(stateID);
};

#endif