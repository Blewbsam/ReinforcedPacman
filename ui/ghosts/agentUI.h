

#ifndef AGENTUI
#define AGENTUI

#include "../../game/globals.h"
#include "../../game/game.h"
#include <SFML/Graphics.hpp>

#define FRAME_SIZE 16


class AgentUI {
protected:
    GameState * gs;
    sf::Vector2f SFposition;
    sf::Clock animationClock;
    int frame;
    float animationSpeed;

public:
    sf::Shape * graphic;
    sf::Sprite * sprite;
    sf::Texture * texture;
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
    virtual void setPositionForRendering();
    virtual void setOrientationForRendering();
    // conersts Vector2f SFPosition to Position struct
    Position getIndexedPosition();
    // setter for SFPosition
    void setSFPosition(Position pos);

    void scaleSprite();

    // sprite dereference getter
    sf::Sprite getSprite();
};





#endif