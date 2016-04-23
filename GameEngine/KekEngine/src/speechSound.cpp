//
// Created by storm on 23/04/16.
//

# include "speechSound.h"
# include <iostream>

SpeechSound::SpeechSound(const sfx::FrameClock *clock)
{
    this->_clock = clock;
    this->_begin = false;
}

void SpeechSound::clearText()
{
    this->_begin = false;
}

const int SpeechSound::textToSpeech(std::vector<std::string> &dialogs, sf::Text &textObject, sf::Sound *sound, const sf::Time &delay, const bool fastForward)
{
    if (!_begin) {
        this->_currentDialog = dialogs.begin();
        this->_currentTime = delay;
        this->_temp = this->_currentDialog->c_str()[0];
        this->_begin = true;
    }
    if (_currentDialog == dialogs.end())
        return (0);
    while (this->_currentDialog->compare(this->_temp))
    {
        if (_currentTime < delay)
            _currentTime += this->_clock->getLastFrameTime();
        else
        {
            int i = 0;
            this->_temp += this->_currentDialog->c_str()[this->_temp.size()];
            while (this->_currentDialog->c_str()[this->_temp.size() + i] == ' ') {
                this->_temp += this->_currentDialog->c_str()[this->_temp.size() + i];
                i++;
            }
            textObject.setString(this->_temp);
            sound->play();
            _currentTime = sf::seconds(0);
        }
        return (2);
    }
    _currentDialog++;
    return (1);
}