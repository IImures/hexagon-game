
#include "GameBoard.h"
#include "Menu.h"
#include "ScoreMenu.h"

#include <SFML/Graphics.hpp>

const int width = 1920;
const int height = 1080;

bool inMenu = true;
bool inScoreMenu = false;


sf::RenderWindow window(
        sf::VideoMode({width, height}),
        "Hexagon Game"
);

GameBoard board = GameBoard(width, height, &window, &inMenu);
Menu menu = Menu(width, height, &inMenu, &inScoreMenu, &board, &window);
ScoreMenu scoreMenu = ScoreMenu(width, height, &inMenu, &inScoreMenu, &window);

auto pollEvents() -> void;

auto drawAll() -> void;


int main() {

    while (window.isOpen()) {
        window.clear();

        if(!inMenu && !inScoreMenu) board.checkForResults();

        pollEvents();
        drawAll();

        window.display();

        }
    return 0;
}

auto drawAll() -> void {
    if (inScoreMenu && inMenu) scoreMenu.drawScoreMenu();
    else if(!inMenu) board.drawGame();
    else if(inMenu && !inScoreMenu) menu.drawMenu(window);

}


auto pollEvents() -> void{
    sf::Event event;
    while (window.pollEvent(event)){
        if(event.type == sf::Event::Closed) window.close();
        if (event.type == sf::Event::MouseButtonPressed) {
            if(inMenu && inScoreMenu) scoreMenu.pollScoreButtons(event);
            if(inMenu) menu.pollButtons(event);
            else board.pollHexagons(event);
        }
    }
}
