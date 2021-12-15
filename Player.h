#ifndef PLAYER_H
#define PLAYER_H
#include "CatanElements.h"

/**
 * @brief Player class to create player object for each player
 * 
 */
class Player
{
public:
    /**
     * @brief Construct a new Player object, and destruct the object at the
     * end
     */
    Player();
    Player(int);
    ~Player();
    /**
     * @brief Set the Corresponded Tiles object, for each player set the corresponded
     *  tiles, at a specific position in the main board
     * @param nodeObject is the occupied node
     * @param allTiles a pointer for the vector that has all the tiles of the main board
     */
    void setCorrespondedTiles(Node, std::vector<Tuile>*);
    /**
     * @brief Set the Ressources for the player object considerating the dice value,
     * @param nodeObject the occupied node by the player
     * @param allTiles a pointer for the vector that has all the tiles of the main board
     * @param diceValue setted by default to zero, and accepts a value of the dice
     * @param isDiceActive active the dice value recuperation after the two first stages
     * 
     */
    void setRessources(Node, std::vector<Tuile>*, int = 0, bool = false);
    /**
     * @brief Set the Score object
     * 
     */
    void setScore(int);
    /**
     * @brief boolean function to check if the player have enough ressources,
     * to build a route
     * 
     * @return true
     * @return false 
     */
    bool buildRoute();
    /**
     * @brief boolean function to check if the player have enough ressources,
     * to build a settlment
     * 
     * @return true 
     * @return false 
     */
    bool buildSettlement();
    /**
     * @brief boolean function to check if the player have enough ressources to 
     * build a city
     * 
     * @return true 
     * @return false 
     */
    bool buildCity();
    /**
     * @brief Get the Score object, getter method
     * 
     * @return int (score)
     */
    int getScore();
    /**
     * @brief Get the Number Of Player object, getter method
     * 
     * @return int (number of player 1,2,3 ...)
     */
    int getNumberOfPlayer();
    /**
     * @brief each function of these will get the Number of each
     *  ressources of each player object
     *  to show it in the main board in the resources frame
     * 
     * @return int (number of Brick ressources )
     */
    int getNumberOfBrick();
    int getNumberOfLumber();
    int getNumberOfGrain();
    int getNumberOfOre();
    int getNumberOfWool();
    /**
     * @brief Get the Settlment path
     * 
     * @return std::string (settlment path)
     */
    std::string getSettlment();
    /**
     * @brief remove ressource after building (route, city, settlment...)
     * @param int ressource the number of the ressource to be removed from the ressource
     * vector 
     * 
     */
    void removeRessourceAfterBuilding(int);
    /**
     * @brief Set the Appropriate Node object for the player
     * each player will choose a node in which, the player will build
     * @param Node-nodeObject the choosed Node
     */
    void setAppropriateNode(Node);
    /**
     * @brief Set the Appropriate Edge object for the player
     * each player will choose an Edge in which, the player will build the route
     * @param Edge-edgeObject the choosed Edge
     */
    void setAppropriateEdge(Edge);
    /**
     * @brief static vector of Player objects to get all the occupied nodes 
     * and all the occupied edges for all the players
     * static is used to reference all the Player objects
     * for optimizing the memory and game performance, i used pointers
     */
    static std::vector<Player> *allClickedNodes;
    static std::vector<Player> *allClickedEdges;
    /**
     * @brief Get the Appropriate Node object of the player
     * 
     * @return Node 
     */
    Node getAppropriateNode();
    /**
     * @brief Get the Appropriate Edge object of the player
     * 
     * @return Edge 
     */
    Edge getAppropriateEdge();

private:
    /**
     * @brief Attribute pointer vector of Nodes to stock the occupied nodes of each player
     * 
     */
    std::vector<Node> *occupiedNodes = new std::vector<Node>();
    // we have 5 types of ressources: 1- Brique, 2- Pierre (Ore)
    // 3- Mouton, 4- Blé(Grain), 5-Bois (Lumber).
    /**
     * @brief vector of ressources and tiles of each player
     * 
     */
    std::vector<int> ressources;
    std::vector<int> tiles;
    /**
     * @brief settelment and city path (as string)
     * 
     */
    std::string settlment;
    std::string city;
    /**
     * @brief vector of all settlments and cities of each player
     * 
     */
    std::vector<std::string> *settlments = new std::vector<std::string>();
    std::vector<std::string> *cities = new std::vector<std::string>();
    /**
     * @brief number of player and the score of player
     * 
     */
    int number;
    int score;
    /**
     * @brief hasNode and hasEdge are the clicked nodes and edges in the main board
     * 
     */
    Node hasNode;
    Edge hasEdge;
};

/**
 * @brief Class to link the game play with the front end
 * 
 */
class GamePlay
{
public:
    GamePlay();
    ~GamePlay();
    /**
     * @brief start the dice by choosing a random int number between 2 and 12
     * 
     * @return int 
     */
    int startDice();
    /**
     * @brief these two methods will set the boolean values for building the settlement, city and the route
     * 
     */
    void enableBuilding();
    void enableBuildingRoute();
};
#endif