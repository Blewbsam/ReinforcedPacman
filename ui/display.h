#ifndef DISPLAY
#define DISPLAY

#include <SFML/Graphics.hpp>
// #include "../game/maze.h"
#include "globalsUI.h"
#include "../game/game.h"
#include "pacmanUI.h"



class Display {

private: 
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event ev;
    GameState * gs;

    // game objects
    PacmanUI pacman;
    sf::RectangleShape wall;
    sf::RectangleShape empty;
    sf::CircleShape pellet;


    // initializaton of display
    void initVariables(GameState * gameState);
    void initWindow();

    // initializes gameObjects to proper sizes and colors
    void initGameObjects();

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

};


#endif  