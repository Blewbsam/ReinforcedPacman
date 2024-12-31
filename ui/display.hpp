#pragma once

#include <SFML/Graphics.hpp>
#include "pacmanUI.hpp"
#include "globalsUI.hpp"
#include "../game/game.hpp"
#include "ghosts/ghostUI.hpp"



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

    void initWindow();
    void initGameObjects();



    // check for and handle triggered events.
    void pollEvents();

    void updateGhosts();
    void updateGhost(GhostUI& ghost);

    void moveGhosts();
    void moveGhost(GhostUI& ghost);

    void handleTeleports();
    void handleTeleport(AgentUI& agent);


    // following set of functions set agent in approriat position to be displayed
    void renderPacman();
    void renderGhosts();

    // use the grid_t structure to render display
    void renderMaze(); 


    void gameLost();

public:
    Display(GameState * gameState);
    ~Display();

    // listens and reponses to events
    // move pieces to determined directions
    void update();
    // render required portions onto the display
    void render();

    void setPacmanDir(Direction dir);

    // returns wether the window is open or not
    bool running() const;
    
    sf::Image getScreenshot();
};

