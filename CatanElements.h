#ifndef CATANELEMENTS_H
#define CATAELEMENTS_H
#include <iostream>
#include <array>
#include <vector>
#include <random>
#include <algorithm>

class Node
{
public:
    Node();
    Node(int, int);
    ~Node();
    
    // All static methods
    static std::vector<Node> *allNodes;
    static std::vector<Node> *occupiedNodes;
    static Node *clickedNode;
    static bool isClicked;
    static bool playerOn;
    static bool buildRoute;
    static void setClickedNode(Node);
    static void setOccupiedNodes(Node);
    static void setAllNodes(Node);
    static bool checkIfNodeIsOccupied(Node, std::vector<Node>*);
    static Node getSpecificNode(Node);
    static std::vector<Node> getNodesOfAnEdge(Node);    

    // class methods
    void setOccupied();
    bool isOccupied();
    void setAdjacentNodes();
    std::vector<Node> getAdjacentNodes();
    int getX();
    int getY();

private:
    int x;
    int y;
    bool occupied;
    std::vector<Node> adjacentNodes;
};

class Tuile
{
public:
    Tuile();
    ~Tuile();
    int getNumberOfTuile();
    int getRessourceOfTuile();
    std::vector<Node>* getNodesCoordinates();
    std::vector<Node>* getEdgesCoordinates();
    void setNumberOfTuile(int);
    void setRessourceOfTuile(int);
    void setNodesCoordinates(int, int);
    void setEdgesCoordinates();
    static Node getMiddleBetweenTwoNodes(Node, Node);

private:
    int numberOfTuile;
    int ressource;
    std::vector<Node> *nodes = new std::vector<Node>(6);
    // int edges[6];
    std::vector<Node> *edges = new std::vector<Node>(6);
};


#endif