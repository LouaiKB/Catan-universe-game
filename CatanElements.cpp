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

void Node::setOccupied() {
    this->occupied = true;
}

bool Node::isOccupied() {
    return this->occupied;
}

void Node::setAdjacentNodes() {
    
    // setting the side Node 
    if (Node::checkIfNodeIsOccupied(Node(x - 85, y))) {
        adjacentNodes.push_back(Node(x - 85, y));
        adjacentNodes.push_back(Node(x + 45, y - 70));
        adjacentNodes.push_back(Node(x + 45, y + 70));
    } else {
        adjacentNodes.push_back(Node(x + 85, y));
        adjacentNodes.push_back(Node(x - 40, y - 70));
        adjacentNodes.push_back(Node(x - 40, y + 70));
    }

    // set all AdjacentNodes occupied
    for (int i = 0; i < adjacentNodes.size(); i++) {
        adjacentNodes[i].setOccupied();
    }
}

int Node::getX() { return this->x; }
int Node::getY() { return this->y; }

std::vector<Node> Node::getAdjacentNodes() {
    return this->adjacentNodes;
}

std::vector<Node> Node::occupiedNodes;
std::vector<Node> Node::allNodes;
// std::vector<Node> Node::clickedNode;

Node * Node::clickedNode = new Node[1];
bool Node::isClicked = false;

void Node::setAllNodes(Node node)
{
    Node::allNodes.push_back(node);
}

void Node::setClickedNode(Node node)
{
    delete[] Node::clickedNode;
    Node::clickedNode = new Node[1];
    Node::clickedNode[0] = node;
}

void Node::setOccupiedNodes(Node node) 
{
    Node::occupiedNodes.push_back(node);
}

bool Node::checkIfNodeIsOccupied(Node node, bool isHouseNode)
{
    bool foundx = false;

    if (!isHouseNode) {
        for (int i = 0; i < Node::allNodes.size(); i++)
        {
            if ((node.getX() == Node::allNodes[i].getX() || 
                (node.getX() <= Node::allNodes[i].getX() + 10 &&
                node.getX() >= Node::allNodes[i].getX() - 10)) && 
                (node.getY() == Node::allNodes[i].getY() || 
                (node.getY() <= Node::allNodes[i].getY() + 10 &&
                node.getY() >= Node::allNodes[i].getY() - 10))) {
                    foundx = true;
                    break;
            }
        }
    }
    // else 
    // {
    //     for (int i = 0; i < Node::occupiedHouseNodes.size(); i++)
    //     {
    //         if ((arr[0] == Node::occupiedHouseNodes[i][0] || 
    //             (arr[0] <= Node::occupiedHouseNodes[i][0] + 10 &&
    //             arr[0] >= Node::occupiedHouseNodes[i][0] - 10)) && 
    //             (arr[1] == Node::occupiedHouseNodes[i][1] || 
    //             (arr[1] <= Node::occupiedHouseNodes[i][1] + 10 &&
    //             arr[1] >= Node::occupiedHouseNodes[i][1] - 10))) {
    //                 foundx = true;
    //                 break;
    //         }
    //     }
    // }
    
    return foundx;
}