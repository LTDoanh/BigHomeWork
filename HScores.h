#ifndef HIGHSCORES_H_INCLUDED
#define HIGHSCORES_H_INCLUDED

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include "Player.h"

class HScores
{
public:
    std::vector<Player> read_high_scores();
    void write_high_scores(string newname, int newscore, std::vector<Player> &highScores);
    bool is_high_score(int newscore, std::vector<Player> highScores);
    void print_player(std::vector<Player> highScores);
private:
    string FILENAME = "high_scores.txt";
    fstream file;
    int dem = 0;
};

#endif // HIGHSCORES_H_INCLUDED
