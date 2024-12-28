
#include <iostream>
#include "chaserUI.h"
#include <SFML/Graphics.hpp>
#include "speeds.h"


#define CHASER_STEP_SIZE 1

ChaserUI::ChaserUI(GameState * gameState) : GhostUI(gameState,sf::Vector2f(CHASER_START_X,CHASER_START_Y),sf::Color::Red,CHASER){}



