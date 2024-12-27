
#include <iostream>
#include "chaserUI.h"
#include <SFML/Graphics.hpp>


#define CHASER_STEP_SIZE 1

ChaserUI::ChaserUI(GameState * gameState) : GhostUI(gameState,sf::Vector2f(CHASER_START_X,CHASER_START_Y),sf::Color::Red){
    this->awake();
}


void ChaserUI::move() {
    Direction ghostDir = this->gs->getGhostDir(CHASER);
    GhostUI::move(ghostDir, CHASER_STEP_SIZE);
    if (this->containedInCell()) gs->updateGhostPos(this->getIndexedPosition(),CHASER);
}


