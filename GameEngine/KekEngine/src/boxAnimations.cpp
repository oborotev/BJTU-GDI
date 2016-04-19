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
    this->_animators.insert(std::make_pair(BoxAnimations::ANIMATIONS::SIZE_CHANGE, &BoxAnimations::sizeChange));
    this->_isAlive = true;
    this->_thread = new sf::Thread(&BoxAnimations::animationsHandler, this);
    this->_thread->launch();
}

void BoxAnimations::registerNewAnimation(b2Fixture *fixtures, const BoxAnimations::ANIMATIONS &animationType,
                                         const sf::IntRect &newSize, const float &newAngle, const float &speed, const sf::Time &duration)
{
    t_animationComponents newComponent;

    newComponent.fixtures = fixtures;
    newComponent.animationType = animationType;
    newComponent.newSize = newSize;
    newComponent.newAngle = newAngle;
    newComponent.speed = speed;
    newComponent.duration = duration;
    this->_mutex.lock();
    this->_animations.emplace_back(newComponent);
    this->_mutex.unlock();
    //this->_threadPool.push_back(new sf::Thread(std::bind(&sizeChanger, this, this->_clock, fixtures, animationType, newSize, this->_threadPool.size(), speed)));
    //this->_threadPool.back()->launch();
    return ;
}

bool BoxAnimations::sizeChange(std::vector<t_animationComponents>::iterator animation)
{
    std::cout << animation->animationType << std::endl;
    return (false);
}

void BoxAnimations::animationsHandler()
{
    while (this->_isAlive)
    {
        for (std::vector<t_animationComponents>::iterator it = this->_animations.begin() ; it != this->_animations.end(); ++it) {
            std::cout << "There is an animation" << std::endl;
            if (this->_animations.size() < 1)
                break ;
            if (!(this->*_animators[it->animationType])(it)) {
                this->_mutex.lock();
                this->_animations.erase(it);
                this->_mutex.unlock();
            }
        }
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