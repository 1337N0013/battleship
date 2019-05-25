#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameSettings.h"

class SceneStack;  // forward declaration, solves circular dependency

class Scene {
   public:
    struct Context {
        Context (sf::RenderWindow& window, sf::Font& font, GameSettings& gameSettings, sf::Texture& background, sf::Music& mainMenuMusic, sf::Music& gameSceneMusic, sf::Music& victoryMusic);
        sf::RenderWindow& window;
        sf::Font& font;
        GameSettings& gameSettings;
        sf::Texture& background;
        sf::Music& mainMenuMusic;
        sf::Music& gameSceneMusic;
        sf::Music& victoryMusic;
    };

    enum class ID { None, MainMenu, Game, Settings, Pause };

   public:
    Scene(SceneStack& stack, Context& context);
    virtual ~Scene() {}
    virtual bool input(const sf::Event& e) = 0;
    virtual void draw() = 0;
    virtual bool update(sf::Time deltaTime) = 0;

    void requestScenePush(Scene::ID sceneID);
    void requestScenePop();
    void requestSceneClear();

    Context& getContext();

   private:
    SceneStack& mStack;
    Context& mContext;
};

#endif