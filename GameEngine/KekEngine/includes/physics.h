//
// Created by storm on 02/04/16.
//

#ifndef GAMEENGINE_PHYSICS_H
#define GAMEENGINE_PHYSICS_H

# include <SFML/Graphics.hpp>
# include <Box2D/Box2D.h>

class PhysicsHandler
{
public:
    const bool init(const sf::Vector2f &gravity);
    void terminate();
private:
    b2World *_world;
};

#endif //GAMEENGINE_PHYSICS_H
