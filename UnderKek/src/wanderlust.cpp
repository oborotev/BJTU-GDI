//
// Created by storm on 24/04/16.
//

# include "underkek.h"

const int   Underkek::initBeforeWanderlust()
{
    this->_graphicHandler->getPlayer()->setXYstandalone(this->_xPlayerBeforeCombat, this->_yPlayerBeforeCombat);
    this->_combatMode = false;
    this->_graphicHandler->getCamera()->updatePositionCenter(this->_graphicHandler->getPlayer()->getX(), this->_graphicHandler->getPlayer()->getY());
    this->_graphicHandler->getBoxAnimationsHandler()->registerNewAnimation("restore_box", this->_physicsHandler->getBody("combat_box"), BoxAnimations::SIZE_CHANGE,
                                                                           this->_sizeCombatBox, this->_positionCombatBox,
                                                                           this->_sizeDialogBox, this->_positionDialogBox,
                                                                           this->_physicsHandler->getBody("combat_box")->GetFixtureList()->GetBody()->GetAngle(), 9001);
}