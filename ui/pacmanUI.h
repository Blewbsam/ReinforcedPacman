
#ifndef PACMANUI
#define PACMANUI

#include <SFML/Graphics.hpp>
#include "../game/globals.h"
#include "../game/game.h"
#include "globalsUI.h"




class PacmanUI {
    private:
        GameState * gs;
        Direction pacmanDir;
        // Pacman's current direction
        Direction nextDir;
        // Position of unique game objects
        sf::Vector2f SFposition;
        // Next Direction Pacman should have. Set by events
    public:
        sf::CircleShape graphic;

        PacmanUI(GameState * gamestate);

        // changes direction of pacman to specified dir
        void setNextDir(Direction dir); 
        // snap pacman position to nearest valid grid.
        void snapPacmanToGrid(); 
        // returns true if pacman can move in given direciton, false otherwise
        bool validPacmanMove(Direction dir); 
        // Moves pacman in specified direction.
        void pacmanMove(); 
        // returns true if pacman is in single PIXEL sized cell
        bool pacmanContainedInCell(); 
        // pacmanPos setter
        void setPositionForRendering();

        // conersts Vector2f pacmanPos to Position struct
        Position getIndexedPosition();


};



#endif