//
// Created by storm on 18/03/16.
//

#include "graphicHandler.h"

GraphicHandler::GraphicHandler(const std::string &title, const std::string &mainFontPath, unsigned int modeWidth, unsigned int modeHeight, const bool resizable, const bool cameraDelimited, const sf::IntRect &cameraDelimitation, unsigned int modeBitsPerPixel,
                const bool fixedSize, const bool fpsDebug, const float cameraSpeed)
{
    this->_modeBitsPerPixel = !modeBitsPerPixel ? sf::VideoMode::getDesktopMode().bitsPerPixel : modeBitsPerPixel;
    this->_modeWidth = modeWidth;
    this->_modeHeight = modeHeight;
    this->_fixedSize = fixedSize;
    this->_title = title;
    this->_isAlive = true;
    this->_loop = nullptr;
    this->_mediaHandler = new MediaHandler();
    this->_baseMap = new TilesetHandler();
    this->_mainCamera = new CameraHandler();
    this->_mainFontPath = mainFontPath;
    this->_fpsDebug = fpsDebug;
    this->_cameraSpeed = cameraSpeed;
    this->_cameraDelimitation = cameraDelimitation;
    this->_cameraDelimited = cameraDelimited;
    this->_resizable = resizable;
    this->_keyStates.fill(false);
    this->_cameraOnEntity = NULL;
    this->_playerMoved = false;
    this->_calledToMove = false;
}

GraphicHandler::~GraphicHandler() {
    delete this->_window;
    delete this->_mediaHandler;
    delete this->_baseMap;
    delete this->_clock;
    delete this->_clockHUD;
    delete this->_mainCamera;
    delete this->_speechSoundHandler;
    if (this->_boxAnimationsHandler)
        delete this->_boxAnimationsHandler;
    if (this->_player)
        delete this->_player;
}

TilesetHandler*     GraphicHandler::getBaseMap() const
{
    return (this->_baseMap);
}

MediaHandler*       GraphicHandler::getMediaHandler() const
{
    return (this->_mediaHandler);
}

CameraHandler*      GraphicHandler::getCamera()
{
    return (this->_mainCamera);
}

BoxAnimations* GraphicHandler::getBoxAnimationsHandler() const
{
    return (this->_boxAnimationsHandler);
}

void     GraphicHandler::drawBaseMap() const
{
    this->draw(*this->_baseMap);
}

void     GraphicHandler::draw(const sf::Drawable &drawable) const
{
    if (this->_isAlive)
        this->_window->draw(drawable);
}

const int     GraphicHandler::init(const bool isPhysics, const sf::Vector2f &gravity)
{
    if (_resizable)
        this->_window = new sf::RenderWindow(sf::VideoMode(this->_modeWidth, this->_modeHeight, this->_modeBitsPerPixel), this->_title);
    if (!_resizable)
        this->_window = new sf::RenderWindow(sf::VideoMode(this->_modeWidth, this->_modeHeight, this->_modeBitsPerPixel), this->_title, sf::Style::Close);
    if (this->_mainFontPath != "")
    if (!this->_mainFont.loadFromFile(this->_mainFontPath))
    {
        std::cout << "Couldn't load font from path " << this->_mainFontPath << std::endl;
        return (1);
    }
    this->_clock = new sfx::FrameClock();
    this->_clockHUD = new ClockHUD(*this->_clock, this->_mainFont);
    this->_window->setFramerateLimit(60);
    this->_window->setVerticalSyncEnabled(true);
    this->_mainCamera->init(this->_window->getSize().x, this->_window->getSize().y,sf::FloatRect(0, 0, this->_window->getSize().x, this->_window->getSize().y), this->_cameraDelimited, this->_cameraDelimitation);
    if (this->_player)
    {
        this->_mainCamera->updatePositionCenter(this->_player->getX(), this->_player->getY());
        this->_clockHUD->setPosXY((this->_mainCamera->getCenterX() - (this->_modeWidth / 2)) + 800, (this->_mainCamera->getCenterY() - (this->_modeHeight / 2)) + 600);
    }
    this->_isPhysics = isPhysics;
    if (this->_isPhysics) {
        this->_physics = new PhysicsHandler();
        if (!this->_physics->init(gravity)) {
            std::cout << "Couldn't initialize the physics engine" << std::endl;
            return (1);
        }
    }
    this->_boxAnimationsHandler = new BoxAnimations(this->_clock);
    this->_boxAnimationsHandler->init();
    this->_speechSoundHandler = new SpeechSound(this->_clock);
    this->_window->setView(*this->_mainCamera->getView());
    return (0);
}

