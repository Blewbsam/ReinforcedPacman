

#pragma once

#include "globals.hpp"
#include "ghost.hpp"
#include "pacman.hpp"

class GameState; // forward decleration

// GhostAI determines movement of ghosts on grid
class GhostAI {

    GameState * gs;


public:
    GhostAI(GameState * gameState);
    // set the Direction of corresponding Ghost appropriately depending on their State and Position
    void moveChaser(ChaserGhost * chaser, Pacman * pacman);
    void moveAmbusher(AmbusherGhost * ambusher, Pacman * pacman);
    void moveFickle(FickleGhost * fickle, Pacman * pacman, Position chaserPos);
    void moveStupid(StupidGhost * stupid, Pacman * pacman);
private:
    // determine how ghosts should move.

    // sets ghost to correct direction in persuit of targetPos
    void moveToTarget(Ghost * ghost,Position targetPos,bool hasEscaped);

    // set the direction of corresponding Ghost given that they are in state CHASE
    // REQUIRES: Ghost to be in state CHASE
    void moveChaseChaser(ChaserGhost * chaser, Pacman * pacman);
    void moveChaseAmbusher(AmbusherGhost * ambusher, Pacman * pacman);
    void moveChaseFickle(FickleGhost * fickle, Pacman * pacman, Position chaserPos);
    void moveChaseStupid(StupidGhost * stupid, Pacman * pacman);

    // sets ghost Direction towards corresponding scatter corner
    void moveScatterGhost(Ghost * ghost);

    // moves ghost back to home tile, 
    // sets ghost mode to ESCAPE when ghost is home.
    // REQUIRES: ghost should be in EAten state
    void moveEatenGhost(Ghost * ghost);

    // Forces ghost to leave home
    // sets ghost mode to CHASE when ghost is out.
    void moveEscapeGhost(Ghost * ghost);

    // ghost takes random direction at each corner
    void moveFrightenedGhost(Ghost * ghost);

    // returns where ambusher should target
    // AmbusherTarget is 4 tiles ahead of where pacman is facing
    Position getAmbusherTarget(Position pacmanPos, Direction pacmanDir) const;

    // returns where fickle should target
    Position getFickleTarget(Position pacmanPos, Direction pacmanDir, Position chaserPos) const;

    bool stupidShouldFlee(Position stupidPos, Position pacmanPos) const; 

    // helpers:
    // gets position which is of least euclidian distance from srcPos
    Position getMinEuclidianPosition(std::vector<Position>& possiblePositions, Position srcPos) const;

    // returns euclidian distance between to Positions
    double calculateEuclidianDistance(Position pos1, Position pos2) const;

    // returns manhatan distance between to Positions
    int calculateManhattanDistance(Position pos1,Position pos2) const;
    
    // Gets which direction ghost should move in inorder to go on neighbour
    // requires ghost Position and neighPos to be neighbouring cells
    Direction getNeighbourDirection(Position ghostPos, Position neighPos) const;


    // returns true if ghost is in scared mode.
    bool ghostIsScared(Ghost * ghost);



}; 
