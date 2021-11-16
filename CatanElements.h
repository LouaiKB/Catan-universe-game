#ifndef CATANELEMENTS_H
#define CATAELEMENTS_H
#include <iostream>

class Tuile
{
public:
    Tuile();
    ~Tuile();
    int getNumberOfTuile();
    int getRessourceOfTuile();
    void setNumberOfTuile(int);
    void setRessourceOfTuile(int);
private:
    int numberOfTuile;
    int ressource;
    int nodes[6];
    int edges[6];
};

#endif