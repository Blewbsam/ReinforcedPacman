

#include "ghost.h"

const Position initTile = {-1,-1};

Ghost::Ghost(Position position, Position sc): Agent(position,IDLE), state(SLEEP), target(initTile), scatterCorner(sc){}

void Ghost::setGhostState(GhostState ghostState) {
    this->state = ghostState;
}

Position Ghost::getScatterCorner() const {return this->scatterCorner;}
GhostState Ghost::getGhostState() const {return this->state;}



const Position topLeft = {1,1};
const Position topRight = {16,1};
const Position bottomLeft = {1,19};
const Position bottomRight = {16,19};



FickleGhost::FickleGhost(Position position) : Ghost(position,bottomRight){}
ChaserGhost::ChaserGhost(Position position) : Ghost(position,topRight){}
AmbusherGhost::AmbusherGhost(Position position) : Ghost(position,topLeft){}
StupidGhost::StupidGhost(Position position) : Ghost(position,bottomLeft){}
