#pragma once

#include <vector>
#include <map>
#include "globals.hpp"

// Define or include CellType


typedef std::vector<std::vector<Cell>> grid_t;

class Maze {
    private:
        // Direct Representation of game state. 
        grid_t grid;
        // number of pellet and power pellets together
        unsigned int totalPelletCount;
    public:
        // Constructor with grid to be used for game state
        Maze();

        grid_t getGrid() const;
        int getGridWidth() const;
        int getGridHeight() const;

        unsigned int getTotalPelletCount() const;
        
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

