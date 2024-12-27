#include <iostream>

#include "pacmanUI.h"

sf::Vector2f startPos = sf::Vector2f(PACMAN_START_X * PIXEL_SIZE, PACMAN_START_Y * PIXEL_SIZE);

PacmanUI::PacmanUI(GameState * gameState) : AgentUI(gameState,startPos,new sf::CircleShape(PACMAN_RADIUS)) {
    // this->graphic.setRadius(PACMAN_RADIUS);
    this->graphic->setFillColor(sf::Color::Yellow);
    this->pacmanDir = IDLE;
    this->nextDir = RIGHT;
    this->frame = 0;
    this->animationSpeed = 0.1f;
    if (!this->texture->loadFromFile("animations/PacmanAnimation.png")) {
        std::cerr << "Failed to load Pacman animation texture!" << std::endl;
        return;
    } else {
        std::cout << "Success" << std::endl;
    }
    this->sprite->setTexture(*this->texture);

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

void PacmanUI::setOrientationForRendering() {
    if (this->animationClock.getElapsedTime().asSeconds() > this->animationSpeed) {
        // Cycle through animation states
		this->sprite->setTextureRect(sf::IntRect(FRAME_SIZE * this->frame, FRAME_SIZE * this->getRowIndex(), FRAME_SIZE, FRAME_SIZE));

        // must scale sprite up to CELL_SIZE
        this->scaleSprite();

        this->nextFrame();
        this->animationClock.restart();   
    }
}


void PacmanUI::setPositionForRendering() {
    if (gs->jumpAvail(this->getIndexedPosition())) this->setSFPosition(gs->jumpPortal(this->getIndexedPosition()));
    this->sprite->setPosition(this->SFposition.x, this->SFposition.y);
}


int PacmanUI::getRowIndex() {
    switch (this->pacmanDir) {
        case RIGHT: return 0;
        case UP: return 1;
        case LEFT: return 2;
        default: return 3;
    }
}

void PacmanUI::nextFrame() {
    this->frame = (this->frame + 1) % 5;
}