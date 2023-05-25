
#include <iostream>
#include <algorithm>

#include "Button.h"
#include "ScoreWriter.h"
#include "Computer.h"
#include "GameBoard.h"

#include <SFML/Graphics.hpp>

const int width = 1920;
const int height = 1080;

bool inMenu = true;
bool inScoreMenu = false;

std::array<Button*, 4> menuButtons = {
        new Button(320,70,"Player VS Player"),
        new Button(300,70,"Player VS PC"),
        new Button(150,70,"Score"),
        new Button(100,70,"Exit")
};

sf::Font font;

sf::Text title;

Button *returnButton = new Button(300,70,"Return");

sf::RenderWindow window(
        sf::VideoMode({width, height}),
        "Hexagon Game"
);

GameBoard board = GameBoard(width, height, &window, inMenu);
//Computer pc = Computer(&board);

auto pollEvents() -> void;

auto drawAll() -> void;

auto drawMenu() -> void;

auto pollButtons(sf::Event event) ->void;

auto setUpText() -> void;

auto drawScoreMenu() ->void;

auto pollScoreButtons(sf::Event event) ->void;

int main() {

    setUpText();

    while (window.isOpen()) {
        window.clear();

        if(!inMenu && !inScoreMenu) board.checkForResults();

        pollEvents();
        drawAll();

        window.display();

        }
    return 0;
}

auto setUpText()->void{
    if(!font.loadFromFile("/Users/vladyslavkalinchenko/CLionProjects/PJC_PRO1/Assets/arial.ttf")){
        std::cout<<"Failed to load title font\n";
    }
    title.setFont(font);
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::White);
    title.setString("Hexagon Game");


}

auto drawAll() -> void {
    if (inScoreMenu && inMenu) drawScoreMenu();
    else if(!inMenu) board.drawGame();
    else if(inMenu && !inScoreMenu) drawMenu();

}

auto drawScoreMenu()->void {
    int y = height / 2 - 120;
    int x = height / 2;
    int yOffset = 0;
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(50);
    scoreText.setFillColor(sf::Color::White);
    ScoreWriter reader = ScoreWriter();
    std::vector<std::string> score = reader.getScoreList();
    for(auto text : score){
        scoreText.setString(text);
        sf::FloatRect textBounds = scoreText.getLocalBounds();
        scoreText.setPosition(x - textBounds.width/4, y - textBounds.height + yOffset);
        //scoreText.setPosition(x, y + yOffset);
        yOffset+= 60;
        window.draw(scoreText);
    }
    returnButton->setPosition(scoreText.getPosition().x, scoreText.getPosition().y + yOffset);
    returnButton->draw(window);

}

auto drawMenu() -> void {
    int y = 0;
    for(auto button : menuButtons){
        button->setPosition(width/2 - (button->getWight()/2), (height / 2 - button->getHeight()) + y);
        button->draw(window);
        y+=100;
    }
    sf::Vector2f titlePos;
    titlePos.x = width/2 - (menuButtons[0]->getWight()/2);
    titlePos.y = (height / 2 - menuButtons[0]->getHeight()) - 100;
    title.setPosition(titlePos.x, titlePos.y);
    window.draw(title);
}

auto pollButtons(sf::Event event) ->void{
    for(auto button : menuButtons){
        if(button->checkForClick(event)){
            std::string input = button->getText();
            if(input == "Player VS Player"){
                inMenu = !inMenu;
//                pcPlay = false;
                board.setPcPlay(false);
            }
            else if(input == "Player VS PC"){
                inMenu = !inMenu;
                board.setPcPlay(true);
//                pcPlay = true;
                //pc = Computer(b);
            }
            else if(input == "Score") {
                inScoreMenu = !inScoreMenu;
            } // implement score!
            else window.close();
        }
    }
}

auto pollScoreButtons(sf::Event event) ->void{
    if(returnButton->checkForClick(event)) inScoreMenu = !inScoreMenu;
}

auto pollEvents() -> void{
    sf::Event event;
    while (window.pollEvent(event)){
        if(event.type == sf::Event::Closed) window.close();
        if (event.type == sf::Event::MouseButtonPressed) {
            if(inMenu && inScoreMenu) pollScoreButtons(event);
            if(inMenu) pollButtons(event);
            else board.pollHexagons(event);
        }
    }
}
