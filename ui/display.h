#ifndef DISPLAY
#define DISPLAY

#include <SFML/Graphics.hpp>
#include "../game/maze.h"
#include "../game/game.h"

#define WINDOW_HEIGHT 630
#define WINDOW_WIDTH 570
#define PIXEL_SIZE 30.f
#define PACMAN_RADIUS 15.f
#define PACMAN_START_X 5
#define PACMAN_START_Y 13
#define PACMAN_STEP_SIZE 2


class Display {

private: 
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event ev;
    GameState * gs;

    // game objects
    sf::CircleShape pacman;
    sf::RectangleShape wall;
    sf::RectangleShape empty;

    // Position of unique game objects
    sf::Vector2f pacmanPos;
    // Pacman's current direction
    Direction pacmanDir;
    // Next Direction Pacman should have. Set by events
    Direction nextDir;

    // initializaton of display
    void initVariables(GameState * gameState);
    void initWindow();

    // initializes gameObjects to proper sizes and colors
    void initGameObjects();


    // changes direction of pacman to specified dir
    void setNextDir(Direction dir); 
    // snap pacman position to nearest valid grid.
    void snapPacmanToGrid(); 
    // returns true if pacman can move in given direciton, false otherwise
    bool validPacmanMove(Direction dir); 
    // Moves pacman in specified direction.
    void pacmanMove(); 
    // returns true if pacman is in single PIXEL sized cell
    bool pacmanContainedInCell(); 

public:
    Display(GameState * gameState);
    ~Display();

    // listens and reponses to events
    // move pieces to determined directions
    void update();
    // render required portions onto the display
    void render();
    // check for and handle triggered events.
    void pollEvents();
    // places pacman in appropriate position
    void renderPacman();
    // use the grid_t structure to render display
    void renderMaze(); 
    // returns wether the window is open or not
    bool running() const;

    // conersts Vector2f pacmanPos to Position struct
    Position getIndexedPacmanPos();



};


#endif  