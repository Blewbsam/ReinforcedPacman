
#include <iostream>
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

    std::vector<Position> validPositions = this->gs->getValidNeighbours(chaser->getPos()); // TODO: should not be ampty
    std::cout << "SIZE: " << validPositions.size() << std::endl;
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

    Position validPosition = validPositions[minIndex];

    std::cout << "Done" << std::endl;
    Direction moveDir = this->getNeighbourDirection(chaser->getPos(),validPosition);
    std::cout << "Mid";
    chaser->setDir(moveDir);
    std::cout << "Dir Set" <<std::endl;
}



// helpers
double GhostAI::calculateEuclidianDistance(Position pos1, Position pos2) const {
    return std::sqrt(std::pow((pos1.x - pos2.x),2) + std::pow((pos1.y - pos2.y),2));
}

Direction GhostAI::getNeighbourDirection(Position ghostPos, Position neighPos) const {
    if (ghostPos.x != neighPos.x && ghostPos.y != neighPos.y) std::cout << "Invalid Neighbor" << std::endl;

    if (ghostPos.x == neighPos.x) {
        if (ghostPos.y > neighPos.y) return UP;
        return DOWN;
    } else {
        if (ghostPos.x > neighPos.x) return RIGHT;
        return LEFT;
    }
}
