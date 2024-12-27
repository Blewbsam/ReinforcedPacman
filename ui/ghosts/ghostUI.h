
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
        bool active;
        sf::Sprite * face;
    public:
        GhostUI(GameState * gameState, sf::Vector2f pos);

        sf::RectangleShape getGraphic();
        
        sf::Sprite getFace();
        
        // Specifications similar to pacmanUI
        virtual void move() override;

        void move(Direction dir,int step_size);

        // sets active to true for game to start.
        void awake();

        void setOrientationForRendering() override;

        void render(GhostState state, Direction ghostDir);
        void setFacePositionForRendering();
        void setFaceOrientationForRendering(GhostState state, Direction ghostDir);

        void nextFrame();
        int getRowIndex(Direction ghostDir);
};


#endif