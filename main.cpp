
#include <iostream>
#include <algorithm>
#include "Hexagon.h"
#include <SFML/Graphics.hpp>

const int width = 1920;
const int height = 1080;
Hexagon* selectedHexagon;
Hexagon* usedHexagon;
float HEX_SIZE = 25;
bool playerTurn = true;
bool isPlacing = false;
sf::Vector2f currHex; // coordinates of current used hexagon used to check for enemies hexagons

std::array<Hexagon*, 10> b0 = {nullptr, nullptr, nullptr, nullptr, new Hexagon(HEX_SIZE,1), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE, 0)};
std::array<Hexagon*, 10> b1 = {nullptr, nullptr, nullptr, new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE)};
std::array<Hexagon*, 10> b2 = {nullptr, nullptr, new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), nullptr};
std::array<Hexagon*, 10> b3 = {nullptr, new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE, false), new Hexagon(HEX_SIZE),  new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), nullptr};
std::array<Hexagon*, 10> b4 = {new Hexagon(HEX_SIZE,1), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE, false), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE),  new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE, 0)};
std::array<Hexagon*, 10> b5 = {nullptr, new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE, false), new Hexagon(HEX_SIZE),  new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), nullptr};
std::array<Hexagon*, 10> b6 = {nullptr, nullptr, new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), nullptr};
std::array<Hexagon*, 10> b7 = {nullptr, nullptr, nullptr, new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE)};
std::array<Hexagon*, 10> b8 = {nullptr, nullptr, nullptr, nullptr, new Hexagon(HEX_SIZE,1), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE), new Hexagon(HEX_SIZE, 0)};
std::array<std::array<Hexagon*, 10>, 9> b= { b0, b1, b2, b3, b4, b5, b6, b7, b8 };

sf::RenderWindow window(
        sf::VideoMode({width, height}),
        "Hexagon Game"
);

auto pollEvents() -> void;

auto drawAll() -> void;

auto drawOutline(int posX, int posY) ->void;

auto findPosition() ->void;

auto clearOtline()->void;

auto placeHexagon(Hexagon *hexagon)->void;

auto checkForNeighbors(Hexagon* hex) ->void;

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
    for(int i = 0; i < b.size(); i++){
        auto hexTab = b[i];
        for(int j = 0; j < hexTab.size(); j++){
            if(b[i][j] == nullptr) continue;
            if(b[i][j]->getPosition().x == selectedHexagon->getPosition().x &&
            b[i][j]->getPosition().y == selectedHexagon->getPosition().y){
//                std::cout<< b[i][j]->getPosition().x << " " << b[i][j]->getPosition().y << '\n';
//                std::cout<< selectedHexagon->getPosition().x << " " << selectedHexagon->getPosition().y << '\n';
                std::cout << "Position: (" << i << ", " << j << ")\n";
                currHex.x = j;
                currHex.y = i;
                if(playerTurn == b[i][j]->getPlayer() ) drawOutline(j, i);
                else if (playerTurn == b[i][j]->getPlayer()) drawOutline(j, i);
            }
        }
    }
    usedHexagon = selectedHexagon;
    selectedHexagon = nullptr;
}

