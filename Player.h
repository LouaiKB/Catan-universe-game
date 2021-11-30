#ifndef PLAYER_H
#define PLAYER_H
#include "DrawingArea.h"

class Player
{
public:
    Player(int);
    ~Player();
    void setCorrespondedTiles(Node, std::vector<Tuile>*);
    void setRessources(Node, std::vector<Tuile>*, int = 0, bool = false);
    void setScore(int);
    bool buildRoute();
    bool buildSettlement();
    bool buildCity();
    int getScore();
    int getNumberOfPlayer();

private:
    // we have 5 types of ressources: 1- Brique, 2- Pierre
    // 3- Mouton, 4- Blé, 5-Bois.
    std::vector<int> ressources;
    std::vector<int> tiles;
    int number;
    int score;
};

#endif