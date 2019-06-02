#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <unordered_map>
#include "Scene.h"

class Command;

class Button : public sf::Drawable, public sf::Transformable {
    sf::Font& mFont;
    sf::FloatRect labelBounds;
    static sf::Vector2i lastMousePos;

   public:
    sf::RectangleShape rectangle;
    sf::Text label;

    std::shared_ptr<Command> onClickCommand;

    sf::Time timeSinceClick;
    float buttonReleaseTime = 0.3f;

    enum class State { Default, Hovered, Pressed, Released };

    Button(const std::string& text, sf::Font& font);
    Button(const sf::Vector2f& position, const sf::Vector2f& size,
           const std::string& text, sf::Font& font);
    Button(const float left, const float top, const sf::Vector2f& size,
           const std::string& text, sf::Font& font);
    Button(const float left, const float top, const float width,
           const float height, const std::string& text, sf::Font& font);
    ~Button();

    virtual void draw(sf::RenderTarget& target,
                      sf::RenderStates states) const override;

    void setPosition(const float x, const float y);
    void setPosition(const sf::Vector2f& pos);
    const sf::Vector2f& getPosition();

    void setSize(const float x, const float y);
    void setSize(const sf::Vector2f& size);
    const sf::Vector2f& getSize();

    void setText(std::string text);
    const std::string getText();

    void setCharacterSize(unsigned int size);
    unsigned int getCharacterSize();

    void setFillColor(const sf::Color& color);
    const sf::Color& getFillColor();

    void setTextColor(const sf::Color& color);
    const sf::Color& getTextColor();

    sf::FloatRect getGlobalBounds();

    void setState(const State& state);
    const State getState();
    void setStateColor(const State state, const sf::Color& color);
    const sf::Color& getStateColor(const State state);

    void resetTimeSinceClick();

    virtual bool update(sf::Time deltaTime);

    virtual bool handleInput(sf::Event e);

   private:
    State currentState;
    std::unordered_map<State, sf::Color> stateColors;

    void centerText();
};

#endif