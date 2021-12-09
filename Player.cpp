#include "Player.h"

GamePlay::GamePlay() {}
GamePlay::~GamePlay() {}

// void GamePlay::firstSettlmentPlay() {}
// void GamePlay::secondSettlmentPlay() {}
// void GamePlay::loopPlay() {}

int GamePlay::startDice() 
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(2, 12);
    return distr(gen);
}

void GamePlay::enableBuilding()
{
    Node::playerOn = true;
}

void GamePlay::enableBuildingRoute()
{
    Node::buildRoute = true;
}

void GamePlay::setPlayers()
{
    this->players->push_back(Player(1));
    this->players->push_back(Player(2));
}

std::vector<Player>* GamePlay::getPlayers()
{
    return this->players;
}

Player::Player() {}

Player::Player(int num) : number(num) {
    this->score = 0;
    switch (this->number)
    {
    case 1:
        this->settlment = "Tokens/green_house.png";
        this->city = "Tokens/green_city";
        break;
    
    case 2:
        this->settlment = "Tokens/blue_house.png";
        this->city = "Tokens/blue_city.png";
        break;
    
    case 3:
        this->settlment = "Tokens/red_house.png";
        this->city = "Tokens/red_city.png";
        break;
    
    case 4:
        this->settlment = "Tokens/orange_house.png";
        this->city = "Tokens/orange_city.png";
        break;
    
    case 5:
        this->settlment = "Tokens/brown_house.png";
        this->city = "Tokens/brown_city.png";
        break;

    case 6:
        this->settlment = "Tokens/white_house.png";
        this->city = "Tokens/white_city.png";
        break;
    
    default:
        break;
    }       
}

Player::~Player() {}

void Player::setScore(int num) 
{
    this->score += num;
}

int Player::getScore()
{
    return this->score;
}

int Player::getNumberOfPlayer()
{
    return this->number;
}

void Player::setCorrespondedTiles(Node node, std::vector<Tuile> *allTiles)
{
    for (int i = 0; i < allTiles->size(); i++) {
        // know we will parse each node of the tile 
        std::vector<Node>* nodes = allTiles->at(i).getNodesCoordinates();
        if (Node::checkIfNodeExists(node, nodes)) {
            this->tiles.push_back(allTiles->at(i).getNumberOfTuile());
        }
    }
}

void Player::setRessources(Node node, std::vector<Tuile> *allTiles, int diceValue, bool isDiceActive)
{
    if(isDiceActive) {
        bool isTileFound; 
        for (int i = 0; i < allTiles->size(); i++) {
            int currentTile = allTiles->at(i).getNumberOfTuile();
            isTileFound = (std::find(this->tiles.begin(), this->tiles.end(), currentTile) != tiles.end());
            if (diceValue == currentTile && isTileFound) {
                this->ressources.push_back(allTiles->at(i).getRessourceOfTuile());
            }
        }
    } else {
        for (int i = 0; i < allTiles->size(); i++) {
            // know we will parse each node of the tile 
            std::vector<Node>* nodes = allTiles->at(i).getNodesCoordinates();
            if (Node::checkIfNodeExists(node, nodes)) {
                this->ressources.push_back(allTiles->at(i).getRessourceOfTuile());
            }
        }
    }
}

std::string Player::getSettlment()
{
    return this->settlment;
}

bool Player::buildRoute()
{
    // nombre de briques et de bois
    int numberOfBriks = 0, numberOfLumbers = 0;

    for (int i = 0; i < this->ressources.size(); i++) {
        if (ressources[i] == 1)
            numberOfBriks += 1;
        
        if (ressources[i] == 5)
            numberOfLumbers += 1;
    }
    return (numberOfBriks != 0 && numberOfLumbers != 0);
}

bool Player::buildSettlement()
{
    int numberOfBriks = 0, numberOfLumbers = 0, numberOfGrain = 0, numberOfWool = 0;

    for (int i = 0; i < this->ressources.size(); i++) {
        switch (ressources[i]) {
        case 1:
            numberOfBriks += 1;
            break;
        case 5:
            numberOfLumbers += 1;
            break;
        case 4:
            numberOfGrain += 1;
            break;
        case 3:
            numberOfWool += 1;
            break;
        default:
            break;
        }
    }
    if (numberOfBriks != 0 && numberOfLumbers != 0 
        && numberOfGrain != 0 && numberOfWool != 0) {
            this->settlments->push_back(this->settlment);
            return true;
    } else {
        return false;
    }

}

bool Player::buildCity()
{
    int numberOfGrain = 0, numberOfOre = 0;

    for (int i = 0; i < this->ressources.size(); i++) {
        if (ressources[i] == 4)
            numberOfGrain += 1;
        if (ressources[i] == 2)
            numberOfOre += 1;
    }
    if (numberOfGrain >= 2 && numberOfOre >= 3) {
        this->cities->push_back(this->city);
        return true;
    } else {
        return false;
    }
}

void Player::setAppropriateNode(Node node)
{
    this->hasNode = node;
}

void Player::setAppropriateEdge(Edge edge)
{
    this->hasEdge = edge;
}


Node Player::getAppropriateNode()
{
    return this->hasNode;
}

Edge Player::getAppropriateEdge()
{
    return this->hasEdge;
}

std::vector<Player> *Player::allClickedNodes = new std::vector<Player>();
std::vector<Player> *Player::allClickedEdges = new std::vector<Player>();