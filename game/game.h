

#ifndef GAME
#define GAME    

#include "ghost.h"
#include "pacman.h"
#include "maze.h"


#include <vector>

// Pointer to created Ghosts fond on maze
struct Ghosts {
    FickleGhost * fickle_p;
    ChaserGhost * chaser_p;
    AmbusherGhost * ambusher_p;
    StupidGhost * stupid_p;
};



class GameState {
    Maze * maze_p;
    Pacman * pacman_p;
    Ghosts ghosts;
    bool gameOver;
public:
    GameState(const std::vector<std::string>& layout);
    ~GameState();

    // getters used to get position of agents: 
    Position getPacmanPos();
    Position getFicklePos();
    Position getAmbusherPos();
    Position getStupidPos();
    Position getChaserPos();
    grid_t getGrid();


    // changes position of pacman  to given pos.
    void updatePacmanPos(Position pos);

    // assesses wether pacman moving in given direction encounters a wall.
    bool validPacmanMove(Direction dir) const;



private:

    // Iterators over all cells to find position of specifiedagentCell being one of: 
    // {GHOST_FICKLE,GHOST_CHASER, GHOST_AMBUSER, GHOST_STUPID}
    // To be used in constructor only
    Position getAgentPositionBrute(Cell agentCell ,const std::vector<std::vector<Cell >> grid);    

};




#endif 
