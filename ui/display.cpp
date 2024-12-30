#include <iostream>
#include "display.hpp"
#include "ghosts/speeds.hpp"
#include "pacmanUI.hpp"


void Display::initWindow() {
    this->videoMode.height = WINDOW_HEIGHT;
    this->videoMode.width = WINDOW_WIDTH;
    this->window = new sf::RenderWindow(this->videoMode,"Pacman");
    this->window->setFramerateLimit(FRAMES);
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

Display::Display(GameState * gameState) :pacman(gameState), gs(gameState) {
    this->initGameObjects();
    this->initWindow();
}

Display::~Display() {
    delete this->window;
}

void Display::update() {
    if (!gs->isGameOver()) {
        this->pollEvents();
        this->pacman.move();
        // generate Directions ghosts should take : using linear interpolation for rendering.
        if (this->chaser.containedInCell()) {
            this->gs->generateGhostMove(CHASER);
            this->chaser.setDir(this->gs->getGhostDir(CHASER));
            this->chaser.setState(this->gs->getGhostState(CHASER));
        }
        if (this->ambusher.containedInCell()) {
            this->gs->generateGhostMove(AMBUSHER);
            this->ambusher.setDir(this->gs->getGhostDir(AMBUSHER));
            this->ambusher.setState(this->gs->getGhostState(AMBUSHER));
        }
        if (this->stupid.containedInCell()) {
            this->gs->generateGhostMove(STUPID);
            this->stupid.setDir(this->gs->getGhostDir(STUPID));
            this->stupid.setState(this->gs->getGhostState(STUPID));
        }
        if (this->fickle.containedInCell()) {
            this->gs->generateGhostMove(FICKLE);
            this->fickle.setDir(this->gs->getGhostDir(FICKLE));
            this->fickle.setState(this->gs->getGhostState(FICKLE));
        }
        this->chaser.move();
        if (this->chaser.containedInCell()) this->gs->updateGhostPos(this->chaser.getIndexedPosition(),CHASER);
        this->ambusher.move();
        if (this->ambusher.containedInCell()) this->gs->updateGhostPos(this->ambusher.getIndexedPosition(),AMBUSHER);
        this->stupid.move();
        if (this->stupid.containedInCell()) this->gs->updateGhostPos(this->stupid.getIndexedPosition(),STUPID);
        this->fickle.move();
        if (this->fickle.containedInCell()) this->gs->updateGhostPos(this->fickle.getIndexedPosition(),FICKLE);
        gs->handleCollisions();

        this->handleTeleports();
    } else {
        this->gameLost();
    }  
}
void Display::handleTeleports() {
    handleTeleport(pacman);
    handleTeleport(chaser);
    handleTeleport(stupid);
    handleTeleport(fickle);
    handleTeleport(ambusher);
}

void Display::handleTeleport(AgentUI& agent) {
    if (gs->jumpAvail(agent.getIndexedPosition())) agent.setSFPosition(gs->jumpPortal(agent.getIndexedPosition()));
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