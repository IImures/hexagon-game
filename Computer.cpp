//
// Created by Vladyslav Kalinchenko on 25.05.2023.
//

#include "Computer.h"
#include "Hexagon.h"
#include "GameBoard.h"

#include<iostream>

//auto GameBoard::getBoard() {
//    return b;
//}
//
//Computer::Computer(GameBoard *board){
//    this->board = board;
//}
//
//void Computer::go() {
//    std::vector<Hexagon*> vec;
//    auto b = board->getBoard();
//    for(auto hexTab : b ){
//        for(auto hx : hexTab){
//            if(hx == nullptr) continue;
//            else if(hx->isCaptured() && !hx->getPlayer()){
//                vec.push_back(hx);
//                std::cout<<"PC hex\n";
//            }
//        }
//    }
//    std::vector<sf::Vector2f> coordinates;
//    for(auto hexagon : vec){
//        coordinates.push_back(board->findPosition(hexagon));
//    }
//
//}
//
//Computer::~Computer() {
//
//}
