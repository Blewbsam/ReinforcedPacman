#include <iostream>
#include "agentUI.h"
#include "../globalsUI.h"




AgentUI::AgentUI(GameState * gameState, sf::Vector2f start, sf::Shape * shape) {
    this->gs = gameState;
    this->SFposition = start;
    this->graphic = shape;
    this->sprite = new sf::Sprite();
    this->texture = new sf::Texture();
}

AgentUI::~AgentUI() {
    delete this->graphic;
    delete this->sprite;
    delete this->texture;    
}


void AgentUI::snapToGrid() {
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
    this->graphic->setPosition(this->SFposition.x, this->SFposition.y);
}


Position AgentUI::getIndexedPosition() { // this
    Position pos(std::round((this->SFposition.x)/ PIXEL_SIZE),std::round((this->SFposition.y)/ PIXEL_SIZE));
    return pos;
}
void AgentUI::setSFPosition(Position pos) { //  this
    this->SFposition.x = pos.x * PIXEL_SIZE;
    this->SFposition.y = pos.y * PIXEL_SIZE;
}


sf::Sprite AgentUI::getSprite() {
    return *(this->sprite);
}