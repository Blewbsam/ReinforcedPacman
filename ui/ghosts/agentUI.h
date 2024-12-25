

#ifndef AGENTUI
#define AGENTUI

#include "../../game/globals.h"
#include "../../game/game.h"
#include <SFML/Graphics.hpp>


class AgentUI {
protected:
    GameState * gs;
    sf::Vector2f SFposition;
public:
    sf::Shape * graphic;
    AgentUI(GameState * gameState, sf::Vector2f start, sf::Shape * shape);
    ~AgentUI();

    // snap graphic position to nearest valid grid
    void snapToGrid();
    // To be overriden. Move agent in direction recieved from gs
    virtual void move();
    // returns true if graphic is in single pixel sized cell
    bool containedInCell();
    // Graphic position setter
    // also handles teleports  
    void setPositionForRendering();
    // conersts Vector2f SFPosition to Position struct
    Position getIndexedPosition();
    // setter for SFPosition
    void setSFPosition(Position pos);
};





#endif