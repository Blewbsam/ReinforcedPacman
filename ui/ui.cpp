
#include "display.h"
#include "../game/game.h"

std::vector<std::string>  levelLayout = {
		"XXXXXXXXXXXXXXXXXXX",
		"X........X........X",
		"XXXX.XXX.X.XXX.XXXX",
		"X.................X",
		"X.XX.X.XXXXX.X.XX.X",
		"X....X...X...X....X",
		"XXXX.XXX X XXX.XXXX",
		"   X.X       X.X   ",
		"XXXX.X XX=XX X.XXXX",
		"    .  X   X  .    ",
		"XXXX.X XXXXX X.XXXX",
		"   X.X       X.X   ",
		"XXXX.X XXXXX X.XXXX",
		"X........X........X",
		"X.XX.XXX.X.XXX.XX.X",
		"X .X..... .....X. X",
		"XX.X.X.XXXXX.X.X.XX",
		"X....X...X...X....X",
		"X.XXXXXX.X.XXXXXX.X",
		"X.................X",
		"XXXXXXXXXXXXXXXXXXX"
};


int main() {    

    GameState * gs = new GameState(levelLayout);
    Display display(gs);

    sf::Event event;

    while (display.running()) {
        // update
        display.update();

        // render
        display.render();
    }



    return 0;
}
