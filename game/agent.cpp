
#include "agent.h"



std::vector<Direction> directions = {UP, DOWN, LEFT, RIGHT};

Agent::Agent(Position position, Direction direction) : pos(position), dir(direction) {};

Position Agent::getPos() {
        return pos;
}

void Agent::move(Direction dir) {
    // TODO: implement move
}
