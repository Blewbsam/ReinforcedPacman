

#include "ghost.h"

Position initTile = {-1,-1};

Ghost::Ghost(Position position): Agent(position,IDLE), state(SLEEP), target(initTile){}

void Ghost::setGhostState(GhostState ghostState) {
    this->state = ghostState;
}

GhostState Ghost::getGhostState() {return this->state;}



FickleGhost::FickleGhost(Position position) : Ghost(position){}
ChaserGhost::ChaserGhost(Position position) : Ghost(position){}
AmbusherGhost::AmbusherGhost(Position position) : Ghost(position){}
StupidGhost::StupidGhost(Position position) : Ghost(position){}
