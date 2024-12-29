
#ifndef AMBUSHER_UI
#define AMBUSHER_UI

#include "ghostUI.h"
#include "../globalsUI.h"

#define AMBUSHER_START_X PIXEL_SIZE * 10
#define AMBUSHER_START_Y PIXEL_SIZE * 9

class AmbusherUI : public GhostUI {
    public:
    AmbusherUI(GameState * gameState);
};


#endif