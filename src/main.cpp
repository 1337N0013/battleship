#include <iostream>
#include "Engine.h"

int main() {
    // load resources
    FontManager::getInstance().load(FontManager::ID::Normal,
                                    "res/fonts/ProFont For Powerline.ttf");
    FontManager::getInstance().load(FontManager::ID::Bold,
                                    "res/fonts/ProFont Bold For Powerline.ttf");
    
    // start game
    Engine app;
    app.start();

    return 0;
}