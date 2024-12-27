

#include "ghost.h"


Ghost::Ghost(Position sc): Agent(IDLE), state(SLEEP), scatterCorner(sc){}

void Ghost::setGhostState(GhostState ghostState) {
    if (ghostState == FRIGHTENED) std::cout << "I am scared" << std::endl;
    this->state = ghostState;
}

Position Ghost::getScatterCorner() const {return this->scatterCorner;}
GhostState Ghost::getGhostState() const {return this->state;}





const Position topLeft = {1,1};
const Position topRight = {16,1};
const Position bottomLeft = {1,19};
const Position bottomRight = {16,19};



FickleGhost::FickleGhost() : Ghost(bottomRight){}
ChaserGhost::ChaserGhost() : Ghost(topRight){}
AmbusherGhost::AmbusherGhost() : Ghost(topLeft){}
StupidGhost::StupidGhost() : Ghost(bottomLeft){}
