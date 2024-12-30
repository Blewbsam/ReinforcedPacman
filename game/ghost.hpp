

#ifndef GHOST
#define GHOST

#include "agent.hpp"

class Ghost: public Agent {
    protected:
    // Ghosts target tile. initalized to (-1,-1)
    Position scatterCorner;
    GhostState state;

    public:
    Ghost(Position sc);
    Position getScatterCorner() const;
    void setGhostState(GhostState ghostState);
    GhostState getGhostState() const;
};



class FickleGhost: public Ghost {
    public:
    FickleGhost();
};

class ChaserGhost: public Ghost {
    public: 
    ChaserGhost();
};

class AmbusherGhost: public Ghost {
    public:
    AmbusherGhost();
};

class StupidGhost: public Ghost {
    public:
    StupidGhost();
};





#endif