
#ifndef GHOSTUI
#define GHOSTUI


#include "../../game/game.h"
#include <SFML/Graphics.hpp>
#include "../../game/globals.h"
#include "agentUI.h"
#include "../globalsUI.h"

class GhostUI : public AgentUI {
    protected:
        Direction ghostDir;
        bool active;
    public:
        GhostUI(GameState * gameState, sf::Vector2f pos);

        sf::RectangleShape getGraphic();
        
        // Specifications similar to pacmanUI
        virtual void move() override;

        // sets active to true for game to start.
        void awake();
};


#endif