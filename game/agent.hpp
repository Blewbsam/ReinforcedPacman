
#ifndef AGENT
#define AGENT
#include <utility> 
#include <vector>
#include "globals.hpp"


extern std::vector<Direction> directions;

class Agent {
protected:
    Position pos;
    Direction dir;
public:
    Agent(Direction direction);
    Position getPos();
    void setPos(Position p);
    void setDir(Direction dir);
    Direction getDir();
};




#endif