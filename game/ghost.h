

#ifndef GHOST
#define GHOST

#include "agent.h"

class Ghost: public Agent {
    public:
    Ghost(Position position);
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