auto drawOutline(int posX, int posY)->void {
    if(posY < 4) {
        std::array<int, 6> neighbors[] = {
                {-1, 0}, {-1, 1}, {0, 1},
                {1, 0}, {1, -1}, {0, -1}
        };

        for (auto & neighbor : neighbors) {
            int neighborX = posX + neighbor[0];
            int neighborY = posY + neighbor[1];
//        for (auto & neighbor : neighbors) {
//            int neighborX = posX + neighbor[0];
//            int neighborY = posY + neighbor[1];
            Hexagon *nearHexagon = b[neighborY][neighborX];

            if (neighborY >= 0 && neighborY < b.size() && neighborX >= 0 && neighborX < b[neighborY].size() &&
                    nearHexagon != nullptr &&
                !nearHexagon->isCaptured()) {
                nearHexagon->hexagon.setOutlineColor(sf::Color::Green);
                nearHexagon->select(true);

                for (auto & neighborFar : neighbors) {
                    int farNeighborX = neighborX + neighborFar[0];
                    int farNeighborY = neighborY + neighborFar[1];

                    Hexagon *farHexagon = b[farNeighborY][farNeighborX];

                    if (farNeighborY >= 0 && farNeighborY < b.size() && farNeighborX >= 0 && farNeighborX < b[farNeighborY].size() && b[farNeighborY][farNeighborX] != nullptr) {
                        if (farHexagon->hexagon.getOutlineColor() == sf::Color::Black &&
                            !farHexagon->isCaptured()) {
                            farHexagon->hexagon.setOutlineColor(sf::Color::Yellow);
                            farHexagon->setSecondRow(true);
                        }
                    }
                }
            }
        }
    }else if(posY == 4){
        std::array<int, 6> neighbors[] = {
                {-1, 0},
                {1, 1},
                {0,  1},
                {1,  0},
                {1,  -1},
                {0,  -1}
        };
        for (auto & neighbor : neighbors) {
            int neighborX = posX + neighbor[0];
            int neighborY = posY + neighbor[1];

            Hexagon *nearHexagon = b[neighborY][neighborX];

            if (neighborY >= 0 && neighborY < b.size() && neighborX >= 0 && neighborX < b[neighborY].size() &&
                nearHexagon != nullptr &&
                !nearHexagon->isCaptured()) {
                nearHexagon->hexagon.setOutlineColor(sf::Color::Green);
                nearHexagon->select(true);

                for (auto & neighborFar : neighbors) {
                    int farNeighborX = neighborX + neighborFar[0];
                    int farNeighborY = neighborY + neighborFar[1];

                    Hexagon *farHexagon = b[farNeighborY][farNeighborX];

                    if (farNeighborY >= 0 && farNeighborY < b.size() && farNeighborX >= 0 && farNeighborX < b[farNeighborY].size() && b[farNeighborY][farNeighborX] != nullptr) {
                        if (farHexagon->hexagon.getOutlineColor() == sf::Color::Black &&
                            !farHexagon->isCaptured()) {
                            farHexagon->hexagon.setOutlineColor(sf::Color::Yellow);
                            farHexagon->setSecondRow(true);
                        }
                    }
                }
            }
        }
    }else{
        std::array<int, 6> neighbors[] = {
                {-1, 0},
                {1, 1},
                {0,  1},
                {1,  0},
                {-1,  -1},
                {0,  -1}
        };
        for (auto & neighbor : neighbors) {
            int neighborX = posX + neighbor[0];
            int neighborY = posY + neighbor[1];

            Hexagon *nearHexagon = b[neighborY][neighborX];

            if (neighborY >= 0 && neighborY < b.size() && neighborX >= 0 && neighborX < b[neighborY].size() &&
                nearHexagon != nullptr &&
                !nearHexagon->isCaptured()) {
                nearHexagon->hexagon.setOutlineColor(sf::Color::Green);
                nearHexagon->select(true);

                for (auto & neighborFar : neighbors) {
                    int farNeighborX = neighborX + neighborFar[0];
                    int farNeighborY = neighborY + neighborFar[1];

                    Hexagon *farHexagon = b[farNeighborY][farNeighborX];

                    if (farNeighborY >= 0 && farNeighborY < b.size() && farNeighborX >= 0 && farNeighborX < b[farNeighborY].size() && b[farNeighborY][farNeighborX] != nullptr) {
                        if (farHexagon->hexagon.getOutlineColor() == sf::Color::Black &&
                            !farHexagon->isCaptured()) {
                            farHexagon->hexagon.setOutlineColor(sf::Color::Yellow);
                            farHexagon->setSecondRow(true);
                        }
                    }
                }
            }
        }
    }
    isPlacing = true;
}

