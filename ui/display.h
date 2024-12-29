#ifndef DISPLAY
#define DISPLAY

#include <SFML/Graphics.hpp>
#include "pacmanUI.h"
#include "globalsUI.h"
#include "../game/game.h"
#include "ghosts/chaserUI.h"
#include "ghosts/ambusherUI.h"
#include "ghosts/fickleUI.h"
#include "ghosts/stupidUI.h"



class Display {

private: 
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event ev;
    GameState * gs;

    // game objects
    PacmanUI pacman;
    ChaserUI chaser;
    AmbusherUI ambusher;
    FickleUI fickle;
    StupidUI stupid;

    sf::RectangleShape wall;
    sf::RectangleShape door;
    sf::RectangleShape empty;
    sf::CircleShape pellet;
    sf::CircleShape powerPellet;


    // initializaton of display
    void initWindow();

    // initializes gameObjects to proper sizes and colors
    void initGameObjects();

    // animation to run once game is over.
    void gameLost();

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

    // following set of functions set agent in approriat position to be displayed
    void renderPacman();
    void renderGhosts();



    // use the grid_t structure to render display
    void renderMaze(); 


    // returns wether the window is open or not
    bool running() const;




};


#endif  