//
// Created by Vladyslav Kalinchenko on 18.05.2023.
//

#ifndef PJC_PRO1_HEXAGON_H
#define PJC_PRO1_HEXAGON_H
#include <SFML/Graphics.hpp>


class Hexagon : public sf::Drawable {
public:
    sf::CircleShape hexagon;

    Hexagon(double rad);

    Hexagon(double rad, int playerNumber);

    Hexagon(double rad, bool isVisible);


    void setPosition(float x, float y);

    sf::Vector2f getPosition();

    bool checkForClick(sf::Event event);

    bool getIsVisible();

    bool isCaptured() const;

    bool isSelected();

    void select(bool select);

    void setSecondRow(bool select);

    bool isSecondRow();

    void capture(bool playerCaptured);

    void unCapture();

    bool getPlayer() const;

    bool getIsPredefined();

    int getPredefinedPlayer();

private:

    virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const;

    int isPredefined = false;
    bool predefinedPlayer;
    bool captured;
    bool secondRow = false;
    bool selected = false;
    bool player;
    bool isVisible = true;
    float radius;


};




#endif //PJC_PRO1_HEXAGON_H
