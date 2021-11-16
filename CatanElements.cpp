#include "CatanElements.h"

Tuile::Tuile() : numberOfTuile(0), ressource(0) {} 

Tuile::~Tuile() {}

int Tuile::getNumberOfTuile()
{
    return numberOfTuile;
}

int Tuile::getRessourceOfTuile()
{
    return ressource;
}

void Tuile::setNumberOfTuile(int num)
{
    this->numberOfTuile = num;
}

void Tuile::setRessourceOfTuile(int num)
{
    this->ressource = num;
}

void Tuile::setNodesCoordinates(int x, int y)
{
    this->nodes[0] = {x - 60, y};
    this->nodes[1] = {x - 20, y - 69};
    this->nodes[2] = {x + 20, y - 69};
    this->nodes[3] = {x + 60, y};
    this->nodes[4] = {x + 20, y + 69};
    this->nodes[5] = {x - 60, y +69};
}