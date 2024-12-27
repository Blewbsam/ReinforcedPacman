#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <map>
#include "globals.h"

// Define or include CellType


typedef std::vector<std::vector<Cell>> grid_t;

class Maze {
    private:
        // Direct Representation of game state. 
        grid_t grid;
    public:
        // Constructor with grid to be used for game state
        Maze(const std::vector<std::string>& layout);

        grid_t getGrid() const;
        int getGridWidth() const;
        int getGridHeight() const;
        
        // returns all neighboring cells that are not WALL
        std::vector<Position> getValidNeighbours(Position pos) const;
        // returns all neighbopring cells that are not WALL and DOOR
        std::vector<Position> getValidEscapedNeighbours(Position pos) const;
        
        Cell getCell(Position pos) const; 
        void setCell(Position pos, Cell type); 
        // terminal output of grid in current state.
        void printGrid();
        // returns true if pos is in grid
        bool validPos(Position pos) const;

};

#endif
