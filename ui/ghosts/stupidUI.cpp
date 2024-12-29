
#include "stupidUI.h"
#include <SFML/Graphics.hpp>
#include "speeds.h"

sf::Color clydeColor(255, 165, 0);

StupidUI::StupidUI(GameState * gameState) : GhostUI(gameState,sf::Vector2f(STUPID_START_X,STUPID_START_Y),clydeColor,STUPID){}