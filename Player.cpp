#include "Player.h"

Player::Player(int num) : number(num) {
    this->score = 0;
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
        if (Node::checkIfNodeIsOccupied(node, nodes)) {
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
            if (Node::checkIfNodeIsOccupied(node, nodes)) {
                this->ressources.push_back(allTiles->at(i).getRessourceOfTuile());
            }
        }
    }
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
    return (numberOfBriks != 0 && numberOfLumbers != 0 && numberOfGrain != 0 && numberOfWool != 0);
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
    return (numberOfGrain >= 2 && numberOfOre >= 3);
}

