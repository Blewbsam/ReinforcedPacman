#include <iostream>
#include "agentUI.h"
#include "../globalsUI.h"




AgentUI::AgentUI(GameState * gameState, sf::Vector2f start) {
    this->gs = gameState;
    this->SFposition = start;
    this->sprite = new sf::Sprite();
    this->texture = new sf::Texture();
}

AgentUI::~AgentUI() {
    delete this->sprite;
    delete this->texture;    
}

void AgentUI::snapToGrid() { //remove:
    this->SFposition.x = std::round(SFposition.x / PIXEL_SIZE) * PIXEL_SIZE;
    this->SFposition.y = std::round(SFposition.y / PIXEL_SIZE) * PIXEL_SIZE;
}

void AgentUI::move(){
}

bool AgentUI::containedInCell() { 
    return (std::fmod(this->SFposition.x,PIXEL_SIZE) == 0 && std::fmod(this->SFposition.y,PIXEL_SIZE) == 0);
}

void AgentUI::setPositionForRendering() {
    if (gs->jumpAvail(this->getIndexedPosition())) this->setSFPosition(gs->jumpPortal(this->getIndexedPosition()));

    this->sprite->setPosition(this->SFposition.x-PIXEL_SIZE, this->SFposition.y);
}

void AgentUI::setOrientationForRendering(){}

Position AgentUI::getIndexedPosition() { // this
    Position pos(std::round((this->SFposition.x)/ PIXEL_SIZE),std::round((this->SFposition.y)/ PIXEL_SIZE));
    return pos;
}
void AgentUI::setSFPosition(Position pos) { //  this
    this->SFposition.x = pos.x * PIXEL_SIZE;
    this->SFposition.y = pos.y * PIXEL_SIZE;
}

void AgentUI::scaleSprite() {
    float scale = PIXEL_SIZE / FRAME_SIZE;
    this->sprite->setScale(scale,scale);
}


sf::Sprite AgentUI::getSprite() {
    return *(this->sprite);
}