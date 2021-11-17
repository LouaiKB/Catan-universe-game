#ifndef CATANELEMENTS_H
#define CATAELEMENTS_H
#include <iostream>
#include <array>


class Tuile
{
public:
    Tuile();
    ~Tuile();
    int getNumberOfTuile();
    int getRessourceOfTuile();
    std::array<std::array<int, 3>, 6> getNodesCoordinates();
    void setNumberOfTuile(int);
    void setRessourceOfTuile(int);
    void setNodesCoordinates(int, int, bool occupied=true);
    

private:
    int numberOfTuile;
    int ressource;
    std::array<std::array<int, 3>, 6> nodes;
    int edges[6];
};

#endif