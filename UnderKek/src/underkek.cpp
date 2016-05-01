//
// Created by storm on 26/03/16.
//

#include "underkek.h"

Underkek::~Underkek() {
    delete this->_graphicHandler;
}

const int        Underkek::wanderlust()
{
    this->_graphicHandler->getPlayer()->setSpeed(2.5);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        this->_graphicHandler->moveLivingEntity(this->_graphicHandler->getPlayer(), LivingEntity::Direction::LEFT, true, true);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        this->_graphicHandler->moveLivingEntity(this->_graphicHandler->getPlayer(), LivingEntity::Direction::RIGHT, true, true);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        this->_graphicHandler->moveLivingEntity(this->_graphicHandler->getPlayer(), LivingEntity::Direction::UP, true, true);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        this->_graphicHandler->moveLivingEntity(this->_graphicHandler->getPlayer(), LivingEntity::Direction::DOWN, true, true);
    this->_graphicHandler->drawBaseMap();
    this->_graphicHandler->getPlayer()->update(this->_graphicHandler->getClock()->getLastFrameTime());
    this->_graphicHandler->draw(*this->_graphicHandler->getPlayer()->getAnimation());
    return (0);
}

const int   Underkek::pollEvents()
{
    if (this->_inSelection > 1 && this->_inSelection < 6)
        this->inHudCombatMovements();
    else if (this->_inSelection == 7)
        this->inActMenuMovements();
    if (this->_graphicHandler->eventTriggered(sf::Event::KeyReleased, sf::Keyboard::K))
    {
        if (!this->_combatMode)
            this->initBeforeCombat();
        else
            this->initBeforeWanderlust();
    }
    if (this->_combatMode)
    {
        if (this->_graphicHandler->eventTriggered(sf::Event::KeyReleased, sf::Keyboard::Return) && this->_inSelection == 1)
        {
            if (this->_stateDialogBox == 2) {
                this->_stateDialogBox = this->_graphicHandler->getSpeechSoundHandler()->textToSpeech(this->_empty,
                                                                                                     this->_dialogBox,
                                                                                                     this->_mediaHandler->getSound(
                                                                                                             "tic_dialog"), true);
                this->_stateDialogBox = 3;
            }
            else if (this->_stateDialogBox == 1)
                this->_stateDialogBox = 2;
            else if (this->_stateDialogBox == 0)
            {
                this->_graphicHandler->getSpeechSoundHandler()->clearText();
                this->_inSelection = 2;
                this->_graphicHandler->getPlayer()->getBody()->SetTransform(b2Vec2(145, 685), this->_graphicHandler->getPlayer()->getBody()->GetAngle());
            }
        }
    }
}

const int   Underkek::start() {
    this->_graphicHandler->launch();
    while (this->_graphicHandler->getIsAlive())
    {
        while (this->_graphicHandler->pollEvent()) {
            if (this->_graphicHandler->eventTriggered(sf::Event::Closed))
                this->_graphicHandler->terminate();
            this->pollEvents();
        }
        if (this->_graphicHandler->getIsAlive()) {
            this->_physicsHandler->getWorld()->Step(1/60.f, 8, 3);
            this->_graphicHandler->getPlayer()->getBody()->SetLinearVelocity(b2Vec2(0,0));
            if (this->_combatMode)
                this->combat();
            else
                this->wanderlust();
            this->_graphicHandler->loop();
        }
    }
    return (0);
}