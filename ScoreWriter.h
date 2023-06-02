//
// Created by Vladyslav Kalinchenko on 24.05.2023.
//

#ifndef PJC_PRO1_SCOREWRITER_H
#define PJC_PRO1_SCOREWRITER_H

#include <fstream>
#include <set>

class ScoreWriter {
public:
    /**
     * Constructor used when writing info to ScoreBoard
     * @param redHex
     * @param blueHex
     * @param winner
     */
    ScoreWriter(int redHex, int blueHex, int winner);

    /**
     * Constructor used to read from ScoreBoard
     */
    ScoreWriter();

    ~ScoreWriter();

    void read();

    /**
     * Returns score list in set
     * @return std::set<std::array<int,3>> score;
     */
    std::vector<std::string> getScoreList();

    void write();
private:
    std::fstream file;
    std::set<std::array<int,3>> score;

    int redHex{};
    int blueHex{};
    int winner{};
};


#endif //PJC_PRO1_SCOREWRITER_H
