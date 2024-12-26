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
        
        // returns all neighbors that are OPEN
        std::vector<Position> getValidNeighbours(Position pos) const;
        std::vector<Position> getValidEscapedNeighbours(Position pos) const;
        Cell getCell(Position pos) const; 
        void setCell(Position pos, Cell type); 
        void printGrid();
        bool validPos(Position pos) const;

};

#endif
