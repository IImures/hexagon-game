
#include <iostream>
#include <algorithm>

#include "Button.h"
#include "Hexagon.h"

#include <SFML/Graphics.hpp>

const int width = 1920;
const int height = 1080;
Hexagon* selectedHexagon;
Hexagon* usedHexagon;
float HEX_SIZE = 25;
bool playerTurn = true;
bool isPlacing = false;

bool inMenu = true;

std::array<Button*, 3> menuButtons = {
        new Button(300,70,"New Game"),
        new Button(300,70,"Score"),
        new Button(300,70,"Exit")
};

sf::Font font;

sf::Text title;

sf::Text playerRedScore;
sf::Text playerBlueScore;
sf::Text totalSore;
Button *returnButton = new Button(300,70,"Return");

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

sf::RenderWindow window(
        sf::VideoMode({width, height}),
        "Hexagon Game"
);

auto pollEvents() -> void;

auto drawAll() -> void;

auto drawGame() ->void;

auto drawMenu() -> void;

auto drawOutline(int posX, int posY) ->void;

auto findPosition(Hexagon *target) ->sf::Vector2f;

auto clearOtline()->void;

auto placeHexagon(Hexagon *hexagon)->void;

auto checkForNeighbors(Hexagon* hex) ->void;

auto checkForResults() -> void;

auto isPossibleToGo(Hexagon *hexagon) -> bool;

auto pollHexagons(sf::Event event)->void;

auto pollButtons(sf::Event event) ->void;

auto setUpText() -> void;

int main() {


    setUpText();

    while (window.isOpen()) {
        window.clear();

        if(!inMenu) checkForResults();

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

    playerRedScore.setFont(font);
    playerRedScore.setCharacterSize(50);
    playerRedScore.setFillColor(sf::Color::White);
    playerRedScore.setString("Red hexagons: 0");

    playerBlueScore.setFont(font);
    playerBlueScore.setCharacterSize(50);
    playerBlueScore.setFillColor(sf::Color::White);
    playerBlueScore.setString("Blue hexagons: 0");

    totalSore.setFont(font);
    totalSore.setCharacterSize(50);
    totalSore.setFillColor(sf::Color::White);
    totalSore.setString("Total hexagons: 58");

}

auto drawAll() -> void {
    if (inMenu) drawMenu();
    else drawGame();

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

auto drawGame() -> void {
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
            hx->setPosition(width/4.f + x, height/4.f +  y);
            //window.draw(hx);
            hx->draw(window);
            x+=50;
        }
        y+=40;
    }

    playerRedScore.setPosition(width/4.f + 600, height/4.f - 200);
    playerBlueScore.setPosition(width/4.f + 600, height/4.f - 100);

    window.draw(playerBlueScore);
    window.draw(playerRedScore);

    returnButton->setPosition(playerBlueScore.getPosition().x, height - returnButton->getHeight());
    returnButton->draw(window);

    if(selectedHexagon != nullptr){
        auto vec = findPosition(selectedHexagon);
        if(playerTurn == b[vec.y][vec.x]->getPlayer() && b[vec.y][vec.x]->isCaptured()) drawOutline(vec.x, vec.y);
//        else if (playerTurn == b[vec.y][vec.x]->getPlayer()&& b[vec.y][vec.x]->isCaptured() ) drawOutline(vec.x, vec.y);
        usedHexagon = selectedHexagon;
        //selectedHexagon = nullptr;
    }
}

auto findPosition(Hexagon *target) -> sf::Vector2f {
    for(int i = 0; i < b.size(); i++){
        auto hexTab = b[i];
        for(int j = 0; j < hexTab.size(); j++){
            if(b[i][j] == nullptr) continue;
            if(b[i][j]->getPosition().x == target->getPosition().x &&
            b[i][j]->getPosition().y == target->getPosition().y){
                sf::Vector2f vec;
                vec.x = j;
                vec.y = i;
                return vec;
            }
        }
    }
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

            Hexagon *nearHexagon = b[neighborY][neighborX];

            if (neighborY >= 0 && neighborY < b.size() && neighborX >= 0 && neighborX < b[neighborY].size() &&
                    nearHexagon != nullptr &&
                !nearHexagon->isCaptured()) {
                nearHexagon->hexagon.setOutlineColor(sf::Color::Green);
                nearHexagon->select(true);
            }

            for (auto & neighborFar : neighbors) {
                int farNeighborX = neighborX + neighborFar[0];
                int farNeighborY = neighborY + neighborFar[1];

                //std::cout<< farNeighborY << " " << farNeighborX << '\n';

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
            }
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
            }

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
    for(auto hexTab : b) {
        for (auto hx: hexTab) {
            if (hx == nullptr) continue;
            else {
                hx->setSecondRow(false); // maybe place it into clearOutlinefunc
                hx->select(false);
            }
        }
    }
    selectedHexagon = nullptr;
    usedHexagon = nullptr;
    isPlacing =false;
}

