
#include "display.h"
#include "../game/game.h"

std::vector<std::string>  levelLayout = {
		"XXXXXXXXXXXXXXXXXXX",
		"X........X........X",
		"XoXX.XXX.X.XXX.XXoX",
		"X.................X",
		"X.XX.X.XXXXX.X.XX.X",
		"X....X...X...X....X",
		"XXXX.XXX X XXX.XXXX",
		"   X.X   C   X.X   ",
		"XXXX.X XX=XX X.XXXX",
		"    .  XFASX  .    ",
		"XXXX.X XXXXX X.XXXX",
		"   X.X       X.X   ",
		"XXXX.X XXXXX X.XXXX",
		"X........X........X",
		"X.XX.XXX.X.XXX.XX.X",
		"Xo.X.....P.....X.oX",
		"XX.X.X.XXXXX.X.X.XX",
		"X....X...X...X....X",
		"X.XXXXXX.X.XXXXXX.X",
		"X.................X",
		"XXXXXXXXXXXXXXXXXXX"
};


int main() {    

    GameState gs(levelLayout);
    Display display;



    while (display.window.isOpen()) {
        sf::Event event;
        while (display.window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                display.window.close();                
            }
        }



    


        display.window.clear();
        display.renderMaze(gs.getGrid());
    }



    return 0;
}
