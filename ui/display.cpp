#include <iostream>
#include "display.h"
#include "pacmanUI.h"



using std::cout;
using std::endl;


void Display::initVariables(GameState * gamestate) {
    this->window = nullptr;
}

void Display::initWindow() {
    this->videoMode.height = WINDOW_HEIGHT;
    this->videoMode.width = WINDOW_WIDTH;
    this->window = new sf::RenderWindow(this->videoMode,"Pacman");
    this->window->setFramerateLimit(144);
}

void Display::initGameObjects() {
    this->pellet.setRadius(PELLET_RADIUS);
    sf::Color orange(254,138,24);
    this->pellet.setFillColor(orange);

    this->gs->updateGhostState(CHASER,CHASE);
    gs->updateGhostPos(this->chaser.getIndexedPosition(),CHASER);
    gs->updatePacmanPos(this->pacman.getIndexedPosition());
    this->wall.setSize(sf::Vector2f(PIXEL_SIZE,PIXEL_SIZE));
    this->wall.setFillColor(sf::Color::Blue);
    this->door.setSize(sf::Vector2f(PIXEL_SIZE,PIXEL_SIZE));
    this->door.setFillColor(sf::Color::White);
    this->empty.setSize(sf::Vector2f(PIXEL_SIZE,PIXEL_SIZE));
    this->empty.setFillColor(sf::Color::Black);
}



Display::Display(GameState * gameState) :pacman(gameState), chaser(gameState), ambusher(gameState), fickle(gameState), stupid(gameState), gs(gameState) {
    this->initVariables(gameState);
    this->initGameObjects();
    this->initWindow();
}

Display::~Display() {
    delete this->window;
    delete this->gs;
}



void Display::update() {
    // pollEvents
    this->pollEvents();
    
    // movePacman
    this->pacman.move();

    // generateDirections ghosts should take
    if (this->chaser.containedInCell()) this->gs->generateGhostMoves();

    // move ghost towards that direction

    this->chaser.move();
    this->ambusher.move();
    this->fickle.move();
    this->stupid.move();

    // check if game is over.
    gs->handleCollisions();
}


void Display::render() {
    this->window->clear();
    this->renderMaze();
    this->renderPacman();
    this->renderGhosts();
    this->window->display();
}


void Display::pollEvents() {
    while (this->window->pollEvent(this->ev)) {
        if (this->ev.type == sf::Event::Closed) {
            this->window->close();                
        } else if (this->ev.key.code == sf::Keyboard::Escape) {
            this->window->close();
        } 
        if (this->ev.type == sf::Event::KeyPressed) {
            if (this->ev.key.code == sf::Keyboard::Up) {
                this->pacman.setNextDir(UP);
            } else if (this->ev.key.code == sf::Keyboard::Down) {
                this->pacman.setNextDir(DOWN);
            } else if (this->ev.key.code == sf::Keyboard::Right) {
                this->pacman.setNextDir(RIGHT);
            } else if (this->ev.key.code == sf::Keyboard::Left) {
                this->pacman.setNextDir(LEFT);
            }
        }
    }
}

bool Display::running() const {
    return this->window->isOpen();
}

void Display::renderPacman() {
    this->pacman.setPositionForRendering();
    this->window->draw(this->pacman.getGraphic());
}

void Display::renderGhosts() {
    this->chaser.setPositionForRendering();
    this->window->draw(this->chaser.getGraphic());

    this->ambusher.setPositionForRendering();
    this->window->draw(this->ambusher.getGraphic());

    this->fickle.setPositionForRendering();
    this->window->draw(this->fickle.getGraphic());

    this->stupid.setPositionForRendering();
    this->window->draw(this->stupid.getGraphic());

}


void Display::renderMaze() {

    grid_t grid = gs->getGrid();
    for (size_t y = 0; y < grid.size(); ++y) {
        for (size_t x = 0; x < grid[y].size(); ++x) {
            switch (grid[y][x])
            {
            case WALL:
                this->wall.setPosition(x * PIXEL_SIZE, y * PIXEL_SIZE);
                this->window->draw(this->wall);
                break; 
            case PELLET:
                this->pellet.setPosition(x * PIXEL_SIZE + PELLET_OFFSET, y * PIXEL_SIZE + PELLET_OFFSET);
                this->window->draw(this->pellet);           
                break;
            case DOOR:
                this->door.setPosition(x * PIXEL_SIZE, y * PIXEL_SIZE);
                this->window->draw(this->door);  
                break;
            default:
                this->empty.setPosition(x * PIXEL_SIZE, y * PIXEL_SIZE);
                this->window->draw(this->empty);
                break;
            }
        }
    }
}
