
#ifndef PACMANUI
#define PACMANUI

#include <SFML/Graphics.hpp>
#include "../game/globals.h"
#include "../game/game.h"
#include "globalsUI.h"
#include "ghosts/agentUI.h"





class PacmanUI : public AgentUI {
    private:
        Direction pacmanDir;
        Direction nextDir;

        int animationCycle;
        sf::Clock animationClock;
        flaot animationSpeed;

    public:
        PacmanUI(GameState * gamestate);

        sf::CircleShape getGraphic();

        bool validPacmanMove(Direction dir);

        void move() override;

        // changes direction of pacman to specified dir
        void setNextDir(Direction dir);     

        // sets pacmanDir to nextDir
        void switchDirection();

        void animationUpdate();

};



#endif