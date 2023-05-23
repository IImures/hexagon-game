//
// Created by Vladyslav Kalinchenko on 22.05.2023.
//

#ifndef PJC_PRO1_BUTTON_H
#define PJC_PRO1_BUTTON_H
#include<string>
#include <SFML/Graphics.hpp>


class Button{
public:

    Button(int wigth, int heigt, std::string text);

    void setPosition(float x, float y);

    void draw(sf::RenderWindow& window) const;

    int getWight();

    int getHeight();

    sf::Vector2f getPosition();

    bool checkForClick(sf::Event event);

    std::string getText();

private:
    int wigth;
    int heigt;
    sf::Font font;
    sf::Text text;
    sf::RectangleShape button;

};


#endif //PJC_PRO1_BUTTON_H