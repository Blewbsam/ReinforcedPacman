#include "ghostUI.h"

GhostUI::GhostUI(GameState * gameState, sf::Vector2f pos, sf::Color defaultColor) : AgentUI(gameState,pos,new sf::RectangleShape(sf::Vector2f(PIXEL_SIZE,PIXEL_SIZE))){
    this->ghostDir = IDLE;
    this->active = false;
    this->animationSpeed = 0.1f;
    this->frame = 0;
    this->face = new sf::Sprite();
    this->defaultColor = defaultColor;

    if (!this->texture->loadFromFile("animations/GhostAnimation.png")) {
        std::cerr << "Failed to load Ghost animation texture!" << std::endl;
        return;
    }
    this->sprite->setTexture(*this->texture);
    this->face->setTexture(*this->texture);

}

// Gets which direction to move from gameState and moves in given direction.
void GhostUI::move(){
    // this->gs->
    return;
}

sf::RectangleShape GhostUI::getGraphic() {
    sf::RectangleShape * shape = dynamic_cast<sf::RectangleShape *>(this->graphic);
    return *shape;
}

sf::Sprite GhostUI::getFace() {
    return *this->face;
}

void GhostUI::move(Direction dir,int step_size) {
    switch (dir) {
        case UP:    SFposition.y -= step_size; break;
        case DOWN:  SFposition.y += step_size; break;
        case LEFT:  SFposition.x -= step_size; break;
        case RIGHT: SFposition.x += step_size; break;
        default: break;
    }
}


void GhostUI::render(GhostState state, Direction ghostDir) {
    this->setPositionForRendering();
    this->setOrientationForRendering();
    this->setFacePositionForRendering();
    this->setFaceOrientationForRendering(state,ghostDir);
    this->setBodyColorForRendering(state);
}

void GhostUI::setOrientationForRendering() {
    if (this->animationClock.getElapsedTime().asSeconds() > this->animationSpeed) {
        this->sprite->setTextureRect(sf::IntRect(FRAME_SIZE * this->frame, 0, FRAME_SIZE, FRAME_SIZE));
        this->scaleSprite();
        this->nextFrame();
        this->animationClock.restart();
    }
}

void GhostUI::setBodyColorForRendering(GhostState state) {
    sf::Color frightenedBlue(0, 0, 255); // Pure blue
    if (state == FRIGHTENED) {
        std::cout << "Frightened" << std::endl;
        this->sprite->setColor(frightenedBlue);
    } else {
        this->sprite->setColor(this->defaultColor);
    }
}

int GhostUI::getRowIndex(Direction ghostDir) {
    switch (ghostDir) {
        case RIGHT: return 0;
        case UP: return 1;
        case LEFT: return 2;
        default: return 3;
    }
}

// must be called after rendering Sprite body
void GhostUI::setFacePositionForRendering() {
    this->face->setPosition(this->SFposition.x,this->SFposition.y);
}

void GhostUI::setFaceOrientationForRendering(GhostState state, Direction ghostDir) {
    switch (state)
    {
    case EATEN:
        this->face->setTextureRect(sf::IntRect(FRAME_SIZE * 4, FRAME_SIZE * 1, FRAME_SIZE, FRAME_SIZE));
        break;
    case FRIGHTENED: {
        this->face->setTextureRect(sf::IntRect(FRAME_SIZE * this->getRowIndex(ghostDir), FRAME_SIZE * 2, FRAME_SIZE, FRAME_SIZE));
        break;
    }
    default:
        this->face->setTextureRect(sf::IntRect(FRAME_SIZE * this->getRowIndex(ghostDir), FRAME_SIZE * 1, FRAME_SIZE, FRAME_SIZE));
    }
    // scale face
    int scale = PIXEL_SIZE / FRAME_SIZE;
    this->face->setScale(scale,scale);
}


void GhostUI::awake() {
    this->active = true;
}

void GhostUI::nextFrame() {
    this->frame = (this->frame + 1) % 6;
}
