// #include <iostream>
// #include "game.h"

// // compilation g++ main.cpp -I/opt/homebrew/Cellar/sfml/2.6.2/include -o prog -L//opt/homebrew/Cellar/sfml/2.6.2/lib -lsfml-graphics -lsfml-window -lsfml-system
// #include <vector>

// using std::cout;
// using std::endl;



// int main() {

//     std::vector<std::string>  levelLayout = {
// 		" XXXXXXXXXXXXXXXXXXX ",
// 		" X........X........X ",
// 		" XoXX.XXX.X.XXX.XXoX ",
// 		" X.................X ",
// 		" X.XX.X.XXXXX.X.XX.X ",
// 		" X....X...X...X....X ",
// 		" XXXX.XXX X XXX.XXXX ",
// 		"    X.X   C   X.X    ",
// 		"XXXXX.X XX=XX X.XXXXX",
// 		"     .  XFASX  .     ",
// 		"XXXXX.X XXXXX X.XXXXX",
// 		"    X.X       X.X    ",
// 		" XXXX.X XXXXX X.XXXX ",
// 		" X........X........X ",
// 		" X.XX.XXX.X.XXX.XX.X ",
// 		" Xo.X.....P.....X.oX ",
// 		" XX.X.X.XXXXX.X.X.XX ",
// 		" X....X...X...X....X ",
// 		" X.XXXXXX.X.XXXXXX.X ",
// 		" X.................X ",
// 		" XXXXXXXXXXXXXXXXXXX "
// };


//     GameState gs(levelLayout);



//     Position pos = gs.getPacmanPos();


//     pos = gs.getAmbusherPos();
//     cout << pos.x << endl;
//     cout << pos.y << endl;

//     // Maze m = Maze(levelLayout);
//     // m.printGrid();
// }