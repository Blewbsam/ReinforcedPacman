#include <iostream>
#include "display.h"



using std::cout;
using std::endl;


void Display::initVariables(GameState * gamestate) {
    this->window = nullptr;
    this->gs = gamestate;
}

void Display::initWindow() {
    this->videoMode.height = WINDOW_HEIGHT;
    this->videoMode.width = WINDOW_WIDTH;
    this->window = new sf::RenderWindow(this->videoMode,"Pacman");
    this->window->setFramerateLimit(144);
}



void Display::initGameObjects() {
    this->pacman.setRadius(PACMAN_RADIUS);
    this->pacman.setFillColor(sf::Color::Yellow);
    this->pacmanPos.x = PACMAN_START_X * PIXEL_SIZE;
    this->pacmanPos.y = PACMAN_START_Y * PIXEL_SIZE;
    this->pacmanDir = IDLE;
    this->nextDir = RIGHT;
    gs->updatePacmanPos(this->getIndexedPacmanPos());
    this->wall.setSize(sf::Vector2f(PIXEL_SIZE,PIXEL_SIZE));
    this->wall.setFillColor(sf::Color::Blue);
    this->empty.setSize(sf::Vector2f(PIXEL_SIZE,PIXEL_SIZE));
    this->empty.setFillColor(sf::Color::Black);
}



Display::Display(GameState * gameState) {
    this->initVariables(gameState);
    this->initGameObjects();
    this->initWindow();
    // this->initPacman();
    // this->initGhosts();
}

Display::~Display() {
    delete this->window;
    delete this->gs;
}



void Display::update() {
    // pollEvents
    this->pollEvents();
    
    // movePacman
    this->pacmanMove();

    // moveGhosts

    // check if game is over.

}


void Display::render() {
    this->window->clear();
    this->renderMaze();
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
                setNextDir(UP);
            } else if (this->ev.key.code == sf::Keyboard::Down) {
                setNextDir(DOWN);
            } else if (this->ev.key.code == sf::Keyboard::Right) {
                setNextDir(RIGHT);
            } else if (this->ev.key.code == sf::Keyboard::Left) {
                setNextDir(LEFT);
            }
        }
    }
}



bool Display::running() const {
    return this->window->isOpen();
}




bool Display::validPacmanMove(Direction dir)  {
    return this->pacmanContainedInCell() && gs->validPacmanMove(dir);
}

void Display::setNextDir(Direction dir) {
    this->nextDir = dir;
}

void Display::pacmanMove() {
    if (this->pacmanContainedInCell() && this->nextDir != this->pacmanDir && gs->validPacmanMove(this->nextDir)) this->pacmanDir = this->nextDir;
    if (gs->validPacmanMove(pacmanDir)) {
        switch (pacmanDir) {
            case UP:    pacmanPos.y -= PACMAN_STEP_SIZE; break;
            case DOWN:  pacmanPos.y += PACMAN_STEP_SIZE; break;
            case LEFT:  pacmanPos.x -= PACMAN_STEP_SIZE; break;
            case RIGHT: pacmanPos.x += PACMAN_STEP_SIZE; break;
            default:    break;
        }
    }
    // gs should know position of pacman for generating valid moves.
    if (pacmanContainedInCell()) gs->updatePacmanPos(this->getIndexedPacmanPos());
}

void Display::renderPacman() {
    this->pacman.setPosition(this->pacmanPos.x,this->pacmanPos.y);
    this->window->draw(this->pacman);
}


void Display::snapPacmanToGrid() {
    pacmanPos.x = std::round(pacmanPos.x / PIXEL_SIZE) * PIXEL_SIZE;
    pacmanPos.y = std::round(pacmanPos.y / PIXEL_SIZE) * PIXEL_SIZE;
}




void Display::renderMaze() {


    grid_t grid = gs->getGrid();

    // Draw walls only for now
    for (size_t y = 0; y < grid.size(); ++y) {
        for (size_t x = 0; x < grid[y].size(); ++x) {
            switch (grid[y][x])
            {
            case WALL:
                this->wall.setPosition(x * PIXEL_SIZE, y * PIXEL_SIZE);
                this->window->draw(this->wall);
                break; 
            case PACMAN_CELL:
                this->pacman.setPosition(x * PIXEL_SIZE, y * PIXEL_SIZE);
                this->window->draw(this->pacman);
                break;               
            default:
                this->empty.setPosition(x * PIXEL_SIZE, y * PIXEL_SIZE);
                this->window->draw(this->empty);
                break;
            }
        }
    }
}


Position Display::getIndexedPacmanPos() {
    Position pos;
    pos.x = std::round((this->pacmanPos.x)/ PIXEL_SIZE);
    pos.y = std::round((this->pacmanPos.y)/ PIXEL_SIZE);

    cout << "Pixel" << endl;
    cout << "(" << this->pacmanPos.x <<"," << this->pacmanPos.y << ")" << endl;
    cout << "Position" << endl;
    cout << "("<< pos.x << "," << pos.y << ")" << endl;
    return pos;
}



bool Display::pacmanContainedInCell() {
    return (std::fmod(this->pacmanPos.x,PIXEL_SIZE) == 0 && std::fmod(this->pacmanPos.y,PIXEL_SIZE) == 0);
}