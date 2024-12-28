
#include "ambusherUI.h"
#include <SFML/Graphics.hpp>
#include "speeds.h"


AmbusherUI::AmbusherUI(GameState * gameState) : GhostUI(gameState,sf::Vector2f(AMBUSHER_START_X,AMBUSHER_START_Y),sf::Color::Magenta,AMBUSHER){
    
}
