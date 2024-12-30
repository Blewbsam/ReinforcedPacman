
#include <typeinfo>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include "ghostUI.hpp"
#include "speeds.hpp"


GhostUI::GhostUI(GameState * gameState, sf::Vector2f pos, sf::Color defaultColor, GhostType type) : AgentUI(gameState,pos){
    this->ghostType = type;
    this->animationSpeed = 0.1f;
    this->frame = 0;
    this->face = new sf::Sprite();
    this->defaultColor = defaultColor;

    if (!this->texture->loadFromFile("../ui/animations/GhostAnimation.png")) {
        std::cerr << "Failed to load Ghost animation texture!" << std::endl;
        std::cout << "Current working directory: " << std::__fs::filesystem::current_path() << std::endl;
        return;
    }
    this->sprite->setTexture(*this->texture);
    this->face->setTexture(*this->texture);

}

sf::Sprite GhostUI::getFace() {
    return *this->face;
}

void GhostUI::move(){
    Direction dir = this->gs->getGhostDir(this->ghostType);
    double stepSize = this->getGhostSpeed(this->ghostType,this->gs->getGhostState(this->ghostType));
    this->move(dir,stepSize);
    if (this->containedInCell()) gs->updateGhostPos(this->getIndexedPosition(),this->ghostType);
}

void GhostUI::move(Direction dir,double step_size) {
    switch (dir) {
        case UP:    SFposition.y -= step_size; break;
        case DOWN:  SFposition.y += step_size; break;
        case LEFT:  SFposition.x -= step_size; break;
        case RIGHT: SFposition.x += step_size; break;
        default: break;
    }
}

double GhostUI::getGhostSpeed(GhostType type, GhostState state) {
    if (state == TRANSITION || state == FRIGHTENED) {state = FRIGHTENED;}
    else {state = CHASE;}
    static const std::unordered_map<GhostType, std::unordered_map<GhostState, double>> ghostSpeeds = {
    { CHASER, {{ FRIGHTENED, CHASER_FRIGHTENED_STEP_SIZE },  { CHASE, CHASER_CHASE_STEP_SIZE }} },
    { AMBUSHER, {{ FRIGHTENED, AMBUSHER_FRIGHTENED_STEP_SIZE }, { CHASE, AMBUSHER_CHASE_STEP_SIZE }} },
    { FICKLE, {{ FRIGHTENED, FICKLE_FRIGHTENED_STEP_SIZE }, { CHASE, FICKLE_CHASE_STEP_SIZE }} },
    { STUPID, {{ FRIGHTENED, STUPID_FRIGHTENED_STEP_SIZE },{ CHASE, STUPID_CHASE_STEP_SIZE }} }
    };
    return ghostSpeeds.at(type).at(state);
}

void GhostUI::render(GhostState state, Direction ghostDir) {
    // if direction is new, clip position?
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
    sf::Color opaqueBlack = sf::Color::Black;
    opaqueBlack.a = 0;
    switch (state) {
        case TRANSITION: {
            if (this->sprite->getColor() == frightenedBlue) {
                this->sprite->setColor(sf::Color::White);
            } else {
                this->sprite->setColor(frightenedBlue);
            }
            break;
        }
        case FRIGHTENED: this->sprite->setColor(frightenedBlue); break;
        case EATEN: this->sprite->setColor(opaqueBlack); break;
        default:    this->sprite->setColor(this->defaultColor); break;
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
    this->face->setPosition(this->SFposition.x - PIXEL_SIZE,this->SFposition.y);
}
void GhostUI::setFaceOrientationForRendering(GhostState state, Direction ghostDir) {
    switch (state){
    case EATEN:this->face->setTextureRect(sf::IntRect(FRAME_SIZE * 4, FRAME_SIZE * 1, FRAME_SIZE, FRAME_SIZE));break;
    case TRANSITION:
    case FRIGHTENED: this->face->setTextureRect(sf::IntRect(FRAME_SIZE * this->getRowIndex(ghostDir), FRAME_SIZE * 2, FRAME_SIZE, FRAME_SIZE));break;
    default:
        this->face->setTextureRect(sf::IntRect(FRAME_SIZE * this->getRowIndex(ghostDir), FRAME_SIZE * 1, FRAME_SIZE, FRAME_SIZE));
    }
    float scale = PIXEL_SIZE / FRAME_SIZE;
    this->face->setScale(scale,scale);
}

void GhostUI::nextFrame() {
    this->frame = (this->frame + 1) % 6;
}



// Ghost Subclasses constructors

ChaserUI::ChaserUI(GameState * gameState) : GhostUI(gameState,sf::Vector2f(CHASER_START_X,CHASER_START_Y),sf::Color::Red,CHASER){}


FickleUI::FickleUI(GameState * gameState) : GhostUI(gameState,sf::Vector2f(FICKLE_START_X,FICKLE_START_Y),sf::Color::Cyan,FICKLE){
    this->sprite->setColor(sf::Color::Cyan);
}


sf::Color clydeColor(255, 165, 0);

StupidUI::StupidUI(GameState * gameState) : GhostUI(gameState,sf::Vector2f(STUPID_START_X,STUPID_START_Y),clydeColor,STUPID){}

AmbusherUI::AmbusherUI(GameState * gameState) : GhostUI(gameState,sf::Vector2f(AMBUSHER_START_X,AMBUSHER_START_Y),sf::Color::Magenta,AMBUSHER){    }
