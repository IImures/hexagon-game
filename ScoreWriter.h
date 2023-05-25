//
// Created by Vladyslav Kalinchenko on 24.05.2023.
//

#ifndef PJC_PRO1_SCOREWRITER_H
#define PJC_PRO1_SCOREWRITER_H

#include <fstream>
#include <set>

class ScoreWriter {
public:
    ScoreWriter(int redHex, int blueHex, int winner);

    ScoreWriter();

    void read();

    std::vector<std::string> getScoreList();

    void write();
private:
    std::fstream file;
    std::set<std::array<int,3>> score;

    int redHex;
    int blueHex;
    int winner;
};


#endif //PJC_PRO1_SCOREWRITER_H
