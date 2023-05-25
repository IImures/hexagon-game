//
// Created by Vladyslav Kalinchenko on 25.05.2023.
//

#ifndef PJC_PRO1_GAMEBOARD_H
#define PJC_PRO1_GAMEBOARD_H

#include "Hexagon.h"
#include "Button.h"
#include "Computer.h"
#include <SFML/Graphics.hpp>


class GameBoard {
public:

    GameBoard(int width, int height, sf::RenderWindow *window, bool &inMenu);

    auto setPcPlay(bool isPlay) -> void;

    //void setPc(Computer computer);

    auto drawGame() ->void;

    auto drawOutline(int posX, int posY) ->void;

    auto findPosition(Hexagon *target) ->sf::Vector2f;

    auto clearOtline()->void;

    auto placeHexagon(Hexagon *hexagon)->void;

    auto checkForNeighbors(Hexagon* hex) ->void;

    auto checkForResults() -> void;

    auto isPossibleToGo(Hexagon *hexagon) -> bool;

    auto pollHexagons(sf::Event event)->void;

    auto endGame() ->void;





    //auto getBoard();

private:
    auto pcGo() ->void;

    auto chooseRandomMove(std::vector<std::map<std::array<int,2>, std::array<int,3>>> maxEnemy)->sf::Vector2f;

    auto calculateMoveFar(Hexagon* hexagon)->std::map<std::array<int,2>, std::array<int,3>>;

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
    int winner = 0;

    bool &inMenu;
    //Computer pc;

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
