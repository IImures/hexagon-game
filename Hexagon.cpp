//
// Created by Vladyslav Kalinchenko on 18.05.2023.
//

#include "Hexagon.h"
#include <iostream>


Hexagon::Hexagon(double rad) {
    radius = rad;
    this->hexagon = sf::CircleShape(radius, 6);
    hexagon.setFillColor(sf::Color(255,255,255));
    //hexagon.setRotation(60);
    hexagon.setOutlineColor(sf::Color(0,0,0));
    hexagon.setOutlineThickness(5);
}

Hexagon::Hexagon(double rad, int playerNumber) {
    radius = rad;
    player = playerNumber;
    captured = true;
    this->hexagon = sf::CircleShape(radius, 6);
    if(player == 1) hexagon.setFillColor(sf::Color::Red);
    if(player == 0) hexagon.setFillColor(sf::Color::Blue);
    //hexagon.setRotation(60);
    hexagon.setOutlineColor(sf::Color(0,0,0));
    hexagon.setOutlineThickness(5);
}

Hexagon::Hexagon(double rad, bool isVisible) {
    radius = rad;
    this->isVisible = isVisible;
    this->hexagon = sf::CircleShape(radius, 6);
    hexagon.setFillColor(sf::Color(rand()%255,rand()%255,rand()%255));
    //hexagon.setRotation(60);
    hexagon.setOutlineColor(sf::Color(255,255,255));
    hexagon.setOutlineThickness(0);
}


//void Hexagon::calculatePosition() {
//    // Calculate the position of the hexagon based on q and r coordinates
//    // ...
//
//    float x = radius * 3.0 / 2.0 * q;
//    //float y = radius * 2 * r;
//    float y = radius  * sqrt(3) * (r + q / 2.0);
//
//    position.x = 1980 / 2.0 + x;
//    position.y = 1080 / 2.0 + y;
//    std::cout<< position.x << " " << position.y << " ";
//
//}


//float Hexagon::getRotation() {
//    return rotation;
//}
//
//void Hexagon::setRotaion(float val) {
//    hexagon.setRotation(val);
//    std::cout<<val << " ";
//    rotation = val;
//}

void Hexagon::draw(sf::RenderWindow& window) const {
    window.draw(hexagon);
}

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
}

sf::Vector2f Hexagon::getPosition() {
    return hexagon.getPosition();
}

bool Hexagon::isCaptured() const {
    return captured;
    return false;
}

bool Hexagon::getPlayer() const {
    return player;
}

void Hexagon::capture(bool playerCaptured) {
    if(playerCaptured){
        captured = true;
        hexagon.setFillColor(sf::Color::Red);
        player = 1;
    }
    if(!playerCaptured){
        captured = true;
        hexagon.setFillColor(sf::Color::Blue);
        player = 0;
    }
}

bool Hexagon::isSelected() {
    return selected;
}

void Hexagon::select(bool select) {
    selected = select;
}

//void Hexagon::draw(sf::RenderTarget &target, sf::RenderStates states) const {
//    target.draw(hexagon);
//}


