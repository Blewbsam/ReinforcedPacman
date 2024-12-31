
#include "display.hpp"
#include "../game/game.hpp"

// g++ command: g++ -std=c++11 ghosts/*.cpp  *.cpp  ../game/*.cpp  -I/opt/homebrew/Cellar/sfml/2.6.2/include -o main  -L/opt/homebrew/Cellar/sfml/2.6.2/lib -lsfml-graphics -lsfml-window -lsfml-system

int main() {    

    GameState * gs = new GameState();
    Display display(gs);
    while (display.running()) {
        display.update();
        display.render();
    }

    return 0;
}
