//
// Created by storm on 23/04/16.
//

#include "underkek.h"

const int   Underkek::hudCombat()
{
    //Player GUI elems
    this->_graphicHandler->draw(this->_namePlayer);
    this->_graphicHandler->draw(this->_levelPlayer);
    this->_graphicHandler->draw(this->_hpText);
    this->_graphicHandler->draw(this->_redBar);
    this->_graphicHandler->draw(this->_yellowBar);
    this->_graphicHandler->draw(this->_hpNumbers);

    //Buttons elems
    if (this->_inSelection == 2)
        this->_graphicHandler->draw(*this->_mediaHandler->getSprite("fight_button_selected"));
    else
        this->_graphicHandler->draw(*this->_mediaHandler->getSprite("fight_button_unselected"));
    if (this->_inSelection == 3)
        this->_graphicHandler->draw(*this->_mediaHandler->getSprite("act_button_selected"));
    else
        this->_graphicHandler->draw(*this->_mediaHandler->getSprite("act_button_unselected"));
    if (this->_inSelection == 4)
        this->_graphicHandler->draw(*this->_mediaHandler->getSprite("item_button_selected"));
    else
        this->_graphicHandler->draw(*this->_mediaHandler->getSprite("item_button_unselected"));
    if (this->_inSelection == 5)
        this->_graphicHandler->draw(*this->_mediaHandler->getSprite("mercy_button_selected"));
    else
        this->_graphicHandler->draw(*this->_mediaHandler->getSprite("mercy_button_unselected"));
    return (0);
}

const int   Underkek::inCombatMovements()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        this->_graphicHandler->moveLivingEntityBody(this->_graphicHandler->getPlayer(), LivingEntity::Direction::LEFT);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        this->_graphicHandler->moveLivingEntityBody(this->_graphicHandler->getPlayer(), LivingEntity::Direction::RIGHT);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        this->_graphicHandler->moveLivingEntityBody(this->_graphicHandler->getPlayer(), LivingEntity::Direction::UP);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        this->_graphicHandler->moveLivingEntityBody(this->_graphicHandler->getPlayer(), LivingEntity::Direction::DOWN);
}

const int   Underkek::inHudCombatMovements()
{
    if (this->_graphicHandler->eventTriggered(sf::Event::KeyReleased, sf::Keyboard::Left)) {
        this->_inSelection = this->_inSelection > 2 ? this->_inSelection - 1 : 5;
        this->_mediaHandler->getSound("tic_dialog")->play();
    }
    else if (this->_graphicHandler->eventTriggered(sf::Event::KeyReleased, sf::Keyboard::Right)) {
        this->_inSelection = this->_inSelection < 5 ? this->_inSelection + 1 : 2;
        this->_mediaHandler->getSound("tic_dialog")->play();
    }
}

const int   Underkek::combat()
{
    this->_graphicHandler->getPlayer()->setSpeed(2.5);
    if (this->_graphicHandler->getPlayer()->getActive() && this->_inCombat)
    {
        this->inCombatMovements();
    }

    this->_graphicHandler->drawPolygonFromFixtures(this->_physicsHandler->getBody("combat_box")->GetFixtureList());

    //Speech dialog box
    if (this->_stateDialogBox == 3 || this->_stateDialogBox == 2)
        this->_stateDialogBox = this->_graphicHandler->getSpeechSoundHandler()->textToSpeech(this->_empty, this->_dialogBox, this->_mediaHandler->getSound("tic_dialog"));
    this->_graphicHandler->draw(this->_dialogBox);

    //Hud combat
    if (this->_inSelection)
        this->hudCombat();

    //Heart
    if (this->_graphicHandler->getPlayer()->getActive() && this->_inCombat)
    {
        this->_graphicHandler->getPlayer()->updateBody();
        this->_graphicHandler->draw(*this->_graphicHandler->getPlayer()->getBodySprite());
    }
    return (0);
}