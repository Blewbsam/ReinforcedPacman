#include <iostream>

#include "game.h"



std::vector<std::string>  levelLayout = {
		"XXXXXXXXXXXXXXXXXXX",
		"X..O.....X.....O..X",
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
		"X.O.............O.X",
		"XXXXXXXXXXXXXXXXXXX"
};

const std::unordered_map<GhostState, int> globalStateDurations = {
    {CHASE,20},
    {SCATTER,7},
    {FRIGHTENED,6}
};

GameState::GameState() : ghostAI(this){
    maze_p = new Maze(levelLayout);
    pacman_p = new Pacman();
    ghosts.fickle_p = new FickleGhost();
    ghosts.chaser_p = new ChaserGhost();
    ghosts.ambusher_p = new AmbusherGhost();
    ghosts.stupid_p = new StupidGhost();
    gameOver = false;
    this->setInitialGhostStates();
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



Direction GameState::getGhostDir(GhostType type) {
    switch (type) {
        case CHASER: return ghosts.chaser_p->getDir();
        case AMBUSHER: return ghosts.ambusher_p->getDir();
        case FICKLE: return ghosts.fickle_p->getDir();
        default: return ghosts.stupid_p->getDir();
    }
}
GhostState GameState::getGhostState(GhostType type) {
    switch (type) {
        case CHASER: return ghosts.chaser_p->getGhostState();
        case AMBUSHER: return ghosts.ambusher_p->getGhostState();
        case FICKLE: return ghosts.fickle_p->getGhostState();
        default: return ghosts.stupid_p->getGhostState();
    }
}


grid_t GameState::getGrid() const {return maze_p->getGrid();}
int GameState::getGridWidth()const {return maze_p->getGridWidth();}
int GameState::getGridHeight() const {return maze_p->getGridHeight();}

GhostState GameState::getGlobalState() const {return this->globalState;}


void GameState::setInitialGhostStates() {
    this->updateGhostState(CHASER,ESCAPE);
    this->updateGhostState(AMBUSHER,ESCAPE);
    this->updateGhostState(FICKLE,ESCAPE);
    this->updateGhostState(STUPID,ESCAPE);
}

void GameState::generateGhostMove(GhostType type){
    if (this->hasTimeElapsed()) this->switchToNextState();
    switch (type) {
    case CHASER: ghostAI.moveChaser(this->ghosts.chaser_p,this->pacman_p); break;
    case AMBUSHER: ghostAI.moveAmbusher(this->ghosts.ambusher_p,this->pacman_p); break;
    case FICKLE: ghostAI.moveFickle(this->ghosts.fickle_p, this->pacman_p, this->ghosts.chaser_p->getPos());
    case STUPID: ghostAI.moveStupid(this->ghosts.stupid_p,this->pacman_p);
    default:
        break;
    }
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
    this->handlePowerPelletCollision();
    this->handleGhostCollisions();
}
 
void GameState::handlePelletCollision() {
    Position pacPos = this->pacman_p->getPos();
    if (maze_p->getCell(pacPos) == PELLET) {
        maze_p->setCell(pacPos,EMPTY);
        score += 10;
    }
}

void GameState::handlePowerPelletCollision() {
    Position pacPos = this->pacman_p->getPos();
    if (maze_p->getCell(pacPos) == POWER_PELLET) {
        maze_p->setCell(pacPos,EMPTY);
        score += 20;
        this->updateGlobalState(this->globalState,FRIGHTENED);
    }
}


void GameState::handleGhostCollisions() {
    Position pacmanPosition = this->pacman_p->getPos();
    if (this->globalState != FRIGHTENED){
        if (pacmanPosition == this->ghosts.chaser_p->getPos()) { this->gameOver = true;}
        else if (pacmanPosition == this->ghosts.ambusher_p->getPos()) { this->gameOver = true;}
        else if (pacmanPosition == this->ghosts.fickle_p->getPos()) { this->gameOver = true;}
        else if (pacmanPosition == this->ghosts.stupid_p->getPos()) { this->gameOver = true;}
    } else {
        if (pacmanPosition == this->ghosts.chaser_p->getPos()) {this->ghosts.chaser_p->setGhostState(EATEN);}
        else if (pacmanPosition == this->ghosts.ambusher_p->getPos()) {this->ghosts.ambusher_p->setGhostState(EATEN);}
        else if (pacmanPosition == this->ghosts.fickle_p->getPos()) {this->ghosts.fickle_p->setGhostState(EATEN);}
        else if (pacmanPosition == this->ghosts.stupid_p->getPos()) {this->ghosts.stupid_p->setGhostState(EATEN);}
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

void GameState::updateGlobalState(GhostState prevState, GhostState newState) {
    this->globalState =  newState;
    if (newState == FRIGHTENED) std::cout << "Making frightened" << std::endl;
    if (this->ghosts.chaser_p->getGhostState() == prevState) this->ghosts.chaser_p->setGhostState(newState);
    if (this->ghosts.ambusher_p->getGhostState() == prevState) this->ghosts.ambusher_p->setGhostState(newState);
    if (this->ghosts.fickle_p->getGhostState() == prevState) this->ghosts.fickle_p->setGhostState(newState);
    if (this->ghosts.stupid_p->getGhostState() == prevState) this->ghosts.stupid_p->setGhostState(newState);
    this->startStateTimer();
}

void GameState::startStateTimer() {
    this->stateStartTime = std::chrono::steady_clock::now(); 
}

bool GameState::hasTimeElapsed() const {
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<int> elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(now - stateStartTime);
    return elapsedTime.count() >= globalStateDurations.at(this->globalState);  
}


void GameState::switchToNextState() {
    std::cout << "Switching States" << std::endl;
    if (this->globalState == CHASE) {
        this->updateGlobalState(CHASE,SCATTER);
    } else if (this->globalState == SCATTER) {
        this->updateGlobalState(SCATTER,CHASE);
    } else {
        this->updateGlobalState(FRIGHTENED,CHASE);
    }
}





bool GameState::isGameOver() const {return this->gameOver;}

