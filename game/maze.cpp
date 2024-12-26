
#include <iostream>
#include "maze.h"
#include "agent.h"
#include <vector>

using std::cout;
using std::endl;



Maze::Maze(const std::vector<std::string>& layout){
    grid.resize(layout.size());
    for (unsigned int row = 0; row < layout.size(); ++row) {
        for (char cell: layout[row]) {
            switch (cell) {
                case 'X': grid[row].push_back(WALL); break;
                case '.': grid[row].push_back(PELLET); break;
                case 'O': grid[row].push_back(POWER_PELLET); break;
                case ' ': grid[row].push_back(EMPTY); break;
                case '=': grid[row].push_back(DOOR); break;
                default: cout << __LINE__ << ": got invalid cell" << cell << endl;
            }
        }
    }
}


Cell Maze::getCell(Position pos) const {
    if (pos.y >= 0 && pos.y < grid.size() && pos.x >= 0 && pos.x < grid[0].size()) {
        return grid[pos.y][pos.x];
    }
    throw std::out_of_range("Position out of bounds");
}

void Maze::setCell(Position pos, Cell type) {
    if (pos.y >= 0 && pos.y < grid.size() && pos.x >= 0 && pos.x < grid[0].size()) {
        grid[pos.y][pos.x] = type;
    } else {
        throw std::out_of_range("Position out of bounds");
    }
}

grid_t Maze::getGrid() const {
    return grid;    
}

int Maze::getGridWidth() const {
    return grid[0].size();
}

int Maze::getGridHeight() const {
    return grid.size();
}


void Maze::printGrid() {
    for (std::vector<Cell> row : grid) {
        for (Cell cell: row) {
             switch (cell) {
                case WALL: cout << "X"; break;
                case DOOR: cout << "="; break;
                case PELLET: cout << "."; break;
                case POWER_PELLET: cout << "O"; break;
                case EMPTY: cout << " "; break;
                default: std::cout << "Invalid Cell Type" << std::endl;
             }
        }
        cout << "\n";
    }
}

std::vector<Position> Maze::getValidEscapedNeighbours(Position pos) const {
    std::vector<Position> posVector;
    if (!this->validPos(pos)) throw std::runtime_error("Invalid Index");
    if (pos.y > 0 &&  this->grid[pos.y-1][pos.x] != WALL && this->grid[pos.y-1][pos.x] != DOOR) posVector.push_back(Position(pos.x,pos.y-1));
    if ((pos.x < this->getGridWidth() - 1) && this->grid[pos.y][pos.x+1] != WALL && this->grid[pos.y][pos.x+1] != DOOR) posVector.push_back(Position(pos.x+1,pos.y));
    if (pos.y < (this->getGridHeight() - 1) && this->grid[pos.y+1][pos.x] != WALL && this->grid[pos.y+1][pos.x] != DOOR) posVector.push_back(Position(pos.x,pos.y+1));
    if (pos.x > 0 && this->grid[pos.y][pos.x-1] != WALL && this->grid[pos.y][pos.x-1] != DOOR) posVector.push_back(Position(pos.x-1,pos.y));
    return posVector;
}


std::vector<Position> Maze::getValidNeighbours(Position pos) const {
    std::vector<Position> posVector;
    if (!this->validPos(pos)) throw std::runtime_error("Invalid Index");
    if (pos.y > 0 &&  this->grid[pos.y-1][pos.x] != WALL ) posVector.push_back(Position(pos.x,pos.y-1));
    if ((pos.x < this->getGridWidth() - 1) && this->grid[pos.y][pos.x+1] != WALL ) posVector.push_back(Position(pos.x+1,pos.y));
    if (pos.y < (this->getGridHeight() - 1) && this->grid[pos.y+1][pos.x] != WALL) posVector.push_back(Position(pos.x,pos.y+1));
    if (pos.x > 0 && this->grid[pos.y][pos.x-1] != WALL) posVector.push_back(Position(pos.x-1,pos.y));
    return posVector;
}



bool Maze::validPos(Position pos) const {
    return (pos.x >= 0 && pos.y >= 0 && pos.x < this->getGridWidth() && pos.y < this->getGridHeight());
}
