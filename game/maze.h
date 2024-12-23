#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <map>

// Define or include CellType
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


typedef std::vector<std::vector<Cell>> grid_t;

class Maze {
    private:
        // Direct Representation of game state. 
        grid_t grid;
    public:
        // Constructor with grid to be used for game state
        Maze(const std::vector<std::string>& layout);

        Cell getCell(int x, int y) const; 
        grid_t getGrid() const;
        void setCell(int x, int y, Cell type); 
        void printGrid();
};

#endif
