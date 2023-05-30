//
// Created by Vladyslav Kalinchenko on 30.05.2023.
//

#ifndef PJC_PRO1_SCOREMENU_H
#define PJC_PRO1_SCOREMENU_H

#include <SFML/Graphics.hpp>
#include "Button.h"

class ScoreMenu {
public:
    ScoreMenu(int width, int height, bool *inMenu, bool *inScoreMenu, sf::RenderWindow *window);

    ~ScoreMenu();

    /**
     * Used to poll scoreButtons
     * @param event
     */
    auto pollScoreButtons(sf::Event event) ->void;

    /**
     * Used to draw scoreMenu
     */
    auto drawScoreMenu()->void;

private:
    int width;
    int height;

    bool *inMenu;
    bool *inScoreMenu;

    sf::Font font;
    sf::RenderWindow *window;

    Button *returnButton = new Button(300,70,"Return");
};


#endif //PJC_PRO1_SCOREMENU_H
