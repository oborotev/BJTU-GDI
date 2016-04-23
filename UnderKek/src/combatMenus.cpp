//
// Created by storm on 23/04/16.
//

# include "underkek.h"

const int   Underkek::inHudCombatMovements()
{
    bool    triggered = false;

    if (this->_graphicHandler->eventTriggered(sf::Event::KeyReleased, sf::Keyboard::Left)) {
        this->_inSelection = this->_inSelection > 2 ? this->_inSelection - 1 : 5;
        this->_mediaHandler->getSound("select_hud_combat")->play();
        triggered = true;
    }
    else if (this->_graphicHandler->eventTriggered(sf::Event::KeyReleased, sf::Keyboard::Right)) {
        this->_inSelection = this->_inSelection < 5 ? this->_inSelection + 1 : 2;
        this->_mediaHandler->getSound("select_hud_combat")->play();
        triggered = true;
    }
    else if (this->_graphicHandler->eventTriggered(sf::Event::KeyReleased, sf::Keyboard::Return) && this->_inSelection > 1)
    {
        if (this->_inSelection == 3)
        {
            this->_inSelection = 7;
            this->_stateActMenu = 0;
        }
        this->_mediaHandler->getSound("select_hud_combat")->play();
    }
    if (triggered)
        this->_graphicHandler->getPlayer()->getBody()->SetTransform(b2Vec2(145 + (215 * (this->_inSelection - 2)), 685), this->_graphicHandler->getPlayer()->getBody()->GetAngle());
}

const int   Underkek::inActMenuMovements()
{
    if (this->_graphicHandler->eventTriggered(sf::Event::KeyReleased, sf::Keyboard::Return))
    {
        this->_inSelection = 10;
        this->_graphicHandler->getBoxAnimationsHandler()->registerNewAnimation("combat_standard", this->_physicsHandler->getBody("combat_box"), BoxAnimations::SIZE_CHANGE,
                                                                               this->_sizeDialogBox, this->_positionDialogBox,
                                                                               this->_sizeCombatBox, this->_positionCombatBox,
                                                                               this->_physicsHandler->getBody("combat_box")->GetFixtureList()->GetBody()->GetAngle(), 8);
        this->_graphicHandler->getPlayer()->getBody()->SetTransform(b2Vec2(512, 500), this->_graphicHandler->getPlayer()->getBody()->GetAngle());
        this->_mediaHandler->getSound("select_hud_combat")->play();
    }
}

const int   Underkek::actMenu()
{
    int     x = 200;
    int     y = 425;
    int     yOffset = 50;
    int     i=0;

    for (std::vector<sf::Text>::iterator it= this->_actChoices.begin(); it != this->_actChoices.end(); it++)
    {
        if (i == this->_stateActMenu)
            this->_graphicHandler->getPlayer()->getBody()->SetTransform(b2Vec2(x - 30, y + 25 + (yOffset * i)), this->_graphicHandler->getPlayer()->getBody()->GetAngle());
        it->setPosition(x, y + yOffset*i);
        this->_graphicHandler->draw(*it);
        i++;
    }
}