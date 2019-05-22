#include "Button.h"
#include <iostream>
#include "Command.h"

using std::cout;

sf::Vector2i Button::lastMousePos = sf::Vector2i(0, 0);

Button::Button(const float left, const float top, const sf::Vector2f& size,
               const std::string& text, sf::Font& font)
    : mFont(font) {
    rectangle.setSize(size);
    rectangle.setFillColor(sf::Color::Red);

    label.setFont(mFont);
    label.setString(text);
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
               const float height, const std::string& text, sf::Font& font)
    : Button(left, top, sf::Vector2f(width, height), text, font) {}
Button::Button(const std::string& text, sf::Font& font)
    : Button(0, 0, 100, 100, text, font) {
    onClickCommand.reset(new EmptyCommand());
}
Button::~Button() {}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(rectangle, states);
    target.draw(label, states);
}

void Button::setPosition(const float x, const float y) {
    rectangle.setPosition(x, y);
    centerText();
}
void Button::setPosition(const sf::Vector2f& pos) { setPosition(pos.x, pos.y); }
const sf::Vector2f& Button::getPosition() { return rectangle.getPosition(); }

void Button::setSize(const float x, const float y) {
    rectangle.setSize(sf::Vector2f(x, y));
    centerText();
}
void Button::setSize(const sf::Vector2f& size) {
    rectangle.setSize(size);
    centerText();
}
const sf::Vector2f& Button::getSize() { return rectangle.getSize(); }

void Button::setText(std::string text) {
    label.setString(text);
    centerText();
}
const std::string Button::getText() { return label.getString(); }

void Button::setCharacterSize(unsigned int size) {
    label.setCharacterSize(size);
    centerText();
}
unsigned int Button::getCharacterSize() { return label.getCharacterSize(); }

void Button::setFillColor(const sf::Color& color) {
    rectangle.setFillColor(color);
}
const sf::Color& Button::getFillColor() { return rectangle.getFillColor(); }

void Button::setTextColor(const sf::Color& color) { label.setFillColor(color); }
const sf::Color& Button::getTextColor() { return label.getFillColor(); }

sf::FloatRect Button::getGlobalBounds() { return rectangle.getGlobalBounds(); }

void Button::setState(const State& state) {
    if (state == State::Released) {
        resetTimeSinceClick();
    }
    currentState = state;
    rectangle.setFillColor(stateColors[state]);
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
            if (e.type == sf::Event::MouseButtonPressed &&
                e.mouseButton.button == sf::Mouse::Left) {
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
    labelBounds = label.getLocalBounds();
    sf::Vector2f rectPos = rectangle.getPosition();
    sf::FloatRect rectBounds = rectangle.getLocalBounds();
    label.setOrigin(labelBounds.left + labelBounds.width / 2,
                    labelBounds.top + labelBounds.height / 2);
    label.setPosition(rectPos.x + rectBounds.width / 2,
                      rectPos.y + rectBounds.height / 2);
}