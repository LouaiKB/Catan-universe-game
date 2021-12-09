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
    static bool checkIfNodeExists(Node, std::vector<Node>*);
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

class Edge : public Node
{
public:
    Edge();
    Edge(int, int, int, int);
    ~Edge();
    static std::vector<Edge> *allEdges;
    static bool checkIfNodeExists(Edge, std::vector<Edge>*);
    static void setAllEdges(Edge);
    static std::vector<Node> getNodesOfAnEdge(Edge);
    static void setClickedNode(Edge);
    static Edge getSpecificEdge(Node, std::vector<Edge>*);
    static Edge* clickedEdge;
    static bool isClicked;
    int getRadiusX();
    int getRadiusY();

private:
    int radiusX;
    int radiusY;
};

class Tuile
{
public:
    Tuile();
    ~Tuile();
    int getNumberOfTuile();
    int getRessourceOfTuile();
    std::vector<Node>* getNodesCoordinates();
    std::vector<Edge>* getEdgesCoordinates();
    void setNumberOfTuile(int);
    void setRessourceOfTuile(int);
    void setNodesCoordinates(int, int);
    void setEdgesCoordinates();
    static Edge getMiddleBetweenTwoNodes(Node, Node);

private:
    int numberOfTuile;
    int ressource;
    std::vector<Node> *nodes = new std::vector<Node>(6);
    // int edges[6];
    std::vector<Edge> *edges = new std::vector<Edge>(6);
};


#endif