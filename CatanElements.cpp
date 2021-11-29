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

std::vector<Node>* Tuile::getNodesCoordinates() 
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
    this->nodes->at(0) = Node(x - 60, y + 28);
    this->nodes->at(1) = Node(x - 20, y - 40);
    this->nodes->at(2) = Node(x + 65, y - 40);
    this->nodes->at(3) = Node(x + 105, y + 28);
    this->nodes->at(4) = Node(x + 65, y + 93);
    this->nodes->at(5) = Node(x - 20, y + 93);
}

std::vector<int> Tuile::getTilesOfANode(Node node, std::vector<Tuile>* allTiles)
{
    std::vector<int> numberOfCorrespondedTiles;
    
    // parsing all the Tiles
    for (int i = 0; i < allTiles->size(); i++) {
        // know we will parse each node of the tile 
        std::vector<Node>* nodes = allTiles->at(i).getNodesCoordinates();
        if (Node::checkIfNodeIsOccupied(node, nodes)) {
            numberOfCorrespondedTiles.push_back(allTiles->at(i).getNumberOfTuile());
        }
    }
    return numberOfCorrespondedTiles;
}

std::vector<int> Tuile::getRessourceOfSpecificTiles(Node node, std::vector<Tuile>* allTiles)
{
    std::vector<int> ressourcesOfCorrespondedTiles;
    for (int i = 0; i < allTiles->size(); i++) {
        std::vector<Node>* nodes = allTiles->at(i).getNodesCoordinates();
        if (Node::checkIfNodeIsOccupied(node, nodes)) {
            ressourcesOfCorrespondedTiles.push_back(allTiles->at(i).getRessourceOfTuile());
        }
    }
    return ressourcesOfCorrespondedTiles;
}

Node::Node() : x(0), y(0) {
    this->occupied = false;
}

Node::~Node() {
}

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
    if (Node::checkIfNodeIsOccupied(Node(x - 90, y), Node::allNodes)) {
        adjacentNodes.push_back(Node(x - 90, y));
        adjacentNodes.push_back(Node(x + 50, y - 70));
        adjacentNodes.push_back(Node(x + 50, y + 70));
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

std::vector<Node> *Node::occupiedNodes = new std::vector<Node>();
std::vector<Node> *Node::allNodes = new std::vector<Node>();

Node * Node::clickedNode = new Node[1];
bool Node::isClicked = false;
bool Node::playerOn = true;

void Node::setAllNodes(Node node)
{
    Node::allNodes->push_back(node);
}

void Node::setClickedNode(Node node)
{
    delete[] Node::clickedNode;
    Node::clickedNode = new Node[1];
    Node::clickedNode[0] = node;
}

void Node::setOccupiedNodes(Node node) 
{
    Node::occupiedNodes->push_back(node);
}

bool Node::checkIfNodeIsOccupied(Node node, std::vector<Node> *allNodes)
{
    bool foundx = false;
    for (int i = 0; i < allNodes->size(); i++)
    {
        if ((node.getX() == allNodes->at(i).getX() || 
            (node.getX() <= allNodes->at(i).getX() + 10 &&
            node.getX() >= allNodes->at(i).getX() - 10)) && 
            (node.getY() == allNodes->at(i).getY() || 
            (node.getY() <= allNodes->at(i).getY() + 10 &&
            node.getY() >= allNodes->at(i).getY() - 10))) {
                foundx = true;
                break;
        }
    }
    return foundx;
}

Node Node::getSpecificNode(Node node)
{
    for (int i = 0; i < Node::allNodes->size(); i++) {
        if ((node.getX() == Node::allNodes->at(i).getX() || 
            (node.getX() <= Node::allNodes->at(i).getX() + 20 &&
            node.getX() >= Node::allNodes->at(i).getX() - 20)) && 
            (node.getY() == Node::allNodes->at(i).getY() || 
            (node.getY() <= Node::allNodes->at(i).getY() + 20 &&
            node.getY() >= Node::allNodes->at(i).getY() - 20))) {
                return Node::allNodes->at(i);
        }
    }
    return Node();
}