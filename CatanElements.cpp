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

/**
 * @brief set nodes coordinates, we will retrieve the coordinates of a tile (x and y)
 * and set the coordinates of each node 
 * 
 * examples:
 * (first node coordinates = (x = x(of a tile) - 60) (y = (y(of a tile + 28)))
 * etc..
 * 
 * @param x coordinate of the tile object
 * @param y coordinate of the tile object
 */
void Tuile::setNodesCoordinates(int x, int y)
{
    this->nodes->at(0) = Node(x - 60, y + 28);
    this->nodes->at(1) = Node(x - 20, y - 40);
    this->nodes->at(2) = Node(x + 65, y - 40);
    this->nodes->at(3) = Node(x + 105, y + 28);
    this->nodes->at(4) = Node(x + 65, y + 93);
    this->nodes->at(5) = Node(x - 20, y + 93);
}

/**
 * @brief set edges coordinates, the edge coordinates represente the middle (radius)
 * of two corresponded nodes
 * example:
 * edge1 = is in the middle of node 1 and node 2
 * 
 */
void Tuile::setEdgesCoordinates()
{
    this->edges->at(0) = Tuile::getMiddleBetweenTwoNodes(nodes->at(0), nodes->at(1));
    this->edges->at(1) = Tuile::getMiddleBetweenTwoNodes(nodes->at(1), nodes->at(2));
    this->edges->at(2) = Tuile::getMiddleBetweenTwoNodes(nodes->at(2), nodes->at(3));
    this->edges->at(3) = Tuile::getMiddleBetweenTwoNodes(nodes->at(3), nodes->at(4));
    this->edges->at(4) = Tuile::getMiddleBetweenTwoNodes(nodes->at(4), nodes->at(5));
    this->edges->at(5) = Tuile::getMiddleBetweenTwoNodes(nodes->at(5), nodes->at(0));
}

/**
 * @brief static method that returns an edge object
 * 
 * @param a 
 * @param b 
 * @return Edge 
 */
Edge Tuile::getMiddleBetweenTwoNodes(Node a, Node b)
{
    // compute the edge coordonants (an edge is in the middle of two nodes)
    int middleX = (a.getX() + b.getX()) / 2;
    int middleY = (a.getY() + b.getY()) / 2;

    // get the radius to get the corresponded nodes after
    int xRadius = middleX - a.getX();
    int yRadius;
    
    if (middleY == a.getY()) 
        yRadius = a.getY();
    else
        yRadius = middleY - a.getY();
    
    return Edge(middleX, middleY, xRadius, yRadius);
}

std::vector<Edge>* Tuile::getEdgesCoordinates()
{
    return this->edges;
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

/**
 * @brief Set the Adjacent Nodes for a clicked node that have a settlment
 * to have the three adjacent nodes to disable building in these nodes 
 * 
 */

void Node::setAdjacentNodes() {
    
    // setting the side Node 
    if (Node::checkIfNodeExists(Node(x - 90, y), Node::allNodes)) {
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

// initialize static vectors
std::vector<Node> *Node::occupiedNodes = new std::vector<Node>();
std::vector<Node> *Node::allNodes = new std::vector<Node>();
std::vector<Node> *Node::allClickedNodes = new std::vector<Node>();

Node * Node::clickedNode = new Node[1];
bool Node::isClicked = false;
bool Node::playerOn = true;
bool Node::buildRoute = false;

void Node::setAllNodes(Node node)
{
    Node::allNodes->push_back(node);
}

// set dynamically the clicked node
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

bool Node::checkIfNodeExists(Node node, std::vector<Node> *allNodes)
{
    bool found = false;
    for (int i = 0; i < allNodes->size(); i++)
    {
        if ((node.getX() == allNodes->at(i).getX() || 
            (node.getX() <= allNodes->at(i).getX() + 10 &&
            node.getX() >= allNodes->at(i).getX() - 10)) && 
            (node.getY() == allNodes->at(i).getY() || 
            (node.getY() <= allNodes->at(i).getY() + 10 &&
            node.getY() >= allNodes->at(i).getY() - 10))) {
                found = true;
                break;
        }
    }
    return found;
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

std::vector<Node> Edge::getNodesOfAnEdge(Edge edge)
{
    std::vector<Node> nodesOfthisEdge;
    int radiusX = edge.getRadiusX();
    int radiusY = edge.getRadiusY();
    int y1, y2;
    int x1 = edge.getX() - radiusX;
    int x2 = edge.getX() + radiusX;
    if (radiusY == edge.getY()) {
        y1 = edge.getY();
        y2 = edge.getY();
    } else {
        y1 = edge.getY() - radiusY;
        y2 = edge.getY() + radiusY;
    }

    Node firstNode = Node::getSpecificNode(Node(x1, y1));
    Node secondNode = Node::getSpecificNode(Node(x2, y2));
    
    nodesOfthisEdge.push_back(firstNode);
    nodesOfthisEdge.push_back(secondNode);

    return nodesOfthisEdge;
}

Edge::Edge(int a, int b, int midx, int midy) : Node(a, b)
{
    this->radiusX = midx;
    this->radiusY = midy;
}

Edge::Edge() : Node() {
    this->radiusX = 0;
    this->radiusY = 0;
}
Edge::~Edge() {}

std::vector<Edge>* Edge::allEdges = new std::vector<Edge>();

void Edge::setAllEdges(Edge edge)
{
    Edge::allEdges->push_back(edge);
}

int Edge::getRadiusX() 
{
    return this->radiusX;
}

int Edge::getRadiusY()
{
    return this->radiusY;
}

bool Edge::checkIfNodeExists(Edge edge, std::vector<Edge>* allEdges)
{
    bool found = false;
    for (int i = 0; i < allEdges->size(); i++)
    {
        if ((edge.getX() == allEdges->at(i).getX() || 
            (edge.getX() <= allEdges->at(i).getX() + 10 &&
            edge.getX() >= allEdges->at(i).getX() - 10)) && 
            (edge.getY() == allEdges->at(i).getY() || 
            (edge.getY() <= allEdges->at(i).getY() + 10 &&
            edge.getY() >= allEdges->at(i).getY() - 10))) {
                found = true;
                break;
        }
    }
    return found;
}

Edge Edge::getSpecificEdge(Node node, std::vector<Edge> *allEdges)
{
    for (int i = 0; i < allEdges->size(); i++) {
        if ((node.getX() == allEdges->at(i).getX() || 
            (node.getX() <= allEdges->at(i).getX() + 20 &&
            node.getX() >= allEdges->at(i).getX() - 20)) && 
            (node.getY() == allEdges->at(i).getY() || 
            (node.getY() <= allEdges->at(i).getY() + 20 &&
            node.getY() >= allEdges->at(i).getY() - 20))) {
                return allEdges->at(i);
        }
    }
    return Edge();
}

Edge *Edge::clickedEdge = new Edge[1];

void Edge::setClickedNode(Edge edge)
{
    delete[] Edge::clickedEdge;
    Edge::clickedEdge = new Edge[1];
    Edge::clickedEdge[0] = edge;
}

bool Edge::isClicked = true;