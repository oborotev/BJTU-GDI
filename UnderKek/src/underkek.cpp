//
// Created by storm on 26/03/16.
//

#include "underkek.h"

Underkek::~Underkek() {
    delete this->_graphicHandler;
}

const int        Underkek::wanderlust()
{
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

const int   Underkek::start() {
    this->_graphicHandler->launch();
    while (this->_graphicHandler->getIsAlive())
    {
        while (this->_graphicHandler->pollEvent())
            if (this->_graphicHandler->eventTriggered(sf::Event::Closed))
                this->_graphicHandler->terminate();
        if (this->_graphicHandler->getIsAlive()) {
            this->_physicsHandler->getWorld()->Step(1/60.f, 8, 3);
            if (!this->_combatMode)
                this->_graphicHandler->drawPolygonFromFixtures(this->_physicsHandler->getBody("combat_box")->GetFixtureList());//this->wanderlust();
            this->_mediaHandler->getSprite("player_soul")->setPosition(this->_physicsHandler->getBody("player_soul")->GetPosition().x, this->_physicsHandler->getBody("player_soul")->GetPosition().y);
            this->_mediaHandler->getSprite("player_soul")->setRotation(180/b2_pi * this->_physicsHandler->getBody("player_soul")->GetAngle());
            this->_graphicHandler->draw(*this->_mediaHandler->getSprite("player_soul"));
            this->_graphicHandler->loop();
        }
    }
    return (0);
}