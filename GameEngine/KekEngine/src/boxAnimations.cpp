//
// Created by storm on 10/04/16.
//

# include "boxAnimations.h"
# include <iostream>

BoxAnimations::BoxAnimations(const sfx::FrameClock *clock)
{
    this->_clock = clock;
}

void BoxAnimations::init()
{
    this->_isAlive = true;
    this->_thread = new sf::Thread(&BoxAnimations::animationsHandler, this);
}

void BoxAnimations::registerNewAnimation(b2Fixture *fixtures, const BoxAnimations::ANIMATIONS &animationType,
                                         const sf::IntRect &newSize, const float &newAngle, const float &speed, const sf::Time &duration)
{
    //this->_threadPool.push_back(new sf::Thread(std::bind(&sizeChanger, this, this->_clock, fixtures, animationType, newSize, this->_threadPool.size(), speed)));
    //this->_threadPool.back()->launch();
    return ;
}

void BoxAnimations::animationsHandler()
{
    while (this->_isAlive)
    {
        if (this->_animations.size())
            std::cout << "There is an animation" << std::endl;
    }
}

void BoxAnimations::terminate()
{
    this->_mutex.lock();
    this->_isAlive = false;
    this->_mutex.unlock();
    this->_thread->wait();
    this->_thread->terminate();
    delete this->_thread;
}