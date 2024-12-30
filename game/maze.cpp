
#include <iostream>
#include "maze.hpp"
#include "agent.hpp"
#include <vector>

using std::cout;
using std::endl;


const std::vector<std::string>  layout = {
		" XXXXXXXXXXXXXXXXXXX ",
		" X........X........X ",
		" XOXX.XXX.X.XXX.XXOX ",
		" X.................X ",
		" X.XX.X.XXXXX.X.XX.X ",
		" X....X...X...X....X ",
		" XXXX.XXX X XXX.XXXX ",
		"    X.X       X.X    ",
		"XXXXX.X XX=XX X.XXXXX",
		"     .  X   X  .     ",
		"XXXXX.X XXXXX X.XXXXX",
		"    X.X       X.X    ",
		" XXXX.X XXXXX X.XXXX ",
		" X........X........X ",
		" X.XX.XXX.X.XXX.XX.X ",
		" XO.X..... .....X.OX ",
		" XX.X.X.XXXXX.X.X.XX ",
		" X....X...X...X....X ",
		" X.XXXXXX.X.XXXXXX.X ",
		" X.................X ",
		" XXXXXXXXXXXXXXXXXXX "
};

Maze::Maze(){
    grid.resize(layout.size());
    for (unsigned int row = 0; row < layout.size(); ++row) {
        for (char cell: layout[row]) {
            switch (cell) {
                case 'X': grid[row].push_back(WALL); break;
                case '.': grid[row].push_back(PELLET); this->totalPelletCount++; break;
                case 'O': grid[row].push_back(POWER_PELLET);  this->totalPelletCount++; break;
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

unsigned int Maze::getTotalPelletCount() const {
    return this->totalPelletCount;
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
