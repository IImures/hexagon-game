
#include <iostream>
#include "Hexagon.h"
#include <SFML/Graphics.hpp>

const int width = 1920;
const int height = 1080;
int pos = 1;
std::vector<Hexagon> board;
int BOARD_RADIUS = 5;
float HEX_SIZE = 25;
std::array<Hexagon*, 10> b0 = {nullptr, nullptr, nullptr, nullptr, new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE)};
std::array<Hexagon*, 10> b1 = {nullptr, nullptr, nullptr, new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE)};
std::array<Hexagon*, 10> b2 = {nullptr, nullptr, new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), nullptr};
std::array<Hexagon*, 10> b3 = {nullptr, new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE, false), new Hexagon(HEX_SIZE),  new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), nullptr};
std::array<Hexagon*, 10> b4 = {new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE, false), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE),  new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE)};
std::array<Hexagon*, 10> b5 = {nullptr, new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE, false), new Hexagon(HEX_SIZE),  new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), nullptr};
std::array<Hexagon*, 10> b6 = {nullptr, nullptr, new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), nullptr};
std::array<Hexagon*, 10> b7 = {nullptr, nullptr, nullptr, new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE)};
std::array<Hexagon*, 10> b8 = {nullptr, nullptr, nullptr, nullptr, new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE)};
std::array<std::array<Hexagon*, 10>, 9> b= { b0, b1, b2, b3, b4, b5, b6, b7, b8
//                             {nullptr, nullptr, nullptr, nullptr,new Hexagon(20), nullptr, nullptr, nullptr, nullptr, nullptr},
//                             {nullptr, nullptr, nullptr, new Hexagon(20), new Hexagon(20),  nullptr, nullptr, nullptr, nullptr},
//                             {nullptr, nullptr, nullptr, new Hexagon(20), new Hexagon(20), new Hexagon(20),  nullptr, nullptr, nullptr},
//                             {nullptr, nullptr, new Hexagon(20), new Hexagon(20), new Hexagon(20), new Hexagon(20), nullptr, nullptr, nullptr},
//                             {nullptr, new Hexagon(20), new Hexagon(20), new Hexagon(20), new Hexagon(20), new Hexagon(20), nullptr, nullptr, nullptr},
//                             {new Hexagon(20), new Hexagon(20), new Hexagon(20), new Hexagon(20), new Hexagon(20), new Hexagon(20),  new Hexagon(20), new Hexagon(20), new Hexagon(20)}
//                             {new Hexagon(20), new Hexagon(20), new Hexagon(20), new Hexagon(20), new Hexagon(20), new Hexagon(20),  new Hexagon(20), new Hexagon(20), new Hexagon(20)},
//                             {new Hexagon(20), new Hexagon(20), new Hexagon(20), new Hexagon(20), new Hexagon(20), new Hexagon(20),  new Hexagon(20), new Hexagon(20), new Hexagon(20)},
//                             {new Hexagon(20), new Hexagon(20), new Hexagon(20), new Hexagon(20), new Hexagon(20), new Hexagon(20),  new Hexagon(20), new Hexagon(20), new Hexagon(20)},
//                             {new Hexagon(20), new Hexagon(20), new Hexagon(20), new Hexagon(20), new Hexagon(20), new Hexagon(20),  new Hexagon(20), new Hexagon(20), new Hexagon(20)}
};

sf::RenderWindow window(
        sf::VideoMode({width, height}),
        "Hexagon Game"
);

auto pollEvents() -> void;

auto drawAll() -> void;

auto makeBoard(int BR) -> void;



int main() {

//    for(int q = -BOARD_RADIUS; q < BOARD_RADIUS; q++){
//        for(int r = q; r < BOARD_RADIUS; r++){
//            if(r == 0) break;
//            board.push_back(Hexagon(HEX_SIZE, q, r));
//        }
//    }
    //makeBoard(BOARD_RADIUS);
//    for(int q = -BOARD_RADIUS; q < BOARD_RADIUS; q++){
//        for(int r = -BOARD_RADIUS; r < BOARD_RADIUS; r++){
//            board.push_back(Hexagon(25, r, 0));
//        }
//    }
    //for(Hexagon hexagon : board) hexagon.setRotaion(hexagon.getRotation() + 24);

    while (window.isOpen()) {
        window.clear();

        pollEvents();

        drawAll();
        window.display();

        }
    return 0;
}

