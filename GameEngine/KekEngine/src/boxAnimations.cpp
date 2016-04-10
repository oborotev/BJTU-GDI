//
// Created by storm on 10/04/16.
//

# include "boxAnimations.h"

BoxAnimations::BoxAnimations(const sfx::FrameClock *clock)
{
    this->_clock = clock;
}

void BoxAnimations::registerNewAnimation(b2Fixture *fixtures, const BoxAnimations::ANIMATIONS &animationType, const sf::IntRect &newSize, const float &newAngle)
{
    return ;
}