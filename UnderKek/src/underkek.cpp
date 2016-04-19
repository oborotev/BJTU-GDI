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

const int   Underkek::combat()
{
    this->_graphicHandler->getPlayer()->setSpeed(2.5);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        this->_graphicHandler->getBoxAnimationsHandler()->registerNewAnimation(NULL, BoxAnimations::SIZE_CHANGE, sf::IntRect(0,0,0,0), 0, 1.5);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        this->_graphicHandler->moveLivingEntityBody(this->_graphicHandler->getPlayer(), LivingEntity::Direction::LEFT);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        this->_graphicHandler->moveLivingEntityBody(this->_graphicHandler->getPlayer(), LivingEntity::Direction::RIGHT);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        this->_graphicHandler->moveLivingEntityBody(this->_graphicHandler->getPlayer(), LivingEntity::Direction::UP);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        this->_graphicHandler->moveLivingEntityBody(this->_graphicHandler->getPlayer(), LivingEntity::Direction::DOWN);
    this->_graphicHandler->drawPolygonFromFixtures(this->_physicsHandler->getBody("combat_box")->GetFixtureList());
    this->_graphicHandler->getPlayer()->updateBody();
    this->_graphicHandler->draw(*this->_graphicHandler->getPlayer()->getBodySprite());
    return (0);
}

const int   Underkek::start() {
    this->_graphicHandler->launch();
    while (this->_graphicHandler->getIsAlive())
    {
        while (this->_graphicHandler->pollEvent())
            if (this->_graphicHandler->eventTriggered(sf::Event::Closed))
                this->_graphicHandler->terminate();
        if (this->_graphicHandler->getIsAlive()) {
            this->_physicsHandler->getWorld()->Step(1/60.f, 8, 3);
            this->_graphicHandler->getPlayer()->getBody()->SetLinearVelocity(b2Vec2(0,0));
            if (!this->_combatMode)
                this->combat();//this->wanderlust();
            this->_graphicHandler->loop();
        }
    }
    return (0);
}