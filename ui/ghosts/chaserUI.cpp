
#include <iostream>
#include "chaserUI.h"
#include <SFML/Graphics.hpp>


#define CHASER_STEP_SIZE 1

ChaserUI::ChaserUI(GameState * gameState) : GhostUI(gameState,sf::Vector2f(CHASER_START_X,CHASER_START_Y)){
    this->graphic->setFillColor(sf::Color::Red);
    this->awake();
}


void ChaserUI::move() {
    Direction ghostDir = this->gs->getChaserDir();
    switch (ghostDir) {
        case UP:    SFposition.y -= CHASER_STEP_SIZE; break;
        case DOWN:  SFposition.y += CHASER_STEP_SIZE; break;
        case LEFT:  SFposition.x -= CHASER_STEP_SIZE; break;
        case RIGHT: SFposition.x += CHASER_STEP_SIZE; break;
        default:    std::cout<<"None"<<std::endl; break;
    }

    if (this->containedInCell()) gs->updateGhostPos(this->getIndexedPosition(),CHASER);
}


