//
// Created by Vladyslav Kalinchenko on 30.05.2023.
//

#ifndef PJC_PRO1_MENU_H
#define PJC_PRO1_MENU_H

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "GameBoard.h"

class Menu {
public:

    /**
     * Constructor of menu
     * @param width
     * @param height
     * @param inMenu
     * @param inScoreMenu
     * @param board
     * @param window
     */
    Menu(int width, int height, bool *inMenu, bool *inScoreMenu, GameBoard *board, sf::RenderWindow *window);

    ~Menu();

    /**
     * Drawing all elements of menu
     * @param window
     */
    auto drawMenu(sf::RenderWindow &window) -> void;

    /**
     * Checking if any button is pressed
     * @param event
     */
    auto pollButtons(sf::Event event) ->void;

private:

    /**
     * Load a font
     */
    auto setUpText() -> void;

    bool *inMenu;
    bool *inScoreMenu;

    GameBoard *board;
    sf::RenderWindow *window;

    int width;
    int height;
    sf::Font font;

    sf::Text title;

    std::array<Button*, 4> menuButtons = {
            new Button(320,70,"Player VS Player"),
            new Button(300,70,"Player VS PC"),
            new Button(150,70,"Score"),
            new Button(100,70,"Exit")
    };

};


#endif //PJC_PRO1_MENU_H
