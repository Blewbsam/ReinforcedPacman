#include <iostream>
#include "agentUI.hpp"
#include "../globalsUI.hpp"




AgentUI::AgentUI(sf::Vector2f start) {
    this->SFposition = start;
    this->sprite = new sf::Sprite();
    this->texture = new sf::Texture();
}

AgentUI::~AgentUI() {
    delete this->sprite;
    delete this->texture;    
}

void AgentUI::snapToGrid() { // not being used anywhere
    this->SFposition.x = std::round(SFposition.x / PIXEL_SIZE) * PIXEL_SIZE;
    this->SFposition.y = std::round(SFposition.y / PIXEL_SIZE) * PIXEL_SIZE;
}

void AgentUI::move(){
}

bool AgentUI::containedInCell() {
    const float tolerance = 1e-5;  // A small tolerance to account for floating-point precision issues
    return (std::abs(std::fmod(this->SFposition.x, PIXEL_SIZE)) < tolerance) &&
           (std::abs(std::fmod(this->SFposition.y, PIXEL_SIZE)) < tolerance);
}


void AgentUI::setPositionForRendering() {
    this->sprite->setPosition(this->SFposition.x-PIXEL_SIZE, this->SFposition.y);
}

void AgentUI::setOrientationForRendering(){}


Position AgentUI::getIndexedPosition() { // 
    Position pos(std::round((this->SFposition.x)/ PIXEL_SIZE),std::round((this->SFposition.y)/ PIXEL_SIZE));
    return pos;
}
void AgentUI::setSFPosition(Position pos) { 
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