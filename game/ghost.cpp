

#include "ghost.h"


Ghost::Ghost(Position sc): Agent(IDLE), state(SLEEP), scatterCorner(sc){}

void Ghost::setGhostState(GhostState ghostState) {
    this->state = ghostState;
}

Position Ghost::getScatterCorner() const {return this->scatterCorner;}
GhostState Ghost::getGhostState() const {return this->state;}




// Positions for ghosts to persuit in SCATTER state.
const Position topLeft = {2,1};
const Position topRight = {17,1};
const Position bottomLeft = {2,19};
const Position bottomRight = {17,19};

FickleGhost::FickleGhost() : Ghost(bottomRight){}
ChaserGhost::ChaserGhost() : Ghost(topRight){}
AmbusherGhost::AmbusherGhost() : Ghost(topLeft){}
StupidGhost::StupidGhost() : Ghost(bottomLeft){}
