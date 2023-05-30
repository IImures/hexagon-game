//
// Created by Vladyslav Kalinchenko on 22.05.2023.
//

#include "Button.h"

#include <iostream>

Button::Button(int wigth, int heigt, std::string text) {
    this->wigth = wigth;
    this->heigt = heigt;

    if(!font.loadFromFile("/Users/vladyslavkalinchenko/CLionProjects/PJC_PRO1/Assets/arial.ttf")){
        std::cout<<"Failed to load a font\n";
    }
    this->text.setFont(font);
    this->text.setString(text);
    this->text.setCharacterSize(40);
    this->text.setFillColor(sf::Color::Black);
    this->button = sf::RectangleShape(sf::Vector2f(wigth, heigt));
}

void Button::setPosition(float x, float y) {
    button.setPosition(x, y);
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition(x + (wigth - textBounds.width)/2, y + (heigt - textBounds.height- 20)/2);
}


//void Button::draw(sf::RenderWindow &window) const {
//    window.draw(button);
//    window.draw(text);
//}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(button, states);
    target.draw(text, states);
}

int Button::getWight() {
    return wigth;
}

int Button::getHeight() {
    return heigt;
}

sf::Vector2f Button::getPosition() {
    return button.getPosition();
}

bool Button::checkForClick(sf::Event event) {
    if ((event.mouseButton.x >= button.getPosition().x &&
         event.mouseButton.x <= (button.getPosition().x + button.getSize().x)) &&
        (event.mouseButton.y >= button.getPosition().y &&
         event.mouseButton.y <= (button.getPosition().y + button.getSize().y))) {
        return true;
    }
}

std::string Button::getText() {
    return text.getString();
}
