
#ifndef GHOSTUI
#define GHOSTUI


#include "../../game/game.h"
#include <SFML/Graphics.hpp>
#include "../../game/globals.h"
#include "agentUI.h"
#include "../globalsUI.h"

class GhostUI : public AgentUI {
    protected:
        Direction ghostDir;
        GhostType ghostType;
        sf::Sprite * face;
        sf::Color defaultColor;
    public:
        GhostUI(GameState * gameState, sf::Vector2f pos, sf::Color defaultColor, GhostType type);
        
        sf::Sprite getFace();
        
        // Specifications similar to pacmanUI
        virtual void move() override;

        // moves Ghost to dir by set_size
        void move(Direction dir,double step_size);

        // gets speed of ghost given type and speed
        double getGhostSpeed(GhostType type, GhostState state);

        void setOrientationForRendering() override;

        void render(GhostState state, Direction ghostDir);
        void setBodyColorForRendering(GhostState state);
        void setFacePositionForRendering();
        void setFaceOrientationForRendering(GhostState state, Direction ghostDir);


        void nextFrame();
        int getRowIndex(Direction ghostDir);
};


#endif