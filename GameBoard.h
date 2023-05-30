//
// Created by Vladyslav Kalinchenko on 25.05.2023.
//

#ifndef PJC_PRO1_GAMEBOARD_H
#define PJC_PRO1_GAMEBOARD_H

#include "Hexagon.h"
#include "Button.h"
#include <SFML/Graphics.hpp>


class GameBoard {
public:
    /**
     * Constructor of a gameBoard where game is played
     * @param width
     * @param height
     * @param window
     * @param inMenu
     */
    GameBoard(int width, int height, sf::RenderWindow *window, bool *inMenu);

    ~GameBoard();

    /**
     * Turning on a computer
     * @param isPlay
     */
    auto setPcPlay(bool isPlay) -> void;
    /**
     * Function where every element of a game is drawn
     */
    auto drawGame() ->void;

    /**
     * Function used to check if hexagon was clicked,
     * It detects when hexagon was selected and when player making a move
     * @param event
     */
    auto pollHexagons(sf::Event event)->void;

    /**
     * Function is used for calculating results of a game, it can end a game if
     * some conditions are true
     */
    auto checkForResults() -> void;

private:
    /**
 * Function is called when hexagon is clicked and it is drawing an outline for possible move
     * @param posX
     * @param posY
     */
    auto drawOutline(int posX, int posY) ->void;

    /**
     * Function is used to find a position of hexagon in 2D array
     * @param target
     * @return sf::Vector2f
     */
    auto findPosition(Hexagon *target) ->sf::Vector2f;

    /**
     * Called after when move of hexagon was done
     */
    auto clearOtline()->void;

    /**
     * Called when player is moving on other hexagon
     * @param hex hexagon which was clicked for move
     */
    auto placeHexagon(Hexagon *hexagon)->void;

    /**
     * Used to capture enemy's hexagons if the are near
     * @param hex
     */
    auto checkForNeighbors(Hexagon* hex) ->void;

    /**
     * Is checking if move is posible, used by checkForResults()
     * @param hexagon
     * @return true or false
     */
    auto isPossibleToGo(Hexagon *hexagon) -> bool;

    /**
     * Function called by function checkForResults() or pressing button return
     * It clears a game field and writing a score to a file
     */
    auto endGame() ->void;

    /**
     * Function is called when a player playing against a computer
     * It is used to calculate the best move for the computer
     */
    auto pcGo() ->void;

    /**
     * Function is used by pcGo() it is used to find the move which will capture the most amount of enemy
     * @param maxEnemy vector of map where key is position of a computer hexagon a value is position of targeted hexagon and enemies around it
     * @return sf::Vector2f originX, originY
     */
    auto chooseRandomMove(std::vector<std::map<std::array<int,2>, std::array<int,3>>> maxEnemy)->sf::Vector2f;

    /**
     * Function is searching for an enemy which two hexagons far
     * @param hexagon
     * @return
     */
    auto calculateMoveFar(Hexagon* hexagon)->std::map<std::array<int,2>, std::array<int,3>>;

    /**
 *  * Function is searching for an enemy which one hexagons far
     * @param hexagon
     * @return
     */
    auto calculateMoveNear(Hexagon* hexagon)->std::map<std::array<int,2>, std::array<int,3>>;
    sf::RenderWindow *window;

    float HEX_SIZE = 25;
    int width, height;

    bool playerTurn = true;
    bool isPlacing = false;
    bool pcPlay = false;

    Hexagon* selectedHexagon;
    Hexagon* usedHexagon;

    int redHex = 0;
    int blueHex = 0;
    int totalHex = 58;
    int winner = 3; // 1 - red 0 - blue 3 - none

    bool *inMenu;

    sf::Font font;
    sf::Text playerRedScore;
    sf::Text playerBlueScore;
    sf::Text totalSore;
    Button *returnButton = new Button(300,70, "Return");



    std::array<Hexagon*, 10> b0 = {nullptr, nullptr, nullptr, nullptr, new Hexagon(HEX_SIZE,1), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE, 0)};
    std::array<Hexagon*, 10> b1 = {nullptr, nullptr, nullptr, new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE)};
    std::array<Hexagon*, 10> b2 = {nullptr, nullptr, new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), nullptr};
    std::array<Hexagon*, 10> b3 = {nullptr, new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE, false), new Hexagon(HEX_SIZE),  new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), nullptr};
    std::array<Hexagon*, 10> b4 = {new Hexagon(HEX_SIZE,1), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE, false), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE),  new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE, 0)};
    std::array<Hexagon*, 10> b5 = {nullptr, new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE, false), new Hexagon(HEX_SIZE),  new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), nullptr};
    std::array<Hexagon*, 10> b6 = {nullptr, nullptr, new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), nullptr};
    std::array<Hexagon*, 10> b7 = {nullptr, nullptr, nullptr, new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE)};
    std::array<Hexagon*, 10> b8 = {nullptr, nullptr, nullptr, nullptr, new Hexagon(HEX_SIZE,1), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE, 0)};
    std::array<std::array<Hexagon*, 10>, 9> b = { b0, b1, b2, b3, b4, b5, b6, b7, b8 };

};


#endif //PJC_PRO1_GAMEBOARD_H
