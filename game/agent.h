
#ifndef AGENT
#define AGENT
#include <utility> 
#include <vector>

 
enum Direction {UP,DOWN,LEFT,RIGHT,IDLE}; // Represents Direction in which agent is moving in

struct Position { // Represents Position where agent is located correspondig to gameState.
    int x;
    int y;
};

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