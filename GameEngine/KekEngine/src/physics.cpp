//
// Created by storm on 02/04/16.
//

#include "physics.h"

void  PhysicsHandler::terminate()
{
    delete this->_world;
}

const bool  PhysicsHandler::init(const sf::Vector2f &gravity)
{
    this->_world = new b2World(b2Vec2(gravity.x, gravity.y));
    if (this->_world == nullptr)
        return (false);
    return (true);
}