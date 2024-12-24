#include <iostream>

#include "game.h"

using std::cout;
using std::endl;

GameState::GameState(const std::vector<std::string>& layout) {

    maze_p = new Maze(layout);
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
Position GameState::getFicklePos() {return ghosts.fickle_p->getPos();}
Position GameState::getAmbusherPos() {return ghosts.ambusher_p->getPos();}
Position GameState::getChaserPos() {return ghosts.chaser_p->getPos();}
Position GameState::getStupidPos() {return ghosts.stupid_p->getPos();}
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
    
    Cell cell = maze_p->getCell(pos.x, pos.y);
    return cell != WALL;
}
