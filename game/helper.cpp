
#include <iostream>
#include "helpers.h"

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
