

#ifndef GAME
#define GAME    

#include "globals.h"
#include "ghost.h"
#include "pacman.h"
#include "maze.h"
#include "ghostAI.h"
#include "globals.h"

#include <chrono>
#include <vector>
#include <unordered_map>

extern const std::unordered_map<GhostState,int> globalStateDurations;




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
    GhostAI ghostAI;
    GhostState globalState;
    std::chrono::steady_clock::time_point stateStartTime;
    unsigned int score;
    bool gameOver;

public:
    GameState();
    ~GameState();

    // getters used to get position of agents:
    Position getPacmanPos() const;
    Direction getPacmanDir() const;

    Direction getGhostDir(GhostType type);
    GhostState getGhostState(GhostType type);

    // maze_p accessors for communicating with GhostAI
    grid_t getGrid() const;
    int getGridWidth() const;
    int getGridHeight() const;

    GhostState getGlobalState() const;



    // changes position of pacman to given pos.
    void updatePacmanPos(Position pos);

    // assesses wether pacman moving in given direction encounters a wall.
    bool validPacmanMove(Direction dir) const;

    // Changes direction of pacman to given direction
    void changePacmanDir(Direction dir);



    // set the directon of each ghost given the board and pacman positions.
    void generateGhostMove(GhostType type);

    // set position of given ghost
    void updateGhostPos(Position pos,GhostType type);

    // set state of type to given state
    void updateGhostState(GhostType type, GhostState state);

    // handle all plausible collisions.
    void handleCollisions();

    // returns true if jump possible
    bool jumpAvail(Position pos);
    // takes current pos and returns what it would become
    // requires jumpAvail to return true
    Position jumpPortal(Position pos);

    // returns valid positions that the ghost can move in.
    std::vector<Position> getValidPositions(Position ghostPos, Direction ghostDir, bool hasEscaped) const;
    // Return neighbors of position on grid which are not walls.
    std::vector<Position> getValidNeighbours(Position pos, bool hasEscaped) const;

    // gameOver getter
    bool isGameOver() const;


private:

    // Iterators over all cells to find position of specifiedagentCell being one of: 
    // {GHOST_FICKLE,GHOST_CHASER, GHOST_AMBUSER, GHOST_STUPID}
    // To be used in constructor only
    // Position getAgentPositionBrute(Cell agentCell ,const std::vector<std::vector<Cell >> grid);    

    // check if there is a pellet at pacman's position
    // and remove it if there is so
    void handlePelletCollision();
    void handlePowerPelletCollision();
    void handleGhostCollisions();
    void handleGhostCollision(Ghost * ghost, Position pacmanPosition);

    // changes globalState to newState and changes the state of all active prevStates.
    void updateGlobalState(GhostState prevState,GhostState newState);

    // sets ghost states for beginnig of the game.
    void setInitialGhostStates();

    // resets startTimer.
    void startStateTimer();
    // checks if it is time for new state
    bool hasTimeElapsed() const;
    // switches to next state and resets timer;
    void switchToNextState();

};




#endif 
