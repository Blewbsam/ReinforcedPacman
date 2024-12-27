
#ifndef STUPID_UI
#define STUPID_UI

#include "ghostUI.h"
#include "../globalsUI.h"

#define STUPID_START_X PIXEL_SIZE * 10
#define STUPID_START_Y PIXEL_SIZE * 9

class StupidUI : public GhostUI{    
    public:
    StupidUI(GameState * gameState);
    void move() override;
};





#endif