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

std::array<Node, 6> Tuile::getNodesCoordinates() 
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

void Tuile::setNodesCoordinates(int x, int y)
{
    this->nodes[0] = Node(x - 60, y + 28);
    this->nodes[1] = Node(x - 20, y - 40);
    this->nodes[2] = Node(x + 65, y - 40);
    this->nodes[3] = Node(x + 105, y + 28);
    this->nodes[4] = Node(x + 65, y + 93);
    this->nodes[5] = Node(x - 20, y + 93);
}


Node::Node() : x(0), y(0) {
    this->occupied = false;
}

Node::~Node() {}

Node::Node(int a, int b) : x(a), y(b) {
}


int Node::getX() { return this->x; }
int Node::getY() { return this->y; }

std::vector<std::vector<int>> Node::occupiedNodes;

void Node::setOccupiedNodes(std::vector<int> arr)
{
    Node::occupiedNodes.push_back(arr);
}

bool Node::checkIfNodeIsOccupied(std::vector<int> arr)
{
    bool foundx = false;
    for (int i = 0; i < Node::occupiedNodes.size(); i++)
    {
        if ((arr[0] == Node::occupiedNodes[i][0] || 
            (arr[0] <= Node::occupiedNodes[i][0] + 10 &&
             arr[0] >= Node::occupiedNodes[i][0] - 10)) && 
            (arr[1] == Node::occupiedNodes[i][1] || 
            (arr[1] <= Node::occupiedNodes[i][1] + 10 &&
             arr[1] >= Node::occupiedNodes[i][1] - 10))) {
                foundx = true;
                break;
        }
    }
    return foundx;
}