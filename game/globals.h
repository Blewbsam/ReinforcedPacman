
#ifndef GLOBALS
#define GLOBALS

#include <iostream>

enum Direction {UP,DOWN,LEFT,RIGHT,IDLE}; // Represents Direction in which agent is moving in

struct Position { // Represents Position where agent is located correspondig to gameState.
    int x;
    int y;
    Position(int x_val, int y_val) : x(x_val), y(y_val) {}
    bool operator==(const Position& other) const {
    return (x == other.x && y == other.y);
    }
};

enum Cell {
    PACMAN_CELL,
    GHOST_FICKLE,
    GHOST_CHASER,
    GHOST_AMBUSHER,
    GHOST_STUPID,
    WALL,
    EMPTY,
    PELLET,
    POWER_PELLET,
    DOOR
};

enum GhostType {
    CHASER,
    STUPID,
    FICKLE,
    AMBUSHER
};

enum GhostState {
    CHASE,
    SCATTER,
    EATEN,
    FRIGHTENED,
    SLEEP
};

// index of middle of the screen
// used for handling teleportation
#define MIDLE_ROW_INDEX 9

#define GRID_WIDTH 20
#define GRID_HEIGHT 22



#endif