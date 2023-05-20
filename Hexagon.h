//
// Created by Vladyslav Kalinchenko on 18.05.2023.
//

#ifndef PJC_PRO1_HEXAGON_H
#define PJC_PRO1_HEXAGON_H
#include <SFML/Graphics.hpp>


class Hexagon {
public:
    sf::CircleShape hexagon;

    Hexagon(double rad);

    Hexagon(double rad, int playerNumber);

    Hexagon(double rad, bool isVisible);

//    Hexagon(float rad, int q, int r);
//
//
//    float getRotation();
//
//    void setRotaion(float val);

    void setPosition(float x, float y);

    sf::Vector2f getPosition();

    bool checkForClick(sf::Event event);

    bool getIsVisible();
//    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void draw(sf::RenderWindow& window) const;

    bool isCaptured();

    void capture(int playerCaptured);

    int getPlayer() const;

private:
    int player = 3;
    bool isVisible = true;
    float rotation;
    float radius;
    int q; // Column coordinate
    int r; // Row coordinate
    sf::Vector2f position;

//    void calculatePosition();
};




#endif //PJC_PRO1_HEXAGON_H
