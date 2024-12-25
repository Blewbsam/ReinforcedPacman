
#ifndef GHOSTAI
#define GHOSTAI

#include "globals.h"
#include "ghost.h"
#include "pacman.h"

class GameState; // forward decleration

// GhostAI determines movement of ghosts on grid
class GhostAI {

    GameState * gs;


public:
    GhostAI(GameState * gameState);
    // mvoes set the Direction of Ghost appropriately depending on their State and Position
    void moveChaser(ChaserGhost * chaser, Pacman * pacman);
    void moveAmbusher(AmbusherGhost * ambusher, Pacman * pacman);
    void moveFickle(FickleGhost * fickle, Pacman * pacman);
    void moveStupid(StupidGhost * stupid, Pacman * pacman);



private:
    // determine how ghosts should move.

    // moveChaser
    // getpacman pos
    // get chaserPos
    // getValidPositions 
    // calculate euclidian distances to pacman from valid positions
    // pick the minimum.
    // move chaser in that direction.
    void moveChaseChaser(ChaserGhost * chaser, Pacman * pacman);
    void moveChaseAmbusher(AmbusherGhost * ambusher, Pacman * pacman);
    void moveChaseFickle(FickleGhost * fickle, Pacman * pacman);
    void moveChaseStupid(StupidGhost * stupid, Pacman * pacman);




    // move to helpers later
    // helpers
    double calculateEuclidianDistance(Position pos1, Position pos2) const;
    
    // Gets which direction ghost should move in inorder to go on neighbour
    // requires ghost Posito and neighPos to be neighbouring cells
    Direction getNeighbourDirection(Position ghostPos, Position neighPos) const;
}; 

#endif