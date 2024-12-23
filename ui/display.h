#ifndef DISPLAY
#define DISPLAY

#include <SFML/Graphics.hpp>
#include "../game/maze.h"

#define WINDOW_HEIGHT 630
#define WINDOW_WIDTH 570
#define PIXEL_SIZE 30.f

class Display {

public:
    sf::RenderWindow window;
    Display();
    void renderMaze(const grid_t& grid); 
    
};


#endif  