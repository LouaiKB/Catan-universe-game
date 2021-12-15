#ifndef CATANELEMENTS_H
#define CATAELEMENTS_H
#include <iostream>
#include <array>
#include <vector>
#include <random>
#include <algorithm>

/**
 * @brief Node class to create node objects, that correspond to the interaction
 * of tiles in the mainboard
 */
class Node
{
public:
    Node();
    /**
     * @brief Construct a new Node object
     * @param int-x the x coordonant of the node
     * @param int-y the y coordonant of the node
     * 
     */
    Node(int, int);
    ~Node();
    
    // All static methods, i use static to group all the Node objects
    /**
     * @brief pointer vector of all the Nodes in the main board
     * 
     */
    static std::vector<Node> *allNodes;
    /**
     * @brief pointer vector of all occupied nodes to control the game
     * 
     */
    static std::vector<Node> *occupiedNodes;
    /**
     * @brief pointer vector of all clicked nodes
     * 
     */
    static std::vector<Node> *allClickedNodes;
    /**
     * @brief array that will be allocated dynamically to stock
     * the actual clicked node
     * 
     */
    static Node *clickedNode;
    /**
     * @brief boolean values for the buttons
     * 
     */
    static bool isClicked;
    static bool playerOn;
    static bool buildRoute;
    /**
     * @brief Set the Clicked Node object to the dynamic array
     * 
     */
    static void setClickedNode(Node);
    /**
     * @brief Set the Occupied Nodes object to the occupied nodes vector
     * 
     */
    static void setOccupiedNodes(Node);
    /**
     * @brief Set the All Nodes object to the all nodes vector
     * 
     */
    static void setAllNodes(Node);
    /**
     * @brief check if a node exists in a vector of nodes
     * 
     * @return true 
     * @return false 
     */
    static bool checkIfNodeExists(Node, std::vector<Node>*);
    /**
     * @brief Get the Specific clicked Node object from the available nodes 
     * 
     * @return Node 
     */
    static Node getSpecificNode(Node);  

    // class methods
    /**
     * @brief Setter method to set the node to occupied or not
     * 
     */
    void setOccupied();
    /**
     * @brief boolean method to check if a node is occupied
     * 
     * @return true 
     * @return false 
     */
    bool isOccupied();
    /**
     * @brief Set the Adjacent Nodes for a clicked node that have a settlment
     * to have the three adjacent nodes to disable building in these nodes 
     * 
     */
    void setAdjacentNodes();
    std::vector<Node> getAdjacentNodes();
    int getX();
    int getY();

private:
/**
 * @brief x coordonant, y coordonants, occupied to set if a node is occupied or not
 * and the vector of adjacent nodes
 * 
 */
    int x;
    int y;
    bool occupied;
    std::vector<Node> adjacentNodes;   
};

/**
 * @brief Edge class inherits from the Node class, we consider the edge as a node
 * object to inherit all the same methods of node class 
 * 
 */

class Edge : public Node
{
public:
    Edge();
    /**
     * @brief Construct a new Edge object
     * @param int-x coordonant
     * @param int-y coordonant
     * @param int-radiusX the x coordonant of the radius
     * @param int-radiusY the y coordonant of the radius
     * 
     */
    Edge(int, int, int, int);
    ~Edge();

    // here we will have the same caracteristics of node class but to deal and stock Edge objects
    static std::vector<Edge> *allEdges;
    static bool checkIfNodeExists(Edge, std::vector<Edge>*);
    static void setAllEdges(Edge);
    // get nodes of an edge using the radius x and radius y and return them in a vecotr
    static std::vector<Node> getNodesOfAnEdge(Edge);
    static void setClickedNode(Edge);
    static Edge getSpecificEdge(Node, std::vector<Edge>*);
    static Edge* clickedEdge;
    static bool isClicked;
    /**
     * @brief Get the x coordonant of Radius
     * 
     * @return int 
     */
    int getRadiusX();
    /**
     * @brief Get the y coordonant of Radius
     * 
     * @return int 
     */
    int getRadiusY();

private:
    int radiusX;
    int radiusY;
};

/**
 * @brief Tile class 
 * 
 */
class Tuile
{
public:
    Tuile();
    ~Tuile();
    /**
     * @brief Get the Number Of a tile from the main board
     * 
     * @return int 
     */
    int getNumberOfTuile();
    /**
     * @brief Get the Ressource Of tile from the main board
     * 
     * @return int 
     */
    int getRessourceOfTuile();
    /**
     * @brief Get the Nodes Coordinates of a tile object in a vector
     * 
     * @return std::vector<Node>* (pointer for memory optimization)
     */
    std::vector<Node>* getNodesCoordinates();
    /**
     * @brief Get the Edges Coordinates of a tile object in a vecto
     * 
     * @return std::vector<Edge>* 
     */
    std::vector<Edge>* getEdgesCoordinates();
    // setters to set the number, the ressource, 
    // the nodes coordinates and Edge coordinates of a tile object
    void setNumberOfTuile(int);
    void setRessourceOfTuile(int);
    void setNodesCoordinates(int, int);
    void setEdgesCoordinates();
    // static method to get the edge coordinates from the nodes
    static Edge getMiddleBetweenTwoNodes(Node, Node);

private:
    int numberOfTuile;
    int ressource;
    // the nodes of a tile
    std::vector<Node> *nodes = new std::vector<Node>(6);
    // the edges of a tile
    std::vector<Edge> *edges = new std::vector<Edge>(6);
};


#endif