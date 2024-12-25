
#include "stupidUI.h"
#include <SFML/Graphics.hpp>



StupidUI::StupidUI(GameState * gameState) : GhostUI(gameState,sf::Vector2f(STUPID_START_X,STUPID_START_Y)){
    this->graphic->setFillColor(sf::Color::Green);
}


