#include "display.h"




Display::Display() {
    window.create(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT),"Pacman");

}

void Display::renderMaze(const grid_t& grid) {
    sf::RectangleShape wall(sf::Vector2f(PIXEL_SIZE,PIXEL_SIZE));
    wall.setFillColor(sf::Color::Blue);

    sf::RectangleShape empty(sf::Vector2f(PIXEL_SIZE,PIXEL_SIZE));
    empty.setFillColor(sf::Color::Black);

    sf::CircleShape pacman(PIXEL_SIZE/4);
    pacman.setFillColor(sf::Color::Yellow);

    



    // Draw walls only for now
    for (size_t y = 0; y < grid.size(); ++y) {
        for (size_t x = 0; x < grid[y].size(); ++x) {
            switch (grid[y][x])
            {
            case WALL:
                wall.setPosition(x * PIXEL_SIZE, y * PIXEL_SIZE);
                window.draw(wall);
                break; 
            case PACMAN_CELL:
                pacman.setPosition(x * PIXEL_SIZE, y * PIXEL_SIZE);
                window.draw(pacman);
                break;               
            default:
                empty.setPosition(x * PIXEL_SIZE, y * PIXEL_SIZE);
                window.draw(empty);
                break;
            }
        }
    }
    window.display();
}