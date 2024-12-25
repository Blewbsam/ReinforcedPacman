
#include "ghostAI.h"
#include "game.h"


GhostAI::GhostAI(GameState * gameState) {
    this->gs = gameState;
}



void GhostAI::moveChaser(ChaserGhost * chaser, Pacman * pacman) {
    switch(chaser->getGhostState()) {
        case CHASE: moveChaseChaser(chaser,pacman); break;
        default: break;
    }
}




void GhostAI::moveChaseChaser(ChaserGhost * chaser, Pacman * pacman) {
    std::vector<Position> validPositions = this->gs->getValidPositions(chaser->getPos());
    double minDistance = 1000;
    int minIndex = 0;
    int index = 0;
    for (Position pos: validPositions) {
        double euclid = this->calculateEuclidianDistance(pos,pacman->getPos());
        if (euclid < minDistance) {
            minIndex = index;
            minDistance = euclid;
        }
        index += 1;
    }

    Direction moveDir = this->getNeighbourDirection(chaser,validPositions[minIndex]);
    chaser->setDir(moveDir);
}



// helpers
double GhostAI::calculateEuclidianDistance(Position pos1, Position pos2) {
    return std::sqrt(std::pow((pos1.x - pos2.x),2) + std::pow((pos1.y - pos2.y),2));
}

Direction GhostAI::getNeighbourDirection(Ghost * ghost, Position neighPos) {
    Position ghostPos = ghost->getPos();
    if (ghostPos.x == neighPos.x) {
        if (ghostPos.y > neighPos.y) return UP;
        return DOWN;
    } else {
        if (ghostPos.x > neighPos.x) return RIGHT;
        return LEFT;
    }
}
