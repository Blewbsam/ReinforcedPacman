
#ifndef CHASER_UI
#define CHASER_UI

#include "ghostUI.h"
#include "../globalsUI.h"

#define CHASER_START_X PIXEL_SIZE * 9
#define CHASER_START_Y PIXEL_SIZE * 7

class ChaserUI : public GhostUI{    
    public:
    ChaserUI(GameState * gameState);
};



#endif