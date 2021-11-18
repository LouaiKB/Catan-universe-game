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
    static std::vector<std::vector<int>> occupiedNodes;
    static void setOccupiedNodes(std::vector<int>);
    static bool checkIfNodeIsOccupied(std::vector<int>);
    int getX();
    int getY();

private:
    int x;
    int y;
    bool occupied;
};
class Tuile
{
public:
    Tuile();
    ~Tuile();
    int getNumberOfTuile();
    int getRessourceOfTuile();
    std::array<Node, 6> getNodesCoordinates();
    void setNumberOfTuile(int);
    void setRessourceOfTuile(int);
    void setNodesCoordinates(int, int);

private:
    int numberOfTuile;
    int ressource;
    std::array<Node, 6> nodes;
    int edges[6];
};


#endif