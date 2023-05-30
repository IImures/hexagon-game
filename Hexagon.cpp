//
// Created by Vladyslav Kalinchenko on 18.05.2023.
//

#include "Hexagon.h"
#include <iostream>


Hexagon::Hexagon(double rad) {
    radius = rad;
    this->hexagon = sf::CircleShape(radius, 6);
    hexagon.setFillColor(sf::Color(255,255,255));
    hexagon.setOutlineColor(sf::Color(0,0,0));
    hexagon.setOutlineThickness(5);
}

Hexagon::Hexagon(double rad, int playerNumber) {
    isPredefined = true;
    predefinedPlayer = playerNumber;
    radius = rad;
    player = playerNumber;
    captured = true;
    this->hexagon = sf::CircleShape(radius, 6);
    if(player == 1) hexagon.setFillColor(sf::Color::Red);
    if(player == 0) hexagon.setFillColor(sf::Color::Blue);
    hexagon.setOutlineColor(sf::Color(0,0,0));
    hexagon.setOutlineThickness(5);
}

Hexagon::Hexagon(double rad, bool isVisible) {
    radius = rad;
    this->isVisible = isVisible;
    this->hexagon = sf::CircleShape(radius, 6);
    hexagon.setFillColor(sf::Color(rand()%255,rand()%255,rand()%255));
    hexagon.setOutlineColor(sf::Color(255,255,255));
    hexagon.setOutlineThickness(0);
}

//void Hexagon::draw(sf::RenderWindow& window) const {
//    window.draw(hexagon);
//}

bool Hexagon::getIsVisible() {
    return isVisible;
}

void Hexagon::setPosition(float x, float y) {
    hexagon.setPosition(x, y);
}

bool Hexagon::checkForClick(sf::Event event) {
    if ((event.mouseButton.x < (hexagon.getPosition().x + radius * 2 - 10) &&
         event.mouseButton.x > hexagon.getPosition().x) &&
        (event.mouseButton.y < (hexagon.getPosition().y + radius * 2 - 10) &&
         event.mouseButton.y > hexagon.getPosition().y)) {
        return true;
    }
    return false;
}

sf::Vector2f Hexagon::getPosition() {
    return hexagon.getPosition();
}

bool Hexagon::isCaptured() const {
    return captured;
}

bool Hexagon::getPlayer() const {
    return player;
}

void Hexagon::capture(bool playerCaptured) {
    if(playerCaptured){
        captured = true;
        hexagon.setFillColor(sf::Color::Red);
        player = true;
    }
    if(!playerCaptured){
        captured = true;
        hexagon.setFillColor(sf::Color::Blue);
        player = false;
    }
}

bool Hexagon::isSelected() {
    return selected;
}

void Hexagon::select(bool select) {
    selected = select;
}

void Hexagon::setSecondRow(bool select) {
    secondRow = select;
}

bool Hexagon::isSecondRow() {
    return secondRow;
}

void Hexagon::unCapture() {
    hexagon.setFillColor(sf::Color::White);
    secondRow = false;
    selected = false;
    captured = false;
}

void Hexagon::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(hexagon, states);
}

bool Hexagon::getIsPredefined() {
    return isPredefined;
}

int Hexagon::getPredefinedPlayer() {
    return predefinedPlayer;
}

//void Hexagon::draw(sf::RenderTarget &target, sf::RenderStates states) const {
//    target.draw(hexagon);
//}


