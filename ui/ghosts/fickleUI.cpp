
#include "fickleUI.h"
#include <SFML/Graphics.hpp>

#define FICKLE_STEP_SIZE 1

FickleUI::FickleUI(GameState * gameState) : GhostUI(gameState,sf::Vector2f(FICKLE_START_X,FICKLE_START_Y)){
    this->graphic->setFillColor(sf::Color::Cyan);
}

void FickleUI::move() {
    Direction ghostDir = this->gs->getFickleDir();
    GhostUI::move(ghostDir,FICKLE_STEP_SIZE);
    if (this->containedInCell()) gs->updateGhostPos(this->getIndexedPosition(),FICKLE);
}