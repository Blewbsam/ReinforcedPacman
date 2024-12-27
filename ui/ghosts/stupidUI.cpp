
#include "stupidUI.h"
#include <SFML/Graphics.hpp>


#define STUPID_STEP_SIZE 1

sf::Color clydeColor(255, 165, 0);

StupidUI::StupidUI(GameState * gameState) : GhostUI(gameState,sf::Vector2f(STUPID_START_X,STUPID_START_Y),clydeColor){}

void StupidUI::move() {
    Direction ghostDir =this->gs->getGhostDir(STUPID);
    GhostUI::move(ghostDir, STUPID_STEP_SIZE);
    if (this->containedInCell()) gs->updateGhostPos(this->getIndexedPosition(),STUPID);
}
