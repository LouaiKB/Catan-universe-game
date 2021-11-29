#ifndef CATANELEMENTS_H
#define CATAELEMENTS_H
#include <iostream>
#include <array>
#include <vector>


class Node
{
public:
    Node();
    Node(int, int);
    ~Node();
    
    // All static methods
    static std::vector<Node> *allNodes;
    static std::vector<Node> *occupiedNodes;
    // static std::vector<Node> clickedNode;
    static Node *clickedNode;
    static bool isClicked;
    static bool playerOn;
    static void setClickedNode(Node);
    static void setOccupiedNodes(Node);
    static void setAllNodes(Node);
    static bool checkIfNodeIsOccupied(Node, std::vector<Node>*);
    static Node getSpecificNode(Node);    

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
    static std::vector<int> getTilesOfANode(Node, std::vector<Tuile>*);
    static std::vector<int> getRessourceOfSpecificTiles(Node, std::vector<Tuile>*);
    int getNumberOfTuile();
    int getRessourceOfTuile();
    std::vector<Node>* getNodesCoordinates();
    void setNumberOfTuile(int);
    void setRessourceOfTuile(int);
    void setNodesCoordinates(int, int);

private:
    int numberOfTuile;
    int ressource;
    std::vector<Node> *nodes = new std::vector<Node>(6);
    int edges[6];
};


#endif