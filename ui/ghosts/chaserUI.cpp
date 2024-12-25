

#include "chaserUI.h"
#include <SFML/Graphics.hpp>



ChaserUI::ChaserUI(GameState * gameState) : GhostUI(gameState,sf::Vector2f(CHASER_START_X,CHASER_START_Y)){
    this->graphic->setFillColor(sf::Color::Red);
    this->awake();
}