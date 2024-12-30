

#ifndef AGENTUI
#define AGENTUI

#include "../../game/globals.hpp"
#include "../../game/game.hpp"
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
    sf::Sprite * sprite;
    sf::Texture * texture;
    AgentUI(GameState * gameState, sf::Vector2f start);
    ~AgentUI();

    // snap graphic position to nearest valid grid
    void snapToGrid();
    // To be overriden. Move agent in direction recieved from gs
    virtual void move();
    // returns true if graphic is in single pixel sized cell
    bool containedInCell();
    // Sprite position setter
    // also handles teleports  
    virtual void setPositionForRendering();
    // sets direction setter
    virtual void setOrientationForRendering();
    // converts Vector2f SFPosition to Position struct
    Position getIndexedPosition();
    // setter for SFPosition
    void setSFPosition(Position pos);
    // scales sprite to PIXEL_SIZE
    void scaleSprite();

    // sprite dereference getter
    sf::Sprite getSprite();
};





#endif