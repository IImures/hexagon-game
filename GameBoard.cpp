//
// Created by Vladyslav Kalinchenko on 25.05.2023.
//

#include "GameBoard.h"
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include "ScoreWriter.h"

const int width = 1920;
const int height = 1080;

GameBoard::GameBoard(int width, int height, sf::RenderWindow *window, bool &inMenu) : inMenu(inMenu) {
    this->width=width;
    this->height=height;
    this->window = window;

    if(!font.loadFromFile("/Users/vladyslavkalinchenko/CLionProjects/PJC_PRO1/Assets/arial.ttf")){
        std::cout<<"Failed to load title font\n";
    }
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

auto GameBoard::setPcPlay(bool isPlay) ->void{
    pcPlay = isPlay;
}


auto GameBoard::drawGame() -> void {
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
            hx->draw(*window);
            x+=50;
        }
        y+=40;
    }

    playerRedScore.setPosition(width/4.f + 600, height/4.f - 200);
    playerBlueScore.setPosition(width/4.f + 600, height/4.f - 100);

    window->draw(playerBlueScore);
    window->draw(playerRedScore);

    returnButton->setPosition(playerBlueScore.getPosition().x, height - returnButton->getHeight());
    returnButton->draw(*window);

    if(selectedHexagon != nullptr){
        auto vec = findPosition(selectedHexagon);
        if(playerTurn == b[vec.y][vec.x]->getPlayer() && b[vec.y][vec.x]->isCaptured()) drawOutline(vec.x, vec.y);
//        else if (playerTurn == b[vec.y][vec.x]->getPlayer()&& b[vec.y][vec.x]->isCaptured() ) drawOutline(vec.x, vec.y);
        usedHexagon = selectedHexagon;
        //selectedHexagon = nullptr;
    }
//    else if(selectedHexagon != nullptr && pcPlay){
//        auto vec = findPosition(selectedHexagon);
//    }
}

auto GameBoard::findPosition(Hexagon *target) -> sf::Vector2f {
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
    std::cout<<"wha\n";
}

auto GameBoard::drawOutline(int posX, int posY)->void {
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

//                for(auto & nn : neighbors){
//                    int nnX = farNeighborX + nn[0];
//                    int nnY = farNeighborY + nn[1];
//
//                    Hexagon* faaa = b[nnY][nnX];
//
//                    if (nnY >= 0 && nnY < b.size() && nnX >= 0 && nnX < b[farNeighborY].size() && b[nnY][nnX] != nullptr) {
//                        if (faaa->hexagon.getOutlineColor() == sf::Color::Black &&
//                            !faaa->isCaptured()) {
//                            faaa->hexagon.setOutlineColor(sf::Color::Yellow);
//                            faaa->setSecondRow(true);
//                        }
//                    }
//                }
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

auto GameBoard::clearOtline()->void{
    for(auto hexTab : b){
        for(auto hx : hexTab) {
            if(hx == nullptr) continue;
            hx->hexagon.setOutlineColor(sf::Color::Black);
        }
    }
}

auto GameBoard::placeHexagon(Hexagon *hex)->void{
    if(hex->isSelected()){
        hex->capture(playerTurn);
        playerTurn = !playerTurn;
        checkForNeighbors(hex);
        if(pcPlay){
            pcGo();
        }
    }else if(hex->isSecondRow()){
        usedHexagon->unCapture();
        hex->capture(playerTurn);
        playerTurn = !playerTurn;
        checkForNeighbors(hex);
        if(pcPlay){
            pcGo();
        }
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

void GameBoard::checkForNeighbors(Hexagon* hex) {
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
                nearHexagon->isCaptured()) {
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
                nearHexagon->isCaptured())
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
                nearHexagon->isCaptured()) {
                nearHexagon->capture(usedHexagon->getPlayer());
            }
        }
    }
}

