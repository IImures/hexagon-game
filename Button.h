//
// Created by Vladyslav Kalinchenko on 22.05.2023.
//

#ifndef PJC_PRO1_BUTTON_H
#define PJC_PRO1_BUTTON_H
#include<string>
#include <SFML/Graphics.hpp>


class Button : public sf::Drawable{
public:

    Button(int wigth, int heigt, std::string text);

    void setPosition(float x, float y);

    int getWight() const;

    int getHeight() const;

    /**
     * Used to check if button was clicked
     * @param event
     * @return
     */
    bool checkForClick(sf::Event event);

    std::string getText() const;

private:

    virtual void draw(sf::RenderTarget& target,sf::RenderStates states)const;


    int wigth;
    int heigt;
    sf::Font font;
    sf::Text text;
    sf::RectangleShape button;


};


#endif //PJC_PRO1_BUTTON_H
