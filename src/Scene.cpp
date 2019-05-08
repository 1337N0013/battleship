#include "Scene.h"

Scene::Scene(sf::RenderWindow& window, unsigned int width, unsigned int height,
             sf::Font& font)
    : mWindow(window), mWidth(width), mHeight(height), mFont(font) {}

Scene::~Scene() {}