auto GameBoard::isPossibleToGo(Hexagon *hexagon) -> bool{
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

auto GameBoard::checkForResults() -> void {
    redHex = 0;
    blueHex = 0;
    totalHex = 58;
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

    //std::cout<<"Total: " << totalHex << " redHex: " << redHex << " blueHex: " << blueHex << '\n';
    bool isPossibleToMove = false;
    for(auto hexTab : b){ //false - blue, true - red //not working
        for(auto hx : hexTab) {
            if (hx == nullptr) continue;
            if (hx->getPlayer() && hx->isCaptured()) {
                if (isPossibleToGo(hx)){
                    isPossibleToMove = true;
                    break;
                }
                else
                    isPossibleToMove = false;
            }
        }
    }
    if(!isPossibleToMove){
        winner = false;
        std::cout<<"Red cannot move\n";
        endGame();
    }
    for(auto hexTab : b){ //false - blue, true - red !!!!working
        for(auto hx : hexTab){
            if(hx == nullptr) continue;
            if(!hx->getPlayer() && hx->isCaptured()){
                if(isPossibleToGo(hx)) {
                    isPossibleToMove = true;
                    break;
                }
                else
                    isPossibleToMove = false;
            }
        }
    }
    if(!isPossibleToMove){
        std::cout<<"Blue cannot move\n";
        winner = true;
        endGame();
    } // working
    if(redHex == 0 || blueHex == 0){
        std::cout<<"Someone is fully eaten\n";
        endGame();
    } // someone is not able to move;
    if(redHex + blueHex == totalHex){
        std::cout<<"All board is captured;";
        endGame();
    }
    //std::cout<<"Total: " << totalHex << " redHex: " << redHex << " blueHex: " << blueHex << '\n';
}


auto GameBoard::pollHexagons(sf::Event event)->void{
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
    if(returnButton->checkForClick(event)) endGame();
}

auto GameBoard::endGame() -> void{
    ScoreWriter writer = ScoreWriter(redHex, blueHex, winner);
    writer.read();
    writer.write();
    for(auto& hexTab : b){
        for(auto& hx : hexTab){
            if(hx == nullptr) continue;
            if(hx->getIsPredefined())
                hx = new Hexagon(HEX_SIZE, hx->getPredefinedPlayer());
            else if(!hx->getIsVisible())
                hx = new Hexagon(HEX_SIZE, false);
            else hx = new Hexagon(HEX_SIZE);
        }
    }
    selectedHexagon = nullptr;
    usedHexagon = nullptr;
    playerTurn = true;
    pcPlay = false;
    isPlacing = false;
    inMenu = true;
//    inScoreMenu = false;
}

auto GameBoard::pcGo() ->void{
    std::vector<Hexagon*> hexagonVec;
    for(auto hexTab : b){
        for(auto hx : hexTab){
            if(hx == nullptr) continue;
            else if(hx->isCaptured() && !hx->getPlayer()){
                hexagonVec.push_back(hx);
            }
        }
    }
    std::vector<std::map<std::array<int,2>, std::array<int,3>>> maxEnemy;
    for(auto hexagon : hexagonVec){
        maxEnemy.push_back(calculateMoveNear(hexagon));
        maxEnemy.push_back(calculateMoveFar(hexagon));
    }

    sf::Vector2f origin = chooseRandomMove(maxEnemy);

    usedHexagon->hexagon.setOutlineColor(sf::Color::Red);
    if(usedHexagon->isSelected()) {
        usedHexagon->capture(playerTurn);
        checkForNeighbors(usedHexagon);
    }else if(usedHexagon->isSecondRow()){
        b[origin.y][origin.x]->unCapture();
        usedHexagon->capture(playerTurn);
        checkForNeighbors(usedHexagon);
    }


    for(auto hexTab : b) {
        for (auto hx: hexTab) {
            if (hx == nullptr) continue;
            else {
                hx->setSecondRow(false); // maybe place it into clearOutlinefunc
                hx->select(false);
            }
        }
    }
    playerTurn = !playerTurn;
}

auto GameBoard::chooseRandomMove(std::vector<std::map<std::array<int,2>, std::array<int,3>>> maxEnemy)->sf::Vector2f{
    std::map<std::array<int, 2>, std::array<int,3>>& randomMap = maxEnemy[rand() % maxEnemy.size()];
    while (randomMap.size() == 0)
        randomMap = maxEnemy[rand() % maxEnemy.size()];
    auto item = randomMap.begin();
    std::advance( item, rand() % randomMap.size());

    sf::Vector2f target = sf::Vector2f(item->first[0], item->first[1]);
    int maxEnemies = item->second[2];

    int originX = item->second[0];
    int originY = item->second[1];

    for (const auto& map : maxEnemy) {
        for(auto entry : map){
            sf::Vector2f key = sf::Vector2f(entry.first[0], entry.first[1]);
            int secondElement = entry.second[2];
            if (secondElement > maxEnemies) {
                maxEnemies = secondElement;
                target = key;
                originX = entry.second[0];
                originY = entry.second[1];
            }
        }
    }
    usedHexagon = b[target.y][target.x];
    return sf::Vector2f(originX, originY);
}

auto GameBoard::calculateMoveFar(Hexagon *hexagon) -> std::map<std::array<int,2>, std::array<int,3>> {
    sf::Vector2f position = findPosition(hexagon);
    int posY = position.y;
    int posX = position.x;
    int farEnemy = 0;
    std::map<std::array<int,2>, std::array<int,3>> positions;
    if(posY < 4) {
        std::array<int, 6> neighbors[] = {
                {-1, 0}, {-1, 1}, {0, 1},
                {1, 0}, {1, -1}, {0, -1}
        };

        for (auto & neighbor : neighbors) {
            int neighborX = posX + neighbor[0];
            int neighborY = posY + neighbor[1];

            for (auto & neighborFar : neighbors) {
                int farNeighborX = neighborX + neighborFar[0];
                int farNeighborY = neighborY + neighborFar[1];

                Hexagon *farHexagon = b[farNeighborY][farNeighborX];

                if (farNeighborY >= 0 && farNeighborY < b.size() && farNeighborX >= 0 && farNeighborX < b[farNeighborY].size() && b[farNeighborY][farNeighborX] != nullptr) {
                    if (!farHexagon->isCaptured()) {
                        farHexagon->setSecondRow(true);
                    }
                }

                for(auto & farTarget : neighbors){
                    int farEnemyX = farNeighborX + farTarget[0];
                    int farEnemyY = farNeighborY + farTarget[1];

                    Hexagon* farHex = b[farEnemyY][farEnemyX];

                    if (farEnemyY >= 0 && farEnemyY < b.size() && farEnemyX >= 0 && farEnemyX < b[farEnemyY].size() && b[farEnemyY][farEnemyX] != nullptr) {
                        if (farHex->isCaptured() && farEnemy++) {
                            farEnemy++;
                        }
                    }
                }
                std::array<int, 2> key ={farNeighborX, farNeighborY};
                std::array<int, 3> val = {posX, posY, farEnemy};
                positions[key] = val;
                farEnemy = 0;
            }
        }
        return positions;
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

            for (auto & neighborFar : neighbors) {
                int farNeighborX = neighborX + neighborFar[0];
                int farNeighborY = neighborY + neighborFar[1];

                Hexagon *farHexagon = b[farNeighborY][farNeighborX];

                if (farNeighborY >= 0 && farNeighborY < b.size() && farNeighborX >= 0 && farNeighborX < b[farNeighborY].size() && b[farNeighborY][farNeighborX] != nullptr) {
                    if (!farHexagon->isCaptured()) {
                        farHexagon->setSecondRow(true);
                    }
                }

                for(auto & farTarget : neighbors){
                    int farEnemyX = farNeighborX + farTarget[0];
                    int farEnemyY = farNeighborY + farTarget[1];

                    Hexagon* farHex = b[farEnemyY][farEnemyX];

                    if (farEnemyY >= 0 && farEnemyY < b.size() && farEnemyX >= 0 && farEnemyX < b[farEnemyY].size() && b[farEnemyY][farEnemyX] != nullptr) {
                        if (farHex->isCaptured() && farEnemy++) {
                            farEnemy++;
                        }
                    }
                }
                std::array<int, 2> key ={farNeighborX, farNeighborY};
                std::array<int, 3> val = {posX, posY, farEnemy};
                positions[key] = val;
                farEnemy = 0;
            }
        }
        return positions;
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


            for (auto & neighborFar : neighbors) {
                int farNeighborX = neighborX + neighborFar[0];
                int farNeighborY = neighborY + neighborFar[1];


                Hexagon *farHexagon = b[farNeighborY][farNeighborX];

                if (farNeighborY >= 0 && farNeighborY < b.size() && farNeighborX >= 0 && farNeighborX < b[farNeighborY].size() && b[farNeighborY][farNeighborX] != nullptr) {
                    if (!farHexagon->isCaptured()) {
                        farHexagon->setSecondRow(true);
                    }
                }

                for(auto & farTarget : neighbors){
                    int farEnemyX = farNeighborX + farTarget[0];
                    int farEnemyY = farNeighborY + farTarget[1];

                    Hexagon* farHex = b[farEnemyY][farEnemyX];

                    if (farEnemyY >= 0 && farEnemyY < b.size() && farEnemyX >= 0 && farEnemyX < b[farEnemyY].size() && b[farEnemyY][farEnemyX] != nullptr) {
                        if (farHex->isCaptured() && farEnemy++) {
                            farEnemy++;
                        }
                    }
                }
                std::array<int, 2> key ={farNeighborX, farNeighborY};
                std::array<int, 3> val = {posX, posY, farEnemy};
                positions[key] = val;
                farEnemy = 0;
            }
        }
        return positions;
    }
}

