
#include <iostream>
#include "maze.h"
#include "agent.h"

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
    return grid[pos.y][pos.x];
}

grid_t Maze::getGrid() const {
    return grid;    
}

void Maze::setCell(Position pos, Cell type) {
    grid[pos.y][pos.x] = type;
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

