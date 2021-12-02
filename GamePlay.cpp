#include "GamePlay.h"
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