#include <iostream>

#include "pacmanUI.h"


PacmanUI::PacmanUI(GameState * gameState) {
    this->gs  = gameState;
    this->graphic.setRadius(PACMAN_RADIUS);
    this->graphic.setFillColor(sf::Color::Yellow);
    this->SFposition.x = PACMAN_START_X * PIXEL_SIZE;
    this->SFposition.y = PACMAN_START_Y * PIXEL_SIZE;
    this->pacmanDir = IDLE;
    this->nextDir = RIGHT;
}


void PacmanUI::setNextDir(Direction dir) {
    this->nextDir = dir;
}


void PacmanUI::snapPacmanToGrid() {
    SFposition.x = std::round(SFposition.x / PIXEL_SIZE) * PIXEL_SIZE;
    SFposition.y = std::round(SFposition.y / PIXEL_SIZE) * PIXEL_SIZE;
}

bool PacmanUI::validPacmanMove(Direction dir)  {
    return this->pacmanContainedInCell() && gs->validPacmanMove(dir);
}


void PacmanUI::pacmanMove() {
    if (this->pacmanContainedInCell() && this->nextDir != this->pacmanDir && gs->validPacmanMove(this->nextDir)) this->pacmanDir = this->nextDir;
    if (gs->validPacmanMove(pacmanDir)) {
        switch (pacmanDir) {
            case UP:    SFposition.y -= PACMAN_STEP_SIZE; break;
            case DOWN:  SFposition.y += PACMAN_STEP_SIZE; break;
            case LEFT:  SFposition.x -= PACMAN_STEP_SIZE; break;
            case RIGHT: SFposition.x += PACMAN_STEP_SIZE; break;
            default:    break;
        }
    }
    // gs should know position of pacman for generating valid moves.
    if (pacmanContainedInCell()) gs->updatePacmanPos(this->getIndexedPosition());
    gs->handlePelletCollision();
}

bool PacmanUI::pacmanContainedInCell() {
    return (std::fmod(this->SFposition.x,PIXEL_SIZE) == 0 && std::fmod(this->SFposition.y,PIXEL_SIZE) == 0);
}

\
void PacmanUI::setPositionForRendering() {
    this->graphic.setPosition(this->SFposition.x, this->SFposition.y);
}


Position PacmanUI::getIndexedPosition() {
    Position pos;
    pos.x = std::round((this->SFposition.x)/ PIXEL_SIZE);
    pos.y = std::round((this->SFposition.y)/ PIXEL_SIZE);
    return pos;
}


