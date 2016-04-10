//
// Created by storm on 10/04/16.
//

#ifndef GAMEENGINE_BOXANIMATIONS_H
#define GAMEENGINE_BOXANIMATIONS_H

# include <SFML/Graphics.hpp>
# include <Box2D/Box2D.h>
# include "frameClock.h"

class BoxAnimations
{
public:
    enum ANIMATIONS {
        SIZE_CHANGE = 0
    };
public:
    BoxAnimations(const sfx::FrameClock *clock);
    void registerNewAnimation(b2Fixture *fixtures, const BoxAnimations::ANIMATIONS &animationType, const sf::IntRect &newSize, const float &newAngle);
private:
    const sfx::FrameClock *_clock;
};

#endif //GAMEENGINE_BOXANIMATIONS_H
