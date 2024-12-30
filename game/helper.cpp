
#include <iostream>
#include "helpers.hpp"

void printGhostState(Ghost * ghost) {
    switch (ghost->getGhostState()) {
        case CHASE:
            std::cout << "Ghost is in CHASE state." << std::endl;
            break;
        case SCATTER:
            std::cout << "Ghost is in SCATTER state." << std::endl;
            break;
        case EATEN:
            std::cout << "Ghost is in EATEN state." << std::endl;
            break;
        case FRIGHTENED:
            std::cout << "Ghost is in FRIGHTENED state." << std::endl;
            break;
        case TRANSITION:
            std::cout << "Ghost is in TRANSITION state." << std::endl;
            break;
        case ESCAPE:
            std::cout << "Ghost is in ESCAPE state." << std::endl;
            break;
        case SLEEP:
            std::cout << "Ghost is in SLEEP state." << std::endl;
            break;
        default:
            std::cout << "Unknown ghost state." << std::endl;
            break;
    }
}


void printGhostDir(Ghost * ghost) {
    switch (ghost->getDir()){
    case UP: std::cout << "Direction is UP" << std::endl; break;
    case DOWN: std::cout << "Direction is DOWN" << std::endl; break;
    case RIGHT: std::cout << "Direct is RIGHT" << std::endl; break;
    case LEFT: std::cout << "Directon is LEFT" << std::endl; break; 
    default: std::cout << "Direction is IDLE" << std::endl; break;  
    }
}

void printPos(Position pos) {
    std::cout << "(" << pos.x << "," << pos.y << ")" << std::endl;
}   