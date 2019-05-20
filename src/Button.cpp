#include "Button.h"
#include <iostream>

using std::cout;

sf::Vector2i Button::lastMousePos = sf::Vector2i(0, 0);

Button::Button(const float left, const float top, const sf::Vector2f& size,
               const std::string& text, sf::Font& font)
    : mFont(font) {
    buttonRect.setSize(size);
    buttonRect.setFillColor(sf::Color::Red);

    buttonText.setFont(mFont);
    buttonText.setString(text);
    setPosition(left, top);

    sf::Time timeSinceClick = sf::Time::Zero;
    currentState = State::Default;
    stateColors = {{State::Default, sf::Color::Red},
                   {State::Hovered, sf::Color::Blue},
                   {State::Pressed, sf::Color::Cyan},
                   {State::Released, sf::Color::Green}};
}
Button::Button(const sf::Vector2f& position, const sf::Vector2f& size,
               const std::string& text, sf::Font& font)
    : Button(position.x, position.y, size, text, font) {}
Button::Button(const float left, const float top, const float width,
               const float height, const std::string& text,
               sf::Font& font)
    : Button(left, top, sf::Vector2f(width, height), text, font) {}
Button::Button(const std::string& text, sf::Font& font)
    : Button(0, 0, 100, 100, text, font) {}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(buttonRect, states);
    target.draw(buttonText, states);
}

void Button::setPosition(const float x, const float y) {
    buttonRect.setPosition(x, y);
    centerText();
}
void Button::setPosition(const sf::Vector2f& pos) { setPosition(pos.x, pos.y); }
const sf::Vector2f& Button::getPosition() { return buttonRect.getPosition(); }

void Button::setSize(const float x, const float y) {
    buttonRect.setSize(sf::Vector2f(x, y));
    centerText();
}
void Button::setSize(const sf::Vector2f& size) {
    buttonRect.setSize(size);
    centerText();
}
const sf::Vector2f& Button::getSize() {
    return buttonRect.getSize();
}

void Button::setText(std::string text) {
    buttonText.setString(text);
    centerText();
}
const std::string Button::getText() { return buttonText.getString(); }

void Button::setCharacterSize(unsigned int size) {
    buttonText.setCharacterSize(size);
    centerText();
}
unsigned int Button::getCharacterSize() {
    return buttonText.getCharacterSize();
}

void Button::setFillColor(const sf::Color& color) {
    buttonRect.setFillColor(color);
}
const sf::Color& Button::getFillColor() { return buttonRect.getFillColor(); }

void Button::setTextColor(const sf::Color& color) {
    buttonText.setFillColor(color);
}
const sf::Color& Button::getTextColor() { return buttonText.getFillColor(); }

sf::FloatRect Button::getGlobalBounds() { return buttonRect.getGlobalBounds(); }

void Button::setState(const State& state) {
    currentState = state;
    buttonRect.setFillColor(stateColors[state]);
}
const Button::State Button::getState() { return currentState; }
void Button::setStateColor(const State state, const sf::Color& color) {
    stateColors[state] = color;
}
const sf::Color& Button::getStateColor(const State state) {
    return stateColors[state];
}

void Button::resetTimeSinceClick() { timeSinceClick = sf::Time::Zero; }

bool Button::update(sf::Time deltaTime) {
    timeSinceClick += deltaTime;

    if (getState() == State::Released) {
        if (timeSinceClick.asSeconds() > buttonReleaseTime) {
            if (getGlobalBounds().contains(lastMousePos.x, lastMousePos.y)) {
                setState(State::Hovered);
            } else {
                setState(State::Default);
            }
        }
        return true;
    }

    return false;
}

bool Button::handleInput(sf::Event e) {
    if (e.type == sf::Event::MouseMoved) {
        lastMousePos = sf::Vector2i(e.mouseMove.x, e.mouseMove.y);
    }
    switch (getState()) {
        case State::Default: {
            if (e.type == sf::Event::MouseMoved) {
                if (getGlobalBounds().contains(lastMousePos.x,
                                               lastMousePos.y)) {
                    setState(State::Hovered);
                }
            }
            break;
        }
        case State::Hovered: {
            if (e.type == sf::Event::MouseMoved) {
                if (!getGlobalBounds().contains(lastMousePos.x,
                                                lastMousePos.y)) {
                    setState(State::Default);
                }
            } else if (e.type == sf::Event::MouseButtonPressed &&
                       e.mouseButton.button == sf::Mouse::Left) {
                setState(State::Pressed);
            }
            break;
        }
        case State::Pressed: {
            if (e.type == sf::Event::MouseButtonReleased &&
                e.mouseButton.button == sf::Mouse::Left) {
                if (getGlobalBounds().contains(lastMousePos.x,
                                               lastMousePos.y)) {
                    setState(State::Released);
                    resetTimeSinceClick();
                    onClickCommand->execute();
                    return true;
                } else {
                    setState(State::Default);
                }
            }
            break;
        }
        case State::Released: {
            if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
                setState(State::Pressed);
            }
            return true;
            break;
        }
        default:
            break;
    }
    return false;
}

void Button::centerText() {
    buttonTextBounds = buttonText.getLocalBounds();
    sf::Vector2f rectPos = buttonRect.getPosition();
    sf::FloatRect rectBounds = buttonRect.getLocalBounds();
    buttonText.setOrigin(buttonTextBounds.left + buttonTextBounds.width / 2,
                         buttonTextBounds.top + buttonTextBounds.height / 2);
    buttonText.setPosition(rectPos.x + rectBounds.width / 2,
                           rectPos.y + rectBounds.height / 2);
}