auto clearOtline()->void{
    for(auto hexTab : b){
        for(auto hx : hexTab) {
            if(hx == nullptr) continue;
            hx->hexagon.setOutlineColor(sf::Color::Black);
        }
    }
}

auto placeHexagon(Hexagon *hex)->void{
//    if(hexagon->hexagon.getOutlineColor() == sf::Color::Green) hexagon->capture(playerTurn);
//    else clearOtline();
//    isPlacing = false;


    if(hex->isSelected()){
        hex->capture(playerTurn);
        playerTurn = !playerTurn;
        checkForNeighbors(hex);
    }else if(hex->isSecondRow()){
        usedHexagon->unCapture();
        hex->capture(playerTurn);
        playerTurn = !playerTurn;
        checkForNeighbors(hex);
    }
    else clearOtline();
    for(auto hexTab : b)
        for(auto hx : hexTab)
            if(hx == nullptr) continue;
            else{
                hx->setSecondRow(false);
                hx->select(false);
            }
    isPlacing = false;

}

void checkForNeighbors(Hexagon* hex) {
    int posY, posX;

    for (int i = 0; i < b.size(); i++) {
        auto hexTab = b[i];
        for (int j = 0; j < hexTab.size(); j++) {
            if (b[i][j] == nullptr) continue;
            if (b[i][j]->getPosition().x == hex->getPosition().x &&
                b[i][j]->getPosition().y == hex->getPosition().y) {
                posX = j;
                posY = i;
            }
        }
    }
    if (posY < 4) {
        std::array<int, 6> neighbors[] = {
                {-1, 0},
                {-1, 1},
                {0,  1},
                {1,  0},
                {1,  -1},
                {0,  -1}
        };
        for (auto &neighbor: neighbors) {
            int neighborX = posX + neighbor[0];
            int neighborY = posY + neighbor[1];

            Hexagon *nearHexagon = b[neighborY][neighborX];
            if (neighborY >= 0 && neighborY < b.size() && neighborX >= 0 && neighborX < b[neighborY].size() &&
            nearHexagon != nullptr &&
            nearHexagon->isCaptured() && nearHexagon->getPlayer() != usedHexagon->getPlayer()) {
                nearHexagon->capture(usedHexagon->getPlayer());
            }
        }
    }else if(posY == 4){
        std::array<int, 6> neighbors[] = {
                {-1, 0},
                {1, 1},
                {0,  1},
                {1,  0},
                {1,  -1},
                {0,  -1}
        };
        for (auto &neighbor: neighbors) {
            int neighborX = posX + neighbor[0];
            int neighborY = posY + neighbor[1];

            Hexagon *nearHexagon = b[neighborY][neighborX];

            if (neighborY >= 0 && neighborY < b.size() && neighborX >= 0 && neighborX < b[neighborY].size() &&
                 nearHexagon != nullptr &&
                 nearHexagon->isCaptured() && nearHexagon->getPlayer() != usedHexagon->getPlayer())
                {
                    nearHexagon->capture(usedHexagon->getPlayer());
                }
            }
    }else{
        std::array<int, 6> neighbors[] = {
            {-1, 0},
            {1, 1},
            {0,  1},
            {1,  0},
            {-1,  -1},
            {0,  -1}
        };
        for (auto &neighbor: neighbors) {
            int neighborX = posX + neighbor[0];
            int neighborY = posY + neighbor[1];

            Hexagon *nearHexagon = b[neighborY][neighborX];

            if (neighborY >= 0 && neighborY < b.size() && neighborX >= 0 && neighborX < b[neighborY].size() &&
                nearHexagon != nullptr &&
                nearHexagon->isCaptured() && nearHexagon->getPlayer() != usedHexagon->getPlayer()) {
                nearHexagon->capture(usedHexagon->getPlayer());
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
                        clearOtline();
                        if(!isPlacing) selectedHexagon = hx;
                        else placeHexagon(hx);
                    }
                }
        }
    }
}
