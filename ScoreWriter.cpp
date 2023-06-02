//
// Created by Vladyslav Kalinchenko on 24.05.2023.
//

#include "ScoreWriter.h"
#include <iostream>
#include <array>
#include <set>
#include <string>

ScoreWriter::ScoreWriter(int redHex, int blueHex, int winner){
    this->redHex = redHex;
    this->blueHex = blueHex;
    this->winner = winner;
}

void ScoreWriter::read() {
    file.open(
            "/Users/vladyslavkalinchenko/CLionProjects/PJC_PRO1/Score.txt",
            std::ios::out | std::ios::in
    );
    std::string tmp;
    std::set<std::array<int, 3>> tmpSet;
    while(getline(file, tmp)) {
        std::string target = "Blue hexagons: ";
        auto blueIndex = tmp.find(target);
        auto commaIndex = tmp.find(',', blueIndex);
        std::string blueHexagons = tmp.substr(blueIndex + target.length(), commaIndex - (blueIndex + target.length()));
        int blueTmp = std::stoi(blueHexagons);
        //std::cout << blueTmp << '\n';

        target = "Red hexagons: ";
        auto redIndex = tmp.find(target);
        commaIndex = tmp.find(',', redIndex);
        std::string redHexagons = tmp.substr(redIndex + target.length(), commaIndex - (redIndex + target.length()));
        int redTmp = std::stoi(redHexagons);
        //std::cout << redTmp << " red " << '\n';

        auto winnerIndex = tmp.find("Winner: ");
        std::string winner = tmp.substr(winnerIndex + 8);
        int winnerNum;
        if (winner == "Blue") winnerNum = 0;
        else if (winner == "Red")winnerNum = 1;
        else winnerNum = 3;
        std::array<int, 3> tmpArr = {blueTmp, redTmp, winnerNum};
        tmpSet.insert(tmpArr);
    }
    tmpSet.insert(std::array<int, 3>{redHex, blueHex, winner});
    int count = 0;

    for (auto it = tmpSet.rbegin(); it != tmpSet.rend() && count < 5; ++it) {
        score.insert(*it);
        ++count;
    }

//    for(auto sc : score){
//        for(auto tmp : sc) std::cout<< tmp << " ";
//    }

    file.close();
}

void ScoreWriter::write() {
    file.open(
            "/Users/vladyslavkalinchenko/CLionProjects/PJC_PRO1/Score.txt",
            std::ios::out | std::ios::in |std::ios::trunc
    );
    for(auto scoreTab : score){
        std::string winnerStr;
        if(scoreTab[2] == 0) winnerStr ="Blue";
        else if (scoreTab[2] == 1 ) winnerStr = "Red";
        else winnerStr = "None";
        file << "Blue hexagons: " << scoreTab[1] << ", Red hexagons: " << scoreTab[0] << ", Winner: " << winnerStr << '\n';
    }
    file.close();
}

ScoreWriter::ScoreWriter() {

}

std::vector<std::string> ScoreWriter::getScoreList() {
    std::vector<std::string> scoreList;
    std::string tmp;
    file.open(
            "/Users/vladyslavkalinchenko/CLionProjects/PJC_PRO1/Score.txt",
            std::ios::out | std::ios::in
    );
    while (getline(file, tmp))
        scoreList.push_back(tmp);
    return scoreList;
}

ScoreWriter::~ScoreWriter() {

}


