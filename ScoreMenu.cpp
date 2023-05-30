//
// Created by Vladyslav Kalinchenko on 30.05.2023.
//

#include "ScoreMenu.h"
#include "ScoreWriter.h"
#include <iostream>

ScoreMenu::ScoreMenu(int width, int height, bool *inMenu, bool *inScoreMenu, sf::RenderWindow *window) {
    this->width = width;
    this->height =height;
    this->inMenu = inMenu;
    this->inScoreMenu = inScoreMenu;
    this->window = window;

    if(!font.loadFromFile("/Users/vladyslavkalinchenko/CLionProjects/PJC_PRO1/Assets/arial.ttf")){
        std::cout<<"Failed to load title font\n";
    }
}


auto ScoreMenu::drawScoreMenu() -> void {
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
        window->draw(scoreText);
    }
    returnButton->setPosition(scoreText.getPosition().x, scoreText.getPosition().y + yOffset);
    window->draw(*returnButton);

}

auto ScoreMenu::pollScoreButtons(sf::Event event) -> void {
    if(returnButton->checkForClick(event)) *inScoreMenu = false;
}

ScoreMenu::~ScoreMenu() {

}

