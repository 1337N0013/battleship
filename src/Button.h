#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <unordered_map>
#include "Fonts.h"

#ifndef BUTTON_H
#define BUTTON_H

using std::cout;

class Button : public sf::Drawable, public sf::Transformable {
    sf::RectangleShape buttonRect;
    sf::Font font;
    sf::Text buttonText;
    sf::FloatRect buttonTextBounds;

   public:
    sf::Time timeSinceClick;

    enum State { Default, Hovered, Pressed, Released };

    void create(const float left, const float top, const sf::Vector2f& size,
                const std::string& text);
    void create(const float left, const float top, const float width,
                const float height, const std::string& text);

    Button();

    Button(const float left, const float top, const sf::Vector2f& size,
           const std::string& text);
    Button(const float left, const float top, const float width,
           const float height, const std::string& text);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void setPosition(const float x, const float y);
    void setPosition(const sf::Vector2f& pos);
    const sf::Vector2f& getPosition();

    void setText(std::string text);
    const std::string getText();

    void setCharacterSize(unsigned int size);
    unsigned int getCharacterSize();

    void setFillColor(const sf::Color& color);
    const sf::Color& getFillColor();

    void setTextColor(const sf::Color& color);
    const sf::Color& getTextColor();

    sf::FloatRect getGlobalBounds();

    bool isPressed();
    bool wasPressed();

    void setState(const State state);
    const State getState();
    void setStateColor(const State state, const sf::Color& color);
    const sf::Color& getStateColor(const State state);

    void resetTimeSinceClick();

    void update(sf::Time deltaTime);

    void handleInput(sf::Event e);

   private:
    State currentState = Default;
    std::unordered_map<State, sf::Color> stateColors = {
        {Default, sf::Color::Red},
        {Hovered, sf::Color::Blue},
        {Pressed, sf::Color::Cyan},
        {Released, sf::Color::Green}};

    void centerText();
};

#endif