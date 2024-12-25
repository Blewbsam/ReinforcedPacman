

#ifndef GHOST
#define GHOST

#include "agent.h"

class Ghost: public Agent {
    protected:
    // Ghosts target tile. initalized to (-1,-1)
    Position target;
    GhostState state;

    public:
    Ghost(Position position);


    void setGhostState(GhostState ghostState);
    GhostState getGhostState();
};



class FickleGhost: public Ghost {
    public:
    FickleGhost(Position position);
};

class ChaserGhost: public Ghost {
    public: 
    ChaserGhost(Position position);
};

class AmbusherGhost: public Ghost {
    public:
    AmbusherGhost(Position position);
};

class StupidGhost: public Ghost {
    public:
    StupidGhost(Position position);
};





#endif