
#ifndef PACMANUI
#define PACMANUI

#include <SFML/Graphics.hpp>
#include "../game/globals.hpp"
#include "../game/game.hpp"
#include "globalsUI.hpp"
#include "ghosts/agentUI.hpp"





class PacmanUI : public AgentUI {
    private:
        Direction pacmanDir;
        Direction nextDir;

    public:
        PacmanUI(GameState * gamestate);

        // returns true if pacman is in proper position to
        // move in given direction.
        bool validPacmanMove(Direction dir);
    

        void move() override;

        // changes direction of pacman to specified dir
        void setNextDir(Direction dir);     

        // sets pacmanDir to nextDir
        void switchDirection();

        // returns row index of image to
        // be used for pacman animations
        int getRowIndex();

        // increases frame by one or resets it.
        void nextFrame();
        
        void setOrientationForRendering() override;
};



#endif