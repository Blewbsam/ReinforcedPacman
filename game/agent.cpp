
#include "agent.hpp"


Position agentStartPosition = {-1,-1};

std::vector<Direction> directions = {UP, DOWN, LEFT, RIGHT};

Agent::Agent(Direction direction) : pos(agentStartPosition), dir(direction) {};

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
