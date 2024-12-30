
#include <iostream>
#include <random>
#include <vector>
#include "ghostAI.hpp"
#include "game.hpp"
#include "helpers.hpp"



GhostAI::GhostAI(GameState * gameState) {
    this->gs = gameState;
}
void GhostAI::moveChaser(ChaserGhost * chaser, Pacman * pacman) {
    switch(chaser->getGhostState()) {
        case CHASE: moveChaseChaser(chaser,pacman); break;
        case SCATTER: moveScatterGhost(chaser); break;
        case ESCAPE: moveEscapeGhost(chaser); break;
        case EATEN: moveEatenGhost(chaser); break;
        case TRANSITION: // should fall through to FRIGHTENED behaviour
        case FRIGHTENED: moveFrightenedGhost(chaser); break;
        default: break;
    }
}

void GhostAI::moveAmbusher(AmbusherGhost * ambusher, Pacman * pacman) {
    switch (ambusher->getGhostState()) {
        case CHASE: moveChaseAmbusher(ambusher,pacman); break;
        case SCATTER: moveScatterGhost(ambusher);break;
        case ESCAPE: moveEscapeGhost(ambusher); break;
        case EATEN: moveEatenGhost(ambusher); break;
        case TRANSITION:
        case FRIGHTENED: moveFrightenedGhost(ambusher); break;
        default: break;
    }
}

void GhostAI::moveStupid(StupidGhost * stupid, Pacman * pacman) {
    printGhostState(stupid);
    printGhostDir(stupid);
    printPos(stupid->getPos());
    switch (stupid->getGhostState()) {
        case CHASE: moveChaseStupid(stupid,pacman); break;
        case SCATTER: moveScatterGhost(stupid); break;
        case ESCAPE: moveEscapeGhost(stupid); break;
        case EATEN: moveEatenGhost(stupid); break;
        case TRANSITION:
        case FRIGHTENED: moveFrightenedGhost(stupid); break;
        default: break; 
    }
}

void GhostAI::moveFickle(FickleGhost * fickle, Pacman * pacman, Position chaserPos) {
    switch (fickle->getGhostState()) {
        case CHASE: moveChaseFickle(fickle,pacman,chaserPos); break;
        case SCATTER: moveScatterGhost(fickle); break;
        case ESCAPE: moveEscapeGhost(fickle); break;
        case EATEN: moveEatenGhost(fickle); break;
        case TRANSITION:  
        case FRIGHTENED: moveFrightenedGhost(fickle); break;    
        default: break; 
    }
}

void GhostAI::moveToTarget(Ghost * ghost, Position targetPos, bool hasEscaped) {
    std::vector<Position> validPositions = this->gs->getValidPositions(ghost->getPos(), ghost->getDir(),hasEscaped); 
    Position validNextPos = this->getMinEuclidianPosition(validPositions,targetPos);
    Direction moveDir = this->getNeighbourDirection(ghost->getPos(), validNextPos);
    ghost->setDir(moveDir);
}

void GhostAI::moveChaseChaser(ChaserGhost * chaser, Pacman * pacman) {
    this->moveToTarget(chaser,pacman->getPos(),true);
}

void GhostAI::moveChaseAmbusher(AmbusherGhost * ambusher, Pacman * pacman) {
    // 
    Position targetPos = this->getAmbusherTarget(pacman->getPos(),pacman->getDir());
    this->moveToTarget(ambusher,targetPos,true);
}

void GhostAI::moveChaseStupid(StupidGhost * stupid, Pacman * pacman) {
    Position targetPos;
    if (this->stupidShouldFlee(stupid->getPos(), pacman->getPos())) {
        targetPos = stupid->getScatterCorner();
    } else {
        targetPos = pacman->getPos();
    }
    this->moveToTarget(stupid,targetPos,true);
    printGhostDir(stupid);

}

void GhostAI::moveChaseFickle(FickleGhost * fickle, Pacman * pacman, Position chaserPos) {
    Position targetPos = this->getFickleTarget(pacman->getPos(),pacman->getDir(), chaserPos);
    this->moveToTarget(fickle,targetPos,true);
}

void GhostAI::moveScatterGhost(Ghost * ghost) {
    Position targetPos = ghost->getScatterCorner();
    this->moveToTarget(ghost,targetPos,true);
}

const Position HomePos = {9,9};
void GhostAI::moveEatenGhost(Ghost * ghost) {
    if (ghost->getGhostState() != EATEN) std::runtime_error("Ghost is not in EATEN state.");
    this->moveToTarget(ghost,HomePos,false);
    if (ghost->getPos() == HomePos) ghost->setGhostState(ESCAPE);
}

