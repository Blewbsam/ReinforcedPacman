
#include <iostream>
#include "maze.h"
#include "agent.h"
#include <vector>

using std::cout;
using std::endl;



// levelLayout = {
//     "XXXXXXXXXXXXXXXXXXXXXXXXX",
//     "X..........XX..........X",
//     "X.XXXX.XXX.XX.XXX.XXXX.X",
//     "XOXXXX.XXX.XX.XXX.XXXXOX",
//     "X.XXXX.XXX.XX.XXX.XXXX.X",
//     "X........................X",
//     "X.XXXX.XX.XXXXX.XX.XXXX.X",
//     "X.XXXX.XX.XXXXX.XX.XXXX.X",
//     "X......XX...XX...XX......X",
//     "XXXXXX.XXXXX XX XXXXX.XXXXX",
//     "XXXXX........G.....XXXXX",
//     "XXXXX.XX.XXXXXXXXX.XX.XXXXX",
//     "XXXXX....X......X....XXXXX",
//     "XXXXXXXX.XXXXXXXXX.XXXXXXXX",
//     "X........................X",
//     "X.XXXX.XXX.XXXXX.XXX.XXXX.X",
//     "XOXXXX.XXX.XXXXX.XXX.XXXXOX",
//     "X...XX.......P.......XX...X",
//     "XXX.XX.XX.XXXXX.XX.XX.XXX",
//     "XXX.XX.XX.XXXXX.XX.XX.XXX",
//     "X......XX...XX...XX......X",
//     "X.XXXXXXXXXX.XX.XXXXXXXXX.X",
//     "X.XXXXXXXXXX.XX.XXXXXXXXX.X",
//     "X........................X",
//     "XXXXXXXXXXXXXXXXXXXXXXXXX",
// };





Maze::Maze(const std::vector<std::string>& layout){
    grid.resize(layout.size());
    for (unsigned int row = 0; row < layout.size(); ++row) {
        for (char cell: layout[row]) {
            switch (cell) {
                case 'X': grid[row].push_back(WALL); break;
                case '.': grid[row].push_back(PELLET); break;
                // case 'O': grid[row].push_back(POWER_PELLET); break;
                case ' ': grid[row].push_back(EMPTY); break;
                // case 'P': grid[row].push_back(PACMAN_CELL); break;
                // case 'F': grid[row].push_back(GHOST_FICKLE); break;
                // case 'C': grid[row].push_back(GHOST_CHASER); break;
                // case 'A': grid[row].push_back(GHOST_AMBUSHER); break;
                // case 'S': grid[row].push_back(GHOST_STUPID); break; 
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
                case PACMAN_CELL: cout << "P"; break;
                case GHOST_FICKLE: cout << "F"; break;
                case GHOST_CHASER: cout << "C"; break;
                case GHOST_AMBUSHER: cout << "A"; break;
                case GHOST_STUPID: cout << "S"; break; 
             }
        }
        cout << "\n";
    }
}

std::vector<Position> Maze::getValidNeighbours(Position pos) const {
    std::vector<Position> posVector;
    std::cout << pos.x << std::endl;
    std::cout << pos.y << std::endl;
    if (!this->validPos(pos)) throw std::runtime_error("Invalid Index");
    if (pos.y > 0 &&  this->grid[pos.y-1][pos.x] != WALL) posVector.push_back(Position(pos.x,pos.y-1));
    if ((pos.x < this->getGridWidth() - 1) && this->grid[pos.y][pos.x+1] != WALL) posVector.push_back(Position(pos.x+1,pos.y));
    if (pos.y < (this->getGridHeight() - 1) && this->grid[pos.y+1][pos.x] != WALL) posVector.push_back(Position(pos.x,pos.y+1));
    if (pos.x > 0 && this->grid[pos.y][pos.x-1] != WALL) posVector.push_back(Position(pos.x-1,pos.y));
    return posVector;
}

bool Maze::validPos(Position pos) const {
    return (pos.x >= 0 && pos.y >= 0 && pos.x < this->getGridWidth() && pos.y < this->getGridHeight());
}
