
#include "ambusherUI.h"
#include <SFML/Graphics.hpp>

#define AMBUSHER_STEP_SIZE 1


AmbusherUI::AmbusherUI(GameState * gameState) : GhostUI(gameState,sf::Vector2f(AMBUSHER_START_X,AMBUSHER_START_Y)){
    this->graphic->setFillColor(sf::Color::Magenta);
}



void AmbusherUI::move() {
    Direction ghostDir = this->gs->getAmbusherDir();
    GhostUI::move(ghostDir, AMBUSHER_STEP_SIZE);
    if (this->containedInCell()) gs->updateGhostPos(this->getIndexedPosition(),AMBUSHER);
}