auto GameBoard::calculateMoveNear(Hexagon* hexagon)->std::map<std::array<int,2>, std::array<int,3>> {
    sf::Vector2f position = findPosition(hexagon);
    int posY = position.y;
    int posX = position.x;
    int nearEnemy = 0;
    std::map<std::array<int,2>, std::array<int,3>> positions;
    if(posY < 4) {
        std::array<int, 6> neighbors[] = {
                {-1, 0},
                {-1, 1},
                {0, 1},
                {1, 0},
                {1, -1},
                {0, -1}
        };

        for (auto & neighbor : neighbors) {
            int neighborX = posX + neighbor[0];
            int neighborY = posY + neighbor[1];

            Hexagon *nearHexagon = b[neighborY][neighborX];

            if (neighborY >= 0 && neighborY < b.size() && neighborX >= 0 && neighborX < b[neighborY].size() &&
                nearHexagon != nullptr &&
                !nearHexagon->isCaptured()) {

                nearHexagon->select(true);

                for (auto & neighborFar : neighbors) {
                    int farNeighborX = neighborX + neighborFar[0];
                    int farNeighborY = neighborY + neighborFar[1];

                    Hexagon *farHexagon = b[farNeighborY][farNeighborX];

                    if (farNeighborY >= 0 && farNeighborY < b.size() && farNeighborX >= 0 && farNeighborX < b[farNeighborY].size() && b[farNeighborY][farNeighborX] != nullptr) {
                        if (farHexagon->isCaptured() && farHexagon->getPlayer()) {
                            nearEnemy++;
                        }
                    }
                }
                std::array<int, 2> key ={neighborX, neighborY};
                std::array<int, 3> val ={posY, posX, nearEnemy};
                positions[key] = val;
                nearEnemy = 0;
            }
        }
        return positions;
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

                hexagon->select(true);

                for (auto & neighborFar : neighbors) {
                    int farNeighborX = neighborX + neighborFar[0];
                    int farNeighborY = neighborY + neighborFar[1];

                    Hexagon *farHexagon = b[farNeighborY][farNeighborX];

                    if (farNeighborY >= 0 && farNeighborY < b.size() && farNeighborX >= 0 && farNeighborX < b[farNeighborY].size() && b[farNeighborY][farNeighborX] != nullptr) {
                        if (farHexagon->isCaptured() && farHexagon->getPlayer()) {
                            nearEnemy++;
                        }
                    }
                }
                std::array<int, 2> key ={neighborX, neighborY};
                std::array<int, 3> val ={posY, posX, nearEnemy};
                positions[key] = val;
                nearEnemy = 0;
            }
        }
        return positions;
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

                hexagon->select(true);

                for (auto & neighborFar : neighbors) {
                    int farNeighborX = neighborX + neighborFar[0];
                    int farNeighborY = neighborY + neighborFar[1];

                    Hexagon *farHexagon = b[farNeighborY][farNeighborX];

                    if (farNeighborY >= 0 && farNeighborY < b.size() && farNeighborX >= 0 && farNeighborX < b[farNeighborY].size() && b[farNeighborY][farNeighborX] != nullptr) {
                        if (farHexagon->isCaptured() && farHexagon->getPlayer()) {
                            nearEnemy++;
                        }
                    }
                }
                std::array<int, 2> key ={neighborX, neighborY};
                std::array<int, 3> val ={posY, posX, nearEnemy};
                positions[key] = val;
                nearEnemy = 0;
            }
        }
        return positions;
    }
}


//void GameBoard::setPc(Computer computer) {
//    pc = computer;
//}


