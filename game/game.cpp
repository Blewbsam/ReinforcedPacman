#include <iostream>

#include "game.h"

using std::cout;
using std::endl;

std::vector<std::string>  levelLayout = {
		"XXXXXXXXXXXXXXXXXXX",
		"X........X........X",
		"XXXX.XXX.X.XXX.XXXX",
		"X.................X",
		"X.XX.X.XXXXX.X.XX.X",
		"X....X...X...X....X",
		"XXXX.XXX.X.XXX.XXXX",
		"   X.X.......X.X   ",
		"XXXX.X XX=XX X.XXXX",
		".......X   X.......",
		"XXXX.X XXXXX X.XXXX",
		"   X.X.......X.X   ",
		"XXXX.X.XXXXX.X.XXXX",
		"X........X........X",
		"X.XX.XXX.X.XXX.XX.X",
		"X..X...........X..X",
		"XX.X.X.XXXXX.X.X.XX",
		"X....X...X...X....X",
		"X.XXXXXX.X.XXXXXX.X",
		"X.................X",
		"XXXXXXXXXXXXXXXXXXX"
};

GameState::GameState() : ghostAI(this){
    maze_p = new Maze(levelLayout);
    pacman_p = new Pacman(getAgentPositionBrute(PACMAN_CELL,maze_p->getGrid()));
    ghosts.fickle_p = new FickleGhost(getAgentPositionBrute(GHOST_FICKLE,maze_p->getGrid()));
    ghosts.chaser_p = new ChaserGhost(getAgentPositionBrute(GHOST_CHASER,maze_p->getGrid()));
    ghosts.ambusher_p = new AmbusherGhost(getAgentPositionBrute(GHOST_AMBUSHER,maze_p->getGrid()));
    ghosts.stupid_p = new StupidGhost(getAgentPositionBrute(GHOST_STUPID,maze_p->getGrid()));
    gameOver = false;
}


GameState::~GameState() {
    delete maze_p;
    delete pacman_p;
    delete ghosts.fickle_p;
    delete ghosts.chaser_p;
    delete ghosts.ambusher_p;
    delete ghosts.stupid_p;
}




Position GameState::getPacmanPos() {return pacman_p->getPos();}
Direction GameState::getPacmanDir() {return pacman_p->getDir();};

Position GameState::getFicklePos() {return ghosts.fickle_p->getPos();}
Direction GameState::getFickleDir() {return ghosts.fickle_p->getDir();}
Position GameState::getAmbusherPos() {return ghosts.ambusher_p->getPos();}
Direction GameState::getAmbusherDir() {return ghosts.ambusher_p->getDir();};
Position GameState::getChaserPos() {return ghosts.chaser_p->getPos();}
Direction GameState::getChaserDir() {return ghosts.chaser_p->getDir();}
Position GameState::getStupidPos() {return ghosts.stupid_p->getPos();}
Direction GameState::getStupidDir() {return ghosts.stupid_p->getDir();}
grid_t GameState::getGrid() {return maze_p->getGrid();}


Position GameState::getAgentPositionBrute(Cell agentCell,const std::vector<std::vector<Cell>> grid) {
    Position pos = {-1,-1};
    for (unsigned int y = 0; y < grid.size(); y++) {
        for (unsigned int x = 0; x < grid[y].size(); x++) {
            if (grid[y][x] == agentCell) {
                pos.x = (int) x;
                pos.y = (int) y;
                goto done;
            }
        }
    }
    done:

    if (pos.x == -1 || pos.y == -1) std::cout << __LINE__ << ": specified cell was not found on layout" << std::endl;
    return pos;
}




void GameState::updatePacmanPos(Position pos) {
    this->pacman_p->setPos(pos);
}


bool GameState::validPacmanMove(Direction dir) const {

    Position pos = pacman_p->getPos();

    switch (dir) {
        case UP:
            pos.y -= 1;
            break;
        case DOWN:
            pos.y += 1;
            break;
        case RIGHT:
            pos.x += 1;
            break;
        case LEFT:
            pos.x -= 1;
            break;
        default:
            break;
    }    

    if (pos.x < 0 || pos.x >= maze_p->getGridWidth()) return false;
    if (pos.y < 0 || pos.y >= maze_p->getGridHeight()) return false;
    
    Cell cell = maze_p->getCell(pos);
    return cell != WALL;
}

void GameState::handleCollisions() {
    this->handlePelletCollision();
    // handle ghost collisions here TODO:
}
 
void GameState::handlePelletCollision() {
    Position pacPos = this->pacman_p->getPos();
    if (maze_p->getCell(pacPos) == PELLET) {
        maze_p->setCell(pacPos,EMPTY);
        score += 10;
    }
}


bool GameState::jumpAvail(Position pos) {   
    return (pos.y == MIDLE_ROW_INDEX && pos.x == 0) || (pos.y == MIDLE_ROW_INDEX && pos.x == maze_p->getGridWidth() - 1);
}
Position GameState::jumpPortal(Position pos) {
    if (pos.y == MIDLE_ROW_INDEX && pos.x == 0) {
        pos.x = maze_p->getGridWidth() - 2;
    } else if (pos.y == MIDLE_ROW_INDEX && pos.x == maze_p->getGridWidth() - 1) {
        pos.x = 2;
    }
    return pos;
}

void GameState::changePacmanDir(Direction dir) {
    this->pacman_p->setDir(dir);
}

std::vector<Position> GameState::getValidPositions(Position pos) {
    return this->maze_p->getValidPositions(pos);
}
