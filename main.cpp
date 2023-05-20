
#include <iostream>
#include <algorithm>
#include "Hexagon.h"
#include <SFML/Graphics.hpp>

const int width = 1920;
const int height = 1080;
bool isClicked = false;
Hexagon* selectedHexagon;
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
std::array<std::array<Hexagon*, 10>, 9> b= { b0, b1, b2, b3, b4, b5, b6, b7, b8 };

sf::RenderWindow window(
        sf::VideoMode({width, height}),
        "Hexagon Game"
);

auto pollEvents() -> void;

auto drawAll() -> void;

auto drawOutline(int posX, int posY) ->void;

auto findPosition()->void;

int main() {

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

    if(selectedHexagon != nullptr) findPosition();
}

auto findPosition()->void{
//    for (size_t i = 0; i < b.size(); i++) {
//        auto& hexTab = b[i];
//        auto find = std::find(hexTab.begin(), hexTab.end(), selectedHexagon);
//        if (find != hexTab.end()) {
//            size_t position = std::distance(hexTab.begin(), find);
//            int x = position;
//            int y = i;
//            std::cout << "Position: (" << i << ", " << position << ")\n";
//            drawOutline(x, y);
//            break;
//        }
//    }
    for(int i = 0; i < b.size(); i++){
        auto hexTab = b[i];
        for(int j = 0; j < hexTab.size(); j++){
            if(b[i][j] == nullptr) continue;
            if(b[i][j]->getPosition().x == selectedHexagon->getPosition().x &&
            b[i][j]->getPosition().y == selectedHexagon->getPosition().y){
                std::cout<< b[i][j]->getPosition().x << " " << b[i][j]->getPosition().y << '\n';
                std::cout<< selectedHexagon->getPosition().x << " " << selectedHexagon->getPosition().y << '\n';
                std::cout << "Position: (" << i << ", " << j << ")\n";
                drawOutline(j, i);
            }
        }
    }
    selectedHexagon = nullptr;

}

auto drawOutline(int posX, int posY)->void {
    int x = posX - 2;
    int xConst = posX + 1;
    for(int y = posY - 1; y <= posY + 1; y++) {
        if (y < posY) {
            x = posX;
            xConst = posX + 1;
        }
        else if (y == posY) {
            x = posX - 1;
            xConst;
        }
        else if(y > posY) {
            x = posX;
            xConst = posX + 1;
        }
        for ( ; x <= xConst; x++) {
            if (y >= 0 && y < b.size() && x >= 0 && x < b[y].size() && b[y][x] != nullptr) {
               std::cout<< y << " " << x << '\n';
               b[y][x]->hexagon.setOutlineColor(sf::Color(0,255,0));
            }
        }
    }
}

auto pollEvents() -> void{
    sf::Event event;
    while (window.pollEvent(event)){
        if(event.type == sf::Event::Closed) window.close();
        if (event.type == sf::Event::MouseButtonPressed) {
            for(const auto hexTab : b)
                for (const auto hx: hexTab) {
                    if(hx == nullptr) continue;
                    if(hx->checkForClick(event)){
                        selectedHexagon = hx;
                        std::cout<< selectedHexagon->getPosition().x << " " << selectedHexagon->getPosition().y << '\n';
                    }
                }
        }
    }
}
