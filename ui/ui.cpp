
#include "display.h"
#include "../game/game.h"


int main() {    

    GameState * gs = new GameState();
    Display display(gs);
    while (display.running()) {
        display.update();
        display.render();
    }

    return 0;
}
