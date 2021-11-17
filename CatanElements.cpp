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

std::array<std::array<int, 3>, 6> Tuile::getNodesCoordinates() 
{
    return this->nodes;
}

void Tuile::setNumberOfTuile(int num)
{
    this->numberOfTuile = num;
}

void Tuile::setRessourceOfTuile(int num)
{
    this->ressource = num;
}

void Tuile::setNodesCoordinates(int x, int y, bool occupied)
{
    this->nodes[0] = {x - 60, y + 28, occupied};
    this->nodes[1] = {x - 20, y - 40, occupied};
    this->nodes[2] = {x + 65, y - 40, occupied};
    this->nodes[3] = {x + 105, y + 28, occupied};
    this->nodes[4] = {x + 65, y + 93, occupied};
    this->nodes[5] = {x - 20, y + 93, occupied};
}