void     GraphicHandler::loop()
{
    if (!this->_isAlive)
    {
        this->_window->close();
        return;
    }
    this->_boxAnimationsHandler->animationsHandler();
    if (_fpsDebug) {
        this->_clockHUD->setPosXY((this->_mainCamera->getCenterX() - (this->_modeWidth / 2)) + 800, (this->_mainCamera->getCenterY() - (this->_modeHeight / 2)) + 600);
        this->_window->draw(*this->_clockHUD);
    }
    if (!_playerMoved && _player)
        this->_player->changeDirection(LivingEntity::Direction::STILL);
    _playerMoved = false;
    _calledToMove = false;
    this->_debugEventTriggerOne = false;
    this->_window->setView(*this->_mainCamera->getView());
    this->_window->display();
    this->_window->clear(sf::Color::Black);
    this->_clock->endFrame();
}

bool          GraphicHandler::isKeyDown(const sf::Keyboard::Key &key)
{
    if (this->_event.type == sf::Event::KeyReleased && this->_event.key.code == key)
        this->_keyStates[key] = false;
    if (sf::Keyboard::isKeyPressed(key) && !this->_keyStates[key])
    {
        this->_keyStates[key] = true;
        return (true);
    }
    else if (this->_keyStates[key])
        return (true);
}

void          GraphicHandler::setFpsDebug(const bool &option)
{
    this->_fpsDebug = option;
}

void    GraphicHandler::launch()
{
    //this->_loop->launch();
    this->_isAlive = true;
}

void    GraphicHandler::terminate()
{
    this->_mediaHandler->wipeAll();
    if (this->_isPhysics)
    {
        this->_physics->terminate();
        delete this->_physics;
    }
    this->_boxAnimationsHandler->terminate();
    this->_isAlive = false;
}

const bool      GraphicHandler::pollEvent()
{
    bool        temp;

    this->_clock->beginFrame();
    if (_resizable)
        this->_mainCamera->updateWindowSize(this->_window->getSize().x, this->_window->getSize().y);
    temp = this->_window->pollEvent(this->_event);
    return (temp);
}


const bool      GraphicHandler::eventTriggered(const sf::Event::EventType& eventType, const sf::Keyboard::Key& code)
{
    if (this->_event.type == sf::Event::KeyReleased && this->_event.key.code == sf::Keyboard::F9 && !this->_debugEventTriggerOne)
        this->_fpsDebug = !this->_fpsDebug;
    if (code == sf::Keyboard::KeyCount) {
        if (this->_event.type == eventType)
            return (true);
    }
    else if (this->_event.type == eventType && this->_event.key.code == code)
        return (true);
    this->_debugEventTriggerOne = true;
    return (false);
}

const bool      GraphicHandler::getIsAlive()
{
    return this->_isAlive;
}

void    GraphicHandler::initPlayer(const int &x, const int &y, const int &hp, const float &speed, const bool animated, const sf::Time &animationSpeed, sf::Texture *spriteSheet, const bool focusCamera)
{
    this->_player = new Player(x, y, hp, speed, animated, animationSpeed, spriteSheet);
}

sfx::FrameClock* GraphicHandler::getClock() const
{
    return this->_clock;
}

Player* GraphicHandler::getPlayer() const
{
    return (this->_player);
}

PhysicsHandler* GraphicHandler::getPhysicsHandler() const
{
    return (this->_physics);
}

SpeechSound*    GraphicHandler::getSpeechSoundHandler() const
{
    return (this->_speechSoundHandler);
}

ClockHUD*       GraphicHandler::getClockHUD() const
{
    return (this->_clockHUD);
}