#include "ghostUI.h"

GhostUI::GhostUI(GameState * gameState, sf::Vector2f pos) : AgentUI(gameState,pos,new sf::RectangleShape(sf::Vector2f(PIXEL_SIZE,PIXEL_SIZE))){
    this->ghostDir = IDLE;
    this->active = false;
}

// Gets which direction to move from gameState and moves in given direction.
void GhostUI::move(){
    // this->gs->
    return;
}

sf::RectangleShape GhostUI::getGraphic() {
    sf::RectangleShape * shape = dynamic_cast<sf::RectangleShape *>(this->graphic);
    return *shape;
}

void GhostUI::awake() {
    this->active = true;
}
