#ifndef CREDITSSCENE_H
#define CREDITSSCENE_H

#include "Button.h"
#include "Scene.h"

class CreditsScene : public Scene {
   public:
    CreditsScene(SceneStack& stack, Context context);
    ~CreditsScene();

    bool input(const sf::Event& e);
    void draw();
    bool update(sf::Time deltatTime);

   private:
    sf::RenderWindow& mWindow;

    sf::RectangleShape mBackground;
    sf::Text mCredits;
    sf::Text mCreditsList;
    Button mReturnToMainMenu;
};

#endif