const Position EscapePos = {10,7};
void GhostAI::moveEscapeGhost(Ghost * ghost) {
    if (ghost->getGhostState() != ESCAPE) std::runtime_error("Ghost is not in ESCAPE state.");
    this->moveToTarget(ghost,EscapePos,false);
    if (ghost->getPos() == EscapePos) {
        if (this->gs->getGlobalState() == FRIGHTENED || this->gs->getGlobalState() == TRANSITION) { 
            // when game is in FRIGHTENED state, ghost should CHASE.
            ghost->setGhostState(CHASE);
        } else {
            ghost->setGhostState(this->gs->getGlobalState());
        }
    }
}
void GhostAI::moveFrightenedGhost(Ghost * ghost) {
    if (!this->ghostIsScared(ghost)) std::runtime_error("Ghost is not in FRIGHTENED state.");
    std::vector<Position> validPositions = this->gs->getValidPositions(ghost->getPos(), ghost->getDir(), true); 
    if (validPositions.empty()) {
        throw std::runtime_error("No valid positions to pick from!");
    }
    // Create a random device and generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Define the range for the random index
    std::uniform_int_distribution<> dis(0, validPositions.size() - 1);
    // Pick a random index
    int randomIndex = dis(gen);
    Position validNextPos = validPositions[randomIndex];
    Direction moveDir = this->getNeighbourDirection(ghost->getPos(), validNextPos);
    ghost->setDir(moveDir);
}


// helpers
Position getNTilesAhead(Position pacmanPos, Direction pacmanDir, int n) {
        switch (pacmanDir) {
        case UP: pacmanPos.y -= n; break;
        case DOWN: pacmanPos.y += n; break; 
        case RIGHT: pacmanPos.x += n; break;
        default: pacmanPos.x -= n; break;
    }
    return pacmanPos;
}


// return position which is four tiles ahead of pacman to be target.
Position GhostAI::getAmbusherTarget(Position pacmanPos, Direction pacmanDir) const {
    return getNTilesAhead(pacmanPos,pacmanDir,4);
}


Position GhostAI::getFickleTarget(Position pacmanPos, Direction pacmanDir, Position chaserPos) const {
    Position targetTile = getNTilesAhead(pacmanPos, pacmanDir,2); 
    Position vector = {chaserPos.x - targetTile.x, chaserPos.y - targetTile.y};

    // Calculate Fickle's target
    Position fickleTarget = {targetTile.x + 2 * vector.x, targetTile.y + 2 * vector.y};

    // Clamp the target to fit within the grid boundaries
    fickleTarget.x = std::max(0, std::min(fickleTarget.x, this->gs->getGridWidth() - 1));
    fickleTarget.y = std::max(0, std::min(fickleTarget.y, this->gs->getGridHeight() - 1));

    return fickleTarget;

}

Position GhostAI::getMinEuclidianPosition(std::vector<Position>& possiblePositions,Position srcPos) const {
    double minDistance = 1000;
    int minIndex = -1;
    int index = 0;
    for (Position pos: possiblePositions) {
        double euclid = this->calculateEuclidianDistance(pos,srcPos);
        if (euclid < minDistance) {
            minIndex = index;
            minDistance = euclid;
        }
        index += 1;
    }
    if (minIndex == -1) throw std::runtime_error("chaser must have a position to move to.");
    return possiblePositions[minIndex];
}

int GhostAI::calculateManhattanDistance(Position pos1, Position pos2) const {
    return abs(pos1.x - pos2.x) + abs(pos1.y - pos2.y);
}

double GhostAI::calculateEuclidianDistance(Position pos1, Position pos2) const {
    return std::sqrt(std::pow((pos1.x - pos2.x),2) + std::pow((pos1.y - pos2.y),2));
}

Direction GhostAI::getNeighbourDirection(Position ghostPos, Position neighPos) const {
    if (ghostPos.x != neighPos.x && ghostPos.y != neighPos.y) std::runtime_error("Invalid Neigbour recieved.");
    if (ghostPos.x == neighPos.x) {
        if (ghostPos.y > neighPos.y) return UP;
        return DOWN;
    } else {
        if (ghostPos.x > neighPos.x) return LEFT;
        return RIGHT;
    }
}

bool GhostAI::stupidShouldFlee(Position stupidPos, Position pacmanPos) const {
    return this->calculateManhattanDistance(stupidPos,pacmanPos) < 8;
}

bool GhostAI::ghostIsScared(Ghost * ghost) {
    return (ghost->getGhostState() == FRIGHTENED || ghost->getGhostState() == TRANSITION);
}