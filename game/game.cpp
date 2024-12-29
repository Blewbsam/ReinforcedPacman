#include <iostream>

#include "game.h"






GameState::GameState() : ghostAI(this){
    maze_p = new Maze();
    pacman_p = new Pacman();
    ghosts.fickle_p = new FickleGhost();
    ghosts.chaser_p = new ChaserGhost();
    ghosts.ambusher_p = new AmbusherGhost();
    ghosts.stupid_p = new StupidGhost();
    ghostArray[0] = ghosts.fickle_p;
    ghostArray[1] = ghosts.chaser_p;
    ghostArray[2] = ghosts.ambusher_p;
    ghostArray[3] = ghosts.stupid_p;
    score = 0;
    gameOver = false;
    setInitialGhostStates();
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
    this->updateGhostState(AMBUSHER,SLEEP);
    this->updateGhostState(FICKLE,SLEEP);
    this->updateGhostState(STUPID,SLEEP);
}

void GameState::generateGhostMove(GhostType type){
    if (this->hasTimeElapsed()) this->switchToNextState();
    switch (type) {
    case CHASER: ghostAI.moveChaser(this->ghosts.chaser_p,this->pacman_p); break;
    case AMBUSHER: ghostAI.moveAmbusher(this->ghosts.ambusher_p,this->pacman_p); break;
    case FICKLE: ghostAI.moveFickle(this->ghosts.fickle_p, this->pacman_p, this->ghosts.chaser_p->getPos());break;
    case STUPID: ghostAI.moveStupid(this->ghosts.stupid_p,this->pacman_p);break;    
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
    this->checkPelletStatus();
    this->handleGhostCollisions();
}
 
void GameState::handlePelletCollision() {
    Position pacPos = this->pacman_p->getPos();
    if (maze_p->getCell(pacPos) == PELLET) {
        maze_p->setCell(pacPos,EMPTY);
        score += 10;
        eatenPelletCount += 1;
        this->freeGhostHouseGhosts();
    }
}

void GameState::handlePowerPelletCollision() {
    Position pacPos = this->pacman_p->getPos();
    if (maze_p->getCell(pacPos) == POWER_PELLET) {
        maze_p->setCell(pacPos,EMPTY);
        score += 20;
        eatenPelletCount += 1;
        this->freeGhostHouseGhosts();
        this->updateGlobalState(FRIGHTENED);
    }
}

void GameState::checkPelletStatus() {
    if (this->eatenPelletCount == this->maze_p->getTotalPelletCount()) {
        this->gameOver = true;
    }
}


void GameState::freeGhostHouseGhosts() {
    if (eatenPelletCount == 1) {this->updateGhostState(AMBUSHER,ESCAPE);}
    else if (eatenPelletCount == 30){this->updateGhostState(FICKLE,ESCAPE);}
    else if (eatenPelletCount == 60){this->updateGhostState(STUPID,ESCAPE);}
}


void GameState::handleGhostCollisions() {
    Position pacmanPosition = this->pacman_p->getPos();
    this->handleGhostCollision(this->ghosts.chaser_p,pacmanPosition);
    this->handleGhostCollision(this->ghosts.ambusher_p,pacmanPosition);
    this->handleGhostCollision(this->ghosts.fickle_p,pacmanPosition);
    this->handleGhostCollision(this->ghosts.stupid_p,pacmanPosition);
}

void GameState::handleGhostCollision(Ghost * ghost,Position pacmanPosition) {
    if (ghost->getPos() == pacmanPosition) {
        switch (ghost->getGhostState()){
            case SCATTER:
            case ESCAPE:
            case CHASE: this->gameOver = true; break;
            case TRANSITION:
            case FRIGHTENED: this->eatGhost(ghost);break;
        default: // eaten or asleep
            break;
        }
    }
}


void GameState::eatGhost(Ghost * ghost) {
    ghost->setGhostState(EATEN);
    std::cout << "Eating ghost" << std::endl;
    this->score += 200; 
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

void GameState::updateGlobalState(GhostState newState) {

    static const std::unordered_map<GhostState, std::array<GhostState,2>> canSwitch = {
        {CHASE, {SCATTER,TRANSITION}},
        {SCATTER, {CHASE}},
        {TRANSITION, {FRIGHTENED}},
        {FRIGHTENED,{SCATTER,CHASE}}
    };
    std::array<GhostState,2> plausibleStates = canSwitch.at(newState);
    for (Ghost * ghost: this->ghostArray) {
        if (std::find(plausibleStates.begin(), plausibleStates.end(), ghost->getGhostState()) != plausibleStates.end()){
            ghost->setGhostState(newState);
        }
    }
    this->globalState = newState;
    this->startStateTimer();
}

bool GameState::isActive(Ghost * ghost) const {
    GhostState state =  ghost->getGhostState();
    return (state != SLEEP && state != ESCAPE && state != EATEN);
}

void GameState::startStateTimer() {
    this->stateStartTime = std::chrono::steady_clock::now(); 
}

bool GameState::hasTimeElapsed() const {
    static const std::unordered_map<GhostState, int> globalStateDurations = {
    {CHASE,20},
    {SCATTER,7},
    {FRIGHTENED,4},
    {TRANSITION,2},
};

    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<int> elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(now - stateStartTime);
    return elapsedTime.count() >= globalStateDurations.at(this->globalState);  
}

void GameState::switchToNextState() {
    if (this->globalState == CHASE) {
        std::cout << "Going into scatter" << std::endl;
        this->updateGlobalState(SCATTER);
    } else if (this->globalState == SCATTER) {
        std::cout << "Going into chase" << std::endl;
        this->updateGlobalState(CHASE);
    } else if (this->globalState == FRIGHTENED) {
        std::cout << "Going into transition" << std::endl;
        this->updateGlobalState(TRANSITION);
    } else {
        std::cout << "Going into chase" << std::endl;
        this->updateGlobalState(CHASE);
    }
}

bool GameState::isGameOver() const {return this->gameOver;}
unsigned int GameState::getScore() const {return this->score;}

