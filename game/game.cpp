#include <iostream>

#include "game.h"



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




Position GameState::getPacmanPos() const {return pacman_p->getPos();}
Direction GameState::getPacmanDir() const {return pacman_p->getDir();};

Position GameState::getFicklePos() const {return ghosts.fickle_p->getPos();}
Direction GameState::getFickleDir() const {return ghosts.fickle_p->getDir();}
Position GameState::getAmbusherPos() const {return ghosts.ambusher_p->getPos();}
Direction GameState::getAmbusherDir() const {return ghosts.ambusher_p->getDir();};
Position GameState::getChaserPos() const {return ghosts.chaser_p->getPos();}
Direction GameState::getChaserDir() const {return ghosts.chaser_p->getDir();}
Position GameState::getStupidPos() const {return ghosts.stupid_p->getPos();}
Direction GameState::getStupidDir() const {return ghosts.stupid_p->getDir();}

grid_t GameState::getGrid() const {return maze_p->getGrid();}
int GameState::getGridWidth()const {return maze_p->getGridWidth();}
int GameState::getGridHeight() const {return maze_p->getGridHeight();}


void GameState::generateGhostMoves(){
    ghostAI.moveChaser(this->ghosts.chaser_p,this->pacman_p);
    ghostAI.moveAmbusher(this->ghosts.ambusher_p,this->pacman_p);
    ghostAI.moveStupid(this->ghosts.stupid_p,this->pacman_p);
    ghostAI.moveFickle(this->ghosts.fickle_p, this->pacman_p, this->ghosts.chaser_p->getPos());
}



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

void GameState::updateGhostPos(Position pos, GhostType type) {
    switch (type) {
        case CHASER: this->ghosts.chaser_p->setPos(pos); break;
        case AMBUSHER: this->ghosts.ambusher_p->setPos(pos); break;
        case STUPID: this->ghosts.stupid_p->setPos(pos); break;
        default: this->ghosts.fickle_p->setPos(pos); break;
    }
}

void GameState::updateGhostState(GhostType type, GhostState state) {
    switch (type) {
        case CHASER: this->ghosts.chaser_p->setGhostState(state); break;
        case AMBUSHER: this->ghosts.ambusher_p->setGhostState(state); break;
        case STUPID: this->ghosts.stupid_p->setGhostState(state); break;
        default: this->ghosts.fickle_p->setGhostState(state); break;
    }
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


// takes position and way agent is facing and returns Position behind agent
Position getReversePosition(Position pos, Direction dir) {
    switch (dir) {
        case UP: pos.y += 1; break;
        case DOWN: pos.y -= 1; break;
        case RIGHT: pos.x -= 1; break;
        case LEFT: pos.x += 1; break;
        default: break;
    }
    return pos;
}


std::vector<Position> GameState::getValidPositions(Position ghostPos, Direction ghostDir, bool hasEscaped) const {

    // get Empty neighbouring cells
    std::vector<Position> validNeighbours = this->getValidNeighbours(ghostPos, hasEscaped);
    // remove the one behind the ghost
    Position pos = getReversePosition(ghostPos, ghostDir);
    auto index = std::find(validNeighbours.begin(), validNeighbours.end(), pos);
    if (index != validNeighbours.end() && validNeighbours.size() > 1) {
        validNeighbours.erase(index); 
    }
    return validNeighbours;
}


std::vector<Position> GameState::getValidNeighbours(Position pos, bool hasEscaped) const {
    if (hasEscaped) return this->maze_p->getValidEscapedNeighbours(pos);
    return this->maze_p->getValidNeighbours(pos);
}
