

#include "ghost.h"




Ghost::Ghost(Position position): Agent(position,IDLE){}

FickleGhost::FickleGhost(Position position) : Ghost(position){}
ChaserGhost::ChaserGhost(Position position) : Ghost(position) {}
AmbusherGhost::AmbusherGhost(Position position) : Ghost(position) {}
StupidGhost::StupidGhost(Position position) : Ghost(position) {}
