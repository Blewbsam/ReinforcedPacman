
#include "fickleUI.h"
#include <SFML/Graphics.hpp>



FickleUI::FickleUI(GameState * gameState) : GhostUI(gameState,sf::Vector2f(FICKLE_START_X,FICKLE_START_Y)){
    this->graphic->setFillColor(sf::Color::Cyan);
}