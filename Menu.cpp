//
// Created by Vladyslav Kalinchenko on 30.05.2023.
//

#include "Menu.h"
#include <iostream>

Menu::Menu(int width, int height, bool *inMenu, bool *inScoreMenu, GameBoard *board, sf::RenderWindow *window) {
    this->window = window;
    this->board = board;
    this->inMenu = inMenu;
    this->inScoreMenu = inScoreMenu;
    this->width = width;
    this->height = height;
    setUpText();
}

Menu::~Menu() {

}

auto Menu::setUpText()->void{
    if(!font.loadFromFile("/Users/vladyslavkalinchenko/CLionProjects/PJC_PRO1/Assets/arial.ttf")){
        std::cout<<"Failed to load title font\n";
    }
    title.setFont(font);
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::White);
    title.setString("Hexagon Game");

}

auto Menu::drawMenu(sf::RenderWindow &window) -> void {
    int y = 0;
    for(auto button : menuButtons){
        button->setPosition(width/2 - (button->getWight()/2), (height / 2 - button->getHeight()) + y);
        //button->draw(window);
        window.draw(*button);
        y+=100;
    }
    sf::Vector2f titlePos;
    titlePos.x = width/2 - (menuButtons[0]->getWight()/2);
    titlePos.y = (height / 2 - menuButtons[0]->getHeight()) - 100;
    title.setPosition(titlePos.x, titlePos.y);
    window.draw(title);
}

auto Menu::pollButtons(sf::Event event) ->void{
    for(auto button : menuButtons){
        if(button->checkForClick(event)){
            std::string input = button->getText();
            if(input == "Player VS Player"){
                *inMenu = !inMenu;

                board->setPcPlay(false);
            }
            else if(input == "Player VS PC"){
                *inMenu = !inMenu;
                board->setPcPlay(true);
            }
            else if(input == "Score") {
                *inScoreMenu = true;
            }
            else window->close();
        }
    }
}

