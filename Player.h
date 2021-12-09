#ifndef PLAYER_H
#define PLAYER_H
#include "CatanElements.h"

class Player
{
public:
    Player();
    Player(int);
    ~Player();
    void setCorrespondedTiles(Node, std::vector<Tuile>*);
    void setRessources(Node, std::vector<Tuile>*, int = 0, bool = false);
    void setScore(int);
    bool buildRoute();
    bool buildSettlement();
    bool buildCity();
    int getScore();
    int getNumberOfPlayer();
    std::string getSettlment();
    void setAppropriateNode(Node);
    void setAppropriateEdge(Edge);
    static std::vector<Player> *allClickedNodes;
    static std::vector<Player> *allClickedEdges;
    Node getAppropriateNode();
    Edge getAppropriateEdge();

private:
    // we have 5 types of ressources: 1- Brique, 2- Pierre
    // 3- Mouton, 4- Blé, 5-Bois.
    std::vector<Node> *occupiedNodes = new std::vector<Node>();
    std::vector<int> ressources;
    std::vector<int> tiles;
    std::string settlment;
    std::string city;
    std::vector<std::string> *settlments = new std::vector<std::string>();
    std::vector<std::string> *cities = new std::vector<std::string>();
    int number;
    int score;
    Node hasNode;
    Edge hasEdge;
};

class GamePlay
{
public:
    GamePlay();
    ~GamePlay();
    // void firstSettlmentPlay();
    // void secondSettlmentPlay();
    // void loopPlay();
    int startDice();
    void enableBuilding();
    void enableBuildingRoute();
    void setPlayers();
    std::vector<Player>* getPlayers();

private:
    std::vector<Player> *players;
};
#endif