void checkForNeighbors(Hexagon* hex) {
    sf::Vector2f vec = findPosition(hex);
    int posY = vec.y, posX= vec.x;

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

auto isPossibleToGo(Hexagon *hexagon) -> bool{
    sf::Vector2f position = findPosition(hexagon);
    int posY = position.y;
    int posX = position.x;
    if(posY < 4) {
        std::array<int, 6> neighbors[] = {
                {-1, 0}, {-1, 1}, {0, 1},
                {1, 0}, {1, -1}, {0, -1}
        };

        for (auto & neighbor : neighbors) {
            int neighborX = posX + neighbor[0];
            int neighborY = posY + neighbor[1];

            Hexagon *nearHexagon = b[neighborY][neighborX];

            if ((neighborY >= 0 && neighborY < b.size() && neighborX >= 0 && neighborX < b[neighborY].size() &&
                nearHexagon != nullptr)) {
                if(!nearHexagon->isCaptured())
                    return true;
            }

            for (auto & neighborFar : neighbors) {
                int farNeighborX = neighborX + neighborFar[0];
                int farNeighborY = neighborY + neighborFar[1];

                //std::cout<< farNeighborY << " " << farNeighborX << '\n';

                Hexagon *farHexagon = b[farNeighborY][farNeighborX];

                if (farNeighborY >= 0 && farNeighborY < b.size() && farNeighborX >= 0 && farNeighborX < b[farNeighborY].size() && b[farNeighborY][farNeighborX] != nullptr) {
                    if (!farHexagon->isCaptured()) {
                        return true;
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

            if ((neighborY >= 0 && neighborY < b.size() && neighborX >= 0 && neighborX < b[neighborY].size() &&
                 nearHexagon != nullptr)) {
                if(!nearHexagon->isCaptured())
                    return true;
            }

            for (auto & neighborFar : neighbors) {
                int farNeighborX = neighborX + neighborFar[0];
                int farNeighborY = neighborY + neighborFar[1];

                //std::cout<< farNeighborY << " " << farNeighborX << '\n';

                Hexagon *farHexagon = b[farNeighborY][farNeighborX];

                if (farNeighborY >= 0 && farNeighborY < b.size() && farNeighborX >= 0 && farNeighborX < b[farNeighborY].size() && b[farNeighborY][farNeighborX] != nullptr) {
                    if (!farHexagon->isCaptured()) {
                        return true;
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

            if ((neighborY >= 0 && neighborY < b.size() && neighborX >= 0 && neighborX < b[neighborY].size() &&
                 nearHexagon != nullptr)) {
                if(!nearHexagon->isCaptured())
                    return true;
            }

            for (auto & neighborFar : neighbors) {
                int farNeighborX = neighborX + neighborFar[0];
                int farNeighborY = neighborY + neighborFar[1];

                //std::cout<< farNeighborY << " " << farNeighborX << '\n';

                Hexagon *farHexagon = b[farNeighborY][farNeighborX];

                if (farNeighborY >= 0 && farNeighborY < b.size() && farNeighborX >= 0 && farNeighborX < b[farNeighborY].size() && b[farNeighborY][farNeighborX] != nullptr) {
                    if (!farHexagon->isCaptured()) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

auto checkForResults() -> void {
    int redHex = 0, blueHex = 0, totalHex = 58;
    for(auto hexTab : b){
        for(auto hx : hexTab){
            if(hx == nullptr) continue;
            if(hx->getPlayer() && hx->isCaptured()) //false - blue, true - red
                redHex++;
            else if(!hx->getPlayer() && hx->isCaptured())
                blueHex++;
        }
    }
    auto semiPos = playerBlueScore.getString().find(":");
    playerBlueScore.setString(playerBlueScore.getString().substring(0,semiPos + 1) + " " +  std::to_string(blueHex));
    semiPos = playerRedScore.getString().find(":");
    playerRedScore.setString(playerRedScore.getString().substring(0,semiPos + 1) + " " +  std::to_string(redHex));

    std::cout<<"Total: " << totalHex << " redHex: " << redHex << " blueHex: " << blueHex << '\n';
    bool isPossibleToMove = false;
    for(auto hexTab : b){ //false - blue, true - red //not working
        for(auto hx : hexTab) {
            if (hx == nullptr) continue;
            if (hx->getPlayer() && hx->isCaptured()) {
                if (isPossibleToGo(hx))
                    isPossibleToMove = true;
                else
                    isPossibleToMove = false;
            }
        }
    }
    if(!isPossibleToMove) std::cout<<"Red cannot move\n";
    for(auto hexTab : b){ //false - blue, true - red !!!!working
        for(auto hx : hexTab){
            if(hx == nullptr) continue;
            if(!hx->getPlayer() && hx->isCaptured()){
                if(isPossibleToGo(hx))
                    isPossibleToMove = true;
                else
                    isPossibleToMove = false;
            }
        }
    }
    if(!isPossibleToMove) std::cout<<"Blue cannot move\n"; // working
    if(redHex == 0 || blueHex == 0){
       std::cout<<"Someone is fully eaten\n";
    } // someone is not able to move;
    if(redHex + blueHex == totalHex){
        std::cout<<"All board is captured;";
    }
    std::cout<<"Total: " << totalHex << " redHex: " << redHex << " blueHex: " << blueHex << '\n';
}


auto pollHexagons(sf::Event event)->void{
    for(const auto hexTab : b) {
        for (const auto hx: hexTab) {
            if (hx == nullptr) continue;
            if (hx->checkForClick(event)) {
                clearOtline();
                if (!isPlacing) selectedHexagon = hx;
                else placeHexagon(hx);
            }
        }
    }
    if(returnButton->checkForClick(event)) inMenu = !inMenu;
}

auto pollButtons(sf::Event event) ->void{
    for(auto button : menuButtons){
        if(button->checkForClick(event)){
            std::string input = button->getText();
            if(input == "New Game") inMenu = !inMenu;
            else if(input == "Score") continue; // implement score!
            else window.close();
        }
    }
}

auto pollEvents() -> void{
    sf::Event event;
    while (window.pollEvent(event)){
        if(event.type == sf::Event::Closed) window.close();
        if (event.type == sf::Event::MouseButtonPressed) {
            if(inMenu) pollButtons(event);
            else pollHexagons(event);
        }
    }
}
