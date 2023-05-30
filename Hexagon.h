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

    /**
     * True if someone on this hexagon
     * @return
     */
    bool isCaptured() const;

    /**
     * Selected if it near clicked hexagon, this function is used
     * to decide to copy hexagon or move
     * @return bool
     */
    bool isSelected();

    /**
     * Ability to select hexagon then it became able to capture it
     * @param select
     */
    void select(bool select);

    /**
     * Ability to select hexagon then it became able to move on it
     * @param select
     */
    void setSecondRow(bool select);

    /**
     * Second if it far from clicked hexagon, this function is used
     * to decide to copy hexagon or move
     * @return bool
     */
    bool isSecondRow();

    /**
     * Used to capture hexagon
     * @param playerCaptured
     */
    void capture(bool playerCaptured);

    /**
     * Used to uncapture hexagon
     * @param playerCaptured
     */
    void unCapture();

    /**
     * Usually it is used with isCaptured() to detect if it really player on hexagon
     * @return
     */
    bool getPlayer() const;

    /**
     * Predefined hexagons used to regenerate map doesnt have impact on a gameplay
     * @return
     */
    bool getIsPredefined();

    /**
     * PredefinedPlayer hexagons used to regenerate map doesnt have impact on a gameplay
     * @return
     */
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
