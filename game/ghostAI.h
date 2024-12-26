
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

    // sets ghost to correct direction in persuit of targetPos
    void moveToTarget(Ghost * ghost,Position targetPos);

    void moveChaseChaser(ChaserGhost * chaser, Pacman * pacman);
    void moveChaseAmbusher(AmbusherGhost * ambusher, Pacman * pacman);
    void moveChaseFickle(FickleGhost * fickle, Pacman * pacman, Position chaserPos);
    void moveChaseStupid(StupidGhost * stupid, Pacman * pacman);

    // ghostMoves to its specified scatterCorner
    void moveScatterGhost(Ghost * ghost);

     // moves ghost back to home tile, 
    // sets ghost mode to ESCAPE when ghost is home.
    void moveEatenGhost(Ghost * ghost);


    // Forces ghost to leave home
    // sets ghost mode to CHASE when ghost is out.
    void moveEscapeGhost(Ghost * ghost);

    // ghost takes random direction at each corner
    void moveFrightenedGhost(Ghost * ghost);

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