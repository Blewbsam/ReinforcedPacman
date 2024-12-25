
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

    // get AvailablePositions ghost can move to
    std::vector<Position> validPositions = this->gs->getValidPositions(chaser->getPos(), chaser->getDir()); 
    // calculate which has minimum Euclidian distance to pacman
    double minDistance = 1000;
    int minIndex = -1;
    int index = 0;
    Position chaserPos = chaser->getPos();
    Position pacmanPos = pacman->getPos();
    for (Position pos: validPositions) {
        std::cout << pos.x << "," << pos.y << std::endl;
        double euclid = this->calculateEuclidianDistance(pos,pacman->getPos());
        if (euclid < minDistance) {
            minIndex = index;
            minDistance = euclid;
        }
        index += 1;
    }
    if (minIndex == -1) throw std::runtime_error("chaser must have a position to move to.");

    Position validPosition = validPositions[minIndex];

    Direction moveDir = this->getNeighbourDirection(chaser->getPos(),validPosition);
    // switch (moveDir){
    //     case UP: std::cout << "UP" << std::endl; break;
    //     case DOWN: std::cout <<"DOWN" << std::endl; break;
    //     case RIGHT: std::cout << "RIGHT" << std::endl; break;
    //     case LEFT: std::cout << "LEFT" << std::endl; break;
    //     default: std::cout << "IDLE" << std::endl; break;
    // }

    chaser->setDir(moveDir);
}
// helpers
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
