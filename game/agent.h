
#ifndef AGENT
#define AGENT
#include <utility> 
#include <vector>
#include "globals.h"


extern std::vector<Direction> directions;

class Agent {
protected:
    Position pos;
    Direction dir;
public:
    Agent(Position p, Direction direction);

    Position getPos();
    void setPos(Position p);

};




#endif