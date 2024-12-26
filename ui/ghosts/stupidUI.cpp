
#include "stupidUI.h"
#include <SFML/Graphics.hpp>


#define STUPID_STEP_SIZE 1

StupidUI::StupidUI(GameState * gameState) : GhostUI(gameState,sf::Vector2f(STUPID_START_X,STUPID_START_Y)){
    this->graphic->setFillColor(sf::Color::Green);
}


void StupidUI::move() {
    Direction ghostDir =this->gs->getStupidDir();
    GhostUI::move(ghostDir, STUPID_STEP_SIZE);
    if (this->containedInCell()) gs->updateGhostPos(this->getIndexedPosition(),STUPID);
}


