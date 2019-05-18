#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics.hpp>

class SceneStack;  // forward declaration, solves circular dependency

class Scene {
   public:
    struct Context {
        Context (sf::RenderWindow& window, sf::Font& font);
        sf::RenderWindow& window;
        sf::Font& font;
    };

    enum class ID { None, MainMenu, Game };

   public:
    Scene(SceneStack& stack, Context context);
    virtual ~Scene() {}
    virtual bool input(const sf::Event& e) = 0;
    virtual void draw() = 0;
    virtual bool update(sf::Time deltaTime) = 0;

    void requestScenePush(Scene::ID sceneID);
    void requestScenePop();
    void requestSceneClear();

    Context getContext() const;

   private:
    SceneStack& mStack;
    Context mContext;
};

#endif