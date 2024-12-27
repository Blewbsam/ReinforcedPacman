
#ifndef FICKLE_UI
#define FICKLE_UI

#include "ghostUI.h"
#include "../globalsUI.h"

#define FICKLE_START_X PIXEL_SIZE * 9
#define FICKLE_START_Y PIXEL_SIZE * 9

class FickleUI : public GhostUI{    
    public:
    FickleUI(GameState * gameState);
    void move() override;
};



#endif