
#include "agent.h"



std::vector<Direction> directions = {UP, DOWN, LEFT, RIGHT};

Agent::Agent(Position position, Direction direction) : pos(position), dir(direction) {};

Position Agent::getPos() {
        return this->pos;
}


void Agent::setPos(Position p) {
    this->pos = p;
}

void Agent::setDir(Direction dir) {
    this->dir = dir;
}

Direction Agent::getDir() {
    return this->dir;
}
