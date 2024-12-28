
#include "fickleUI.h"
#include <SFML/Graphics.hpp>
#include "speeds.h"



FickleUI::FickleUI(GameState * gameState) : GhostUI(gameState,sf::Vector2f(FICKLE_START_X,FICKLE_START_Y),sf::Color::Cyan,FICKLE){
    this->sprite->setColor(sf::Color::Cyan);
}
