#include <iostream>

#include "pacmanUI.h"


sf::Vector2f startPos = sf::Vector2f(PACMAN_START_X * PIXEL_SIZE, PACMAN_START_Y * PIXEL_SIZE);

PacmanUI::PacmanUI(GameState * gameState) : AgentUI(gameState,startPos,new sf::CircleShape(PACMAN_RADIUS)) {
    // this->graphic.setRadius(PACMAN_RADIUS);
    this->graphic->setFillColor(sf::Color::Yellow);
    this->pacmanDir = IDLE;
    this->nextDir = RIGHT;
}

sf::CircleShape PacmanUI::getGraphic() {
    sf::CircleShape * circle = dynamic_cast<sf::CircleShape*>(this->graphic);
    return *circle;
}


void PacmanUI::setNextDir(Direction dir) {
    this->nextDir = dir;
}

bool PacmanUI::validPacmanMove(Direction dir)  {
    return this->containedInCell() && gs->validPacmanMove(dir);
}

void PacmanUI::move() { 
    if (this->containedInCell() && this->nextDir != this->pacmanDir && gs->validPacmanMove(this->nextDir)) this->switchDirection();
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
    if (this->containedInCell()) gs->updatePacmanPos(this->getIndexedPosition());
}
void PacmanUI::switchDirection() {
    this->pacmanDir = this->nextDir;
    this->gs->changePacmanDir(this->pacmanDir);
}