//
// Created by storm on 10/04/16.
//

#ifndef GAMEENGINE_BOXANIMATIONS_H
#define GAMEENGINE_BOXANIMATIONS_H

# include <SFML/Graphics.hpp>
# include <SFML/System.hpp>
# include <Box2D/Box2D.h>
# include "frameClock.h"
# include <vector>

class BoxAnimations
{
public:
    enum ANIMATIONS {
        SIZE_CHANGE = 0
    };
public:
    BoxAnimations(const sfx::FrameClock *clock);
    void init();
    void registerNewAnimation(b2Fixture *fixtures, const BoxAnimations::ANIMATIONS &animationType, const sf::IntRect &newSize, const float &newAngle, const float &speed=1.0, const sf::Time &duration=sf::seconds(0));
    void terminate();
    void animationsHandler();
private:
    typedef struct s_animationComponents
    {
        b2Fixture         *fixtures;
        const BoxAnimations::ANIMATIONS &animationType;
        const sf::IntRect newSize;
        const float       newAngle;
        const float       speed;
        const sf::Time    duration;
    }              t_animationComponents;
    const sfx::FrameClock *_clock;
    sf::Thread  *_thread;
    sf::Mutex   _mutex;
    std::vector<t_animationComponents> _animations;
    bool _isAlive;
};

#endif //GAMEENGINE_BOXANIMATIONS_H
