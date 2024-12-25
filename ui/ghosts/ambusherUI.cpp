
#include "ambusherUI.h"
#include <SFML/Graphics.hpp>



AmbusherUI::AmbusherUI(GameState * gameState) : GhostUI(gameState,sf::Vector2f(AMBUSHER_START_X,AMBUSHER_START_Y)){
    this->graphic->setFillColor(sf::Color::Magenta);
}