auto drawAll() -> void{
    int y = 0;
    for(auto hexTab : b){
        int x = 0;
        for(auto hx : hexTab){
            if(hx == nullptr) {
                x+=25;
                continue;
            }if(!hx->getIsVisible()){
                x += 50;
                continue;
            }
            hx->setPosition(width/4 + x, height/4 +  y);
            hx->draw(window);
            x+=50;
        }
        y+=40;
    }
}

auto pollEvents() -> void{
    sf::Event event;
    while (window.pollEvent(event)){
        if(event.type == sf::Event::Closed) window.close();
        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2f mousePosition = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
            for(const auto hexTab : b)
                for (const auto hx: hexTab) {
                    if(hx == nullptr) continue;
                    hx->checkForClick(event);
                }
        }
    }
}


void makeBoard(int BR)
{

    for (int q = -BOARD_RADIUS; q < BOARD_RADIUS; q++) {
        for (int r = -BOARD_RADIUS; r < BOARD_RADIUS; r++) {
            board.push_back(Hexagon(20,q, r));
        }
    }





//    int l = 2 * BR - 1;
//
//
//    /**** Print upper part *****/
//    for (int i = 0; i < BR; i++)
//    {
//        // loop for printing the
//        // whitespaces and the star
//        for (int k = 0; k <= BR; k++)
//        {
//            board.push_back(Hexagon(20, i, k));
//        }
//    }

//    /**** Print middle part *****/
//    // Here we print two vertical lines
//    for (int m = 0; m < BR - 2; m++)
//    {
//        for (int j = 0; j < l; j++)
//        {
//                board.push_back(Hexagon(20, m, j));
//        }
//    }
//
//    /**** Print Lower part *****/
//    int r = BR - 1;
//    for (int h = r; h >= 0; h--)
//    {
//        int elem = h + BR;
//        for (int k = 0; k < elem; k++)
//        {
//            if ((k == BR + h - 1) || (k == BR - h - 1))
//                board.push_back(Hexagon(20, h, k));
//            else
//                board.push_back(Hexagon(20, h, k));
//        }
//    }
}

//#include <iostream>
//#include <SFML/Graphics.hpp>
//int main() {
//    sf::RenderWindow window(
//            sf::VideoMode({800, 600}),
//            "TITILE");
//    float ground = window.getSize().y - 100, velX = 0.0, velY = 0, gravity = 0.00001;
//    sf::Event event;
//    sf::CircleShape cir(30,6);
//    sf::Texture mario;
//    if (!mario.loadFromFile("Assets\\mario_t.png")) {
//        std::cout << "Texture could not load";
//    } else {
////        cir.setTexture(&mario);
//    }
//    cir.setPosition({100, ground});
//    while (window.isOpen()) {
//        window.clear();
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed) {
//                window.close();
//            }
//            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
//                velY = -0.1;
//            if (event.type == sf::Event::MouseButtonPressed) {
//                if ((event.mouseButton.x <= (cir.getPosition().x + cir.getRadius() * 2) &&
//                     event.mouseButton.x > cir.getPosition().x) &&
//                    (event.mouseButton.y <= (cir.getPosition().y + cir.getRadius() * 2) &&
//                     event.mouseButton.y > cir.getPosition().y)) {
//                    std::cout<<cir.getPosition().y<<" "<<cir.getPosition().x<<"\n";
//                    std::cout<<event.mouseButton.y<<" "<<event.mouseButton.x<<"\n";
//                    cir.setFillColor(sf::Color(rand()%255,rand()%255,rand()%255));
//                }
//            }
//        }
//        cir.move({velX, velY});
//        window.draw(cir);
//        if (cir.getPosition().x < 0 || cir.getPosition().x > window.getSize().x - cir.getRadius() * 2)
//            velX *= -1;
//        if (cir.getPosition().y >= ground) velY = 0;
//        else velY += gravity;
//        window.display();
//    }
//    return 0;
//}