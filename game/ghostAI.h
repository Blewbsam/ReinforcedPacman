
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
    void moveFickle(FickleGhost * fickle, Pacman * pacman, Position chaserPos);
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
    void moveChaseFickle(FickleGhost * fickle, Pacman * pacman, Position chaserPos);
    void moveChaseStupid(StupidGhost * stupid, Pacman * pacman);



    // helpers
    // gets position which is of least distance from srcPos
    Position getMinEuclidianPosition(std::vector<Position>& possiblePositions, Position srcPos) const;

    int calculateManhattanDistance(Position pos1,Position pos2) const;

    // returns euclidian distance between to vectors
    double calculateEuclidianDistance(Position pos1, Position pos2) const;
    
    // Gets which direction ghost should move in inorder to go on neighbour
    // requires ghost Posito and neighPos to be neighbouring cells
    Direction getNeighbourDirection(Position ghostPos, Position neighPos) const;

    Position getAmbusherTarget(Position pacmanPos, Direction pacmanDir) const;
    Position getFickleTarget(Position pacmanPos, Direction pacmanDir, Position chaserPos) const;

    bool stupidShouldFlee(Position stupidPos, Position pacmanPos) const; 


}; 

#endif