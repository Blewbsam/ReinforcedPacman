
#pragma once

#include "../../game/game.hpp"
#include <SFML/Graphics.hpp>
#include "../../game/globals.hpp"
#include "agentUI.hpp"
#include "../globalsUI.hpp"

class GhostUI : public AgentUI {
    protected:
        GhostType ghostType;
        sf::Sprite * face;
        sf::Color defaultColor;
        Direction dir;
        GhostState state;
    public:
        GhostUI(sf::Vector2f pos, sf::Color defaultColor, GhostType type);
        
        sf::Sprite getFace();
        
        // moves Ghost to dir by set_size
        virtual void move() override;

        // gets stepsize of ghost
        int getGhostStepSize();

        void setOrientationForRendering() override;

        void render(GhostState state, Direction ghostDir);
        void setBodyColorForRendering(GhostState state);
        void setFacePositionForRendering();
        void setFaceOrientationForRendering(GhostState state, Direction ghostDir);

        void nextFrame();
        int getRowIndex(Direction ghostDir);

        void setDir(Direction direction);
        void setState(GhostState state);
};




#define AMBUSHER_START_X PIXEL_SIZE * 10
#define AMBUSHER_START_Y PIXEL_SIZE * 9

class AmbusherUI : public GhostUI {
    public:
    AmbusherUI();
};


#define CHASER_START_X PIXEL_SIZE * 9
#define CHASER_START_Y PIXEL_SIZE * 7

class ChaserUI : public GhostUI{    
public:
    ChaserUI();
};

#define FICKLE_START_X PIXEL_SIZE * 9
#define FICKLE_START_Y PIXEL_SIZE * 9

class FickleUI : public GhostUI{    
    public:
    FickleUI();
};

#define STUPID_START_X PIXEL_SIZE * 11
#define STUPID_START_Y PIXEL_SIZE * 9

class StupidUI : public GhostUI{    
    public:
    StupidUI();
};




