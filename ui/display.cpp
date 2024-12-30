#include <iostream>
#include "display.h"
#include "pacmanUI.h"



using std::cout;
using std::endl;


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

    this->powerPellet.setRadius(POWER_PELLET_RADIUS);
    this->powerPellet.setFillColor(orange);

    this->gs->updateGhostPos(this->chaser.getIndexedPosition(),CHASER);
    this->gs->updateGhostPos(this->ambusher.getIndexedPosition(),AMBUSHER);
    this->gs->updateGhostPos(this->stupid.getIndexedPosition(), STUPID);
    this->gs->updateGhostPos(this->fickle.getIndexedPosition(),FICKLE);

    gs->updatePacmanPos(this->pacman.getIndexedPosition());

    this->wall.setSize(sf::Vector2f(PIXEL_SIZE,PIXEL_SIZE));
    this->wall.setFillColor(sf::Color::Blue);
    this->door.setSize(sf::Vector2f(PIXEL_SIZE,PIXEL_SIZE));
    this->door.setFillColor(sf::Color::White);
    this->empty.setSize(sf::Vector2f(PIXEL_SIZE,PIXEL_SIZE));
    this->empty.setFillColor(sf::Color::Black);
}

Display::Display(GameState * gameState) :pacman(gameState), chaser(gameState), ambusher(gameState), fickle(gameState), stupid(gameState), gs(gameState) {
    this->initGameObjects();
    this->initWindow();
}

Display::~Display() {
    delete this->window;
    delete this->gs;
}

void Display::update() {
    if (!gs->isGameOver()) {
        this->pollEvents();
        this->pacman.move();
        // generate Directions ghosts should take
        if (this->chaser.containedInCell()) this->gs->generateGhostMove(CHASER);
        if (this->ambusher.containedInCell()) this->gs->generateGhostMove(AMBUSHER);
        if (this->stupid.containedInCell()) this->gs->generateGhostMove(STUPID);
        if (this->fickle.containedInCell()) this->gs->generateGhostMove(FICKLE);


        this->chaser.move();
        this->ambusher.move();
        this->stupid.move();
        this->fickle.move();
        gs->handleCollisions();
    } else {
        this->gameLost();
    }  
}

void Display::render() {
    this->window->clear();
    this->renderMaze();
    this->renderGhosts();
    this->renderPacman();
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
                this->setPacmanDir(UP);
            } else if (this->ev.key.code == sf::Keyboard::Down) {
                this->setPacmanDir(DOWN);
            } else if (this->ev.key.code == sf::Keyboard::Right) {
                this->setPacmanDir(RIGHT);
            } else if (this->ev.key.code == sf::Keyboard::Left) {
                this->setPacmanDir(LEFT);
            }
        }
    }
}

void Display::setPacmanDir(Direction dir) {
    this->pacman.setNextDir(dir);
}

bool Display::running() const {
    return this->window->isOpen();
}

void Display::renderPacman() {

    this->pacman.setPositionForRendering();
    this->pacman.setOrientationForRendering();
    this->window->draw(this->pacman.getSprite());
}

void Display::renderGhosts() {
    this->chaser.render(this->gs->getGhostState(CHASER),this->gs->getGhostDir(CHASER));
    this->window->draw(this->chaser.getSprite());
    this->window->draw(this->chaser.getFace());

    this->ambusher.render(this->gs->getGhostState(AMBUSHER),this->gs->getGhostDir(AMBUSHER));
    this->window->draw(this->ambusher.getSprite());
    this->window->draw(this->ambusher.getFace());

    this->fickle.render(this->gs->getGhostState(FICKLE),this->gs->getGhostDir(FICKLE));
    this->window->draw(this->fickle.getSprite());
    this->window->draw(this->fickle.getFace());

    this->stupid.render(this->gs->getGhostState(STUPID),this->gs->getGhostDir(STUPID));
    this->window->draw(this->stupid.getSprite());
    this->window->draw(this->stupid.getFace());
}

void Display::gameLost() {
    this->window->close();
}

void Display::renderMaze() {
    grid_t grid = gs->getGrid();
    for (size_t y = 0; y < grid.size(); ++y) {
        for (size_t x = 1; x < grid[y].size() - 1; ++x) {
            switch (grid[y][x])
            {
            case WALL:
                this->wall.setPosition((x-1) * PIXEL_SIZE, y * PIXEL_SIZE);
                this->window->draw(this->wall);
                break; 
            case PELLET:
                this->pellet.setPosition((x-1) * PIXEL_SIZE + PELLET_OFFSET, y * PIXEL_SIZE + PELLET_OFFSET);
                this->window->draw(this->pellet);           
                break;
            case POWER_PELLET:
                this->powerPellet.setPosition((x-1) * PIXEL_SIZE + POWER_PELLET_OFFSET, y * PIXEL_SIZE + POWER_PELLET_OFFSET);
                this->window->draw(this->powerPellet);
                break;
            case DOOR:
                this->door.setPosition((x-1) * PIXEL_SIZE, y * PIXEL_SIZE);
                this->window->draw(this->door);  
                break;
            default:
                this->empty.setPosition((x-1) * PIXEL_SIZE, y * PIXEL_SIZE);
                this->window->draw(this->empty);
                break;
            }
        }
    }
}


sf::Image Display::getScreenshot() {
    return this->window->capture();
}