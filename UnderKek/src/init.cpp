//
// Created by storm on 03/04/16.
//

# include "underkek.h"

const int   Underkek::playerInit()
{
    this->_mediaHandler->addNewTexture("../media/textures/frisk.png", "frisky");
    this->_graphicHandler->initPlayer(200, 200, 20, 2.5, true, sf::seconds(0.2), this->_mediaHandler->getTexture("frisky"));
    //Animation Still
    this->_graphicHandler->getPlayer()->addFrameState(LivingEntity::Direction::STILL, sf::IntRect(0, 0, 38, 57));
    //Animation UP
    this->_graphicHandler->getPlayer()->addFrameState(LivingEntity::Direction::UP, sf::IntRect(48, 68, 38, 57));
    this->_graphicHandler->getPlayer()->addFrameState(LivingEntity::Direction::UP, sf::IntRect(0, 68, 38, 57));
    this->_graphicHandler->getPlayer()->addFrameState(LivingEntity::Direction::UP, sf::IntRect(96, 68, 38, 57));
    this->_graphicHandler->getPlayer()->addFrameState(LivingEntity::Direction::UP, sf::IntRect(0, 68, 38, 57));
    //Animation DOWN
    this->_graphicHandler->getPlayer()->addFrameState(LivingEntity::Direction::DOWN, sf::IntRect(48, 0, 38, 57));
    this->_graphicHandler->getPlayer()->addFrameState(LivingEntity::Direction::DOWN, sf::IntRect(0, 0, 38, 57));
    this->_graphicHandler->getPlayer()->addFrameState(LivingEntity::Direction::DOWN, sf::IntRect(96, 0, 38, 57));
    this->_graphicHandler->getPlayer()->addFrameState(LivingEntity::Direction::DOWN, sf::IntRect(0, 0, 38, 57));
    //Animation RIGHT
    this->_graphicHandler->getPlayer()->addFrameState(LivingEntity::Direction::RIGHT, sf::IntRect(50, 136, 38, 59));
    this->_graphicHandler->getPlayer()->addFrameState(LivingEntity::Direction::RIGHT, sf::IntRect(0, 136, 38, 59));
    this->_graphicHandler->getPlayer()->addFrameState(LivingEntity::Direction::RIGHT, sf::IntRect(50, 136, 38, 59));
    this->_graphicHandler->getPlayer()->addFrameState(LivingEntity::Direction::RIGHT, sf::IntRect(0, 136, 38, 59));
    //Animation LEFT
    this->_graphicHandler->getPlayer()->addFrameState(LivingEntity::Direction::LEFT, sf::IntRect(0, 204, 38, 59));
    this->_graphicHandler->getPlayer()->addFrameState(LivingEntity::Direction::LEFT, sf::IntRect(50, 204, 38, 59));
    this->_graphicHandler->getPlayer()->addFrameState(LivingEntity::Direction::LEFT, sf::IntRect(0, 204, 38, 59));
    this->_graphicHandler->getPlayer()->addFrameState(LivingEntity::Direction::LEFT, sf::IntRect(50, 204, 38, 59));
}

const int   Underkek::init()
{
    this->_combatMode = false;
    _tiledef.fill(TilesetHandler::WALL);
    _tiledef[9] = TilesetHandler::FREE;
    this->_graphicHandler = new GraphicHandler("Underkek", "../media/fonts/DTM-Mono.otf");
    this->_tilesetHandler = this->_graphicHandler->getBaseMap();
    this->_mediaHandler = this->_graphicHandler->getMediaHandler();
    this->_physicsHandler = this->_graphicHandler->getPhysicsHandler();
    this->_mediaHandler->addNewFont("../media/fonts/DTM-Sans.otf", "DTM-Sans");
    this->_mediaHandler->addNewFont("../media/fonts/MonsterFriendFore.otf", "MonsterFriendFore");
    this->_mediaHandler->addNewFont("../media/fonts/Mars_Needs_Cunnilingus.ttf", "ROFLMAO");
    this->_mediaHandler->addNewTexture("../media/textures/tileset.gif", "map_tileset");
    this->_mediaHandler->addNewTexture("../media/textures/heart.png", "soul_heart");
    this->_mediaHandler->addNewSprite(this->_mediaHandler->getTexture("soul_heart"), "player_soul");
    this->_mediaHandler->addNewSound("../media/sounds/tic.wav", "tic_dialog");
    this->playerInit();
    this->_tilesetHandler->init(this->_mediaHandler->getTexture("map_tileset"), sf::Vector2u(32, 32), "../media/maps/base", 0, 0, _tiledef.data());
    if (this->_graphicHandler->init()) {
        std::cout << "There was a problem with the graphical initialization" << std::endl;
        return 1;
    }
    this->_physicsHandler = this->_graphicHandler->getPhysicsHandler();
    this->_graphicHandler->getCamera()->updatePositionCenter(1024/2, 768/2);

    //Player Infos
    this->_playerName = "KEK";
    this->_playerLevel = -1;

    //Player GUI Elems
    this->_namePlayer.setFont(*this->_mediaHandler->getFont("ROFLMAO"));
    this->_namePlayer.setString(this->_playerName);
    this->_namePlayer.setColor(sf::Color::White);
    this->_namePlayer.setCharacterSize(27);
    this->_namePlayer.setPosition(115, 610);
    this->_levelPlayer.setFont(*this->_mediaHandler->getFont("ROFLMAO"));
    this->_levelPlayer.setString("LV ?");
    this->_levelPlayer.setColor(sf::Color::White);
    this->_levelPlayer.setCharacterSize(27);
    this->_levelPlayer.setPosition(280, 610);
    this->_hpText.setFont(*this->_mediaHandler->getFont("ROFLMAO"));
    this->_hpText.setString("HP");
    this->_hpText.setColor(sf::Color::White);
    this->_hpText.setCharacterSize(20);
    this->_hpText.setPosition(420, 617);
    this->_hpNumbers.setFont(*this->_mediaHandler->getFont("ROFLMAO"));
    this->_hpNumbers.setString("20 / 20");
    this->_hpNumbers.setCharacterSize(27);
    this->_hpNumbers.setPosition(530, 610);
    this->initCombatMode();
    return (0);
}

const int Underkek::initCombatMode()
{
    /*HUD*/
    //Buttons
    this->_mediaHandler->addNewTexture("../media/textures/buttons.png", "buttons_combat");

    //Fight unselected
    this->_mediaHandler->addNewSprite(this->_mediaHandler->getTexture("buttons_combat"), "fight_button_unselected", sf::IntRect(0, 0, 114, 46));
    this->_mediaHandler->getSprite("fight_button_unselected")->setPosition(120, 660);
    this->_mediaHandler->getSprite("fight_button_unselected")->setScale(1.25, 1.25);

    //Fight selected
    this->_mediaHandler->addNewSprite(this->_mediaHandler->getTexture("buttons_combat"), "fight_button_selected", sf::IntRect(0, 47, 114, 46));
    this->_mediaHandler->getSprite("fight_button_selected")->setPosition(120, 660);
    this->_mediaHandler->getSprite("fight_button_selected")->setScale(1.25, 1.25);

    //Act unselected
    this->_mediaHandler->addNewSprite(this->_mediaHandler->getTexture("buttons_combat"), "act_button_unselected", sf::IntRect(115, 0, 114, 46));
    this->_mediaHandler->getSprite("act_button_unselected")->setPosition(335, 660);
    this->_mediaHandler->getSprite("act_button_unselected")->setScale(1.25, 1.25);

    //Act selected
    this->_mediaHandler->addNewSprite(this->_mediaHandler->getTexture("buttons_combat"), "act_button_selected", sf::IntRect(115, 47, 114, 46));
    this->_mediaHandler->getSprite("act_button_unselected")->setPosition(335, 660);
    this->_mediaHandler->getSprite("act_button_unselected")->setScale(1.25, 1.25);

    //Item unselected
    this->_mediaHandler->addNewSprite(this->_mediaHandler->getTexture("buttons_combat"), "item_button_unselected", sf::IntRect(230, 0, 114, 46));
    this->_mediaHandler->getSprite("item_button_unselected")->setPosition(550, 660);
    this->_mediaHandler->getSprite("item_button_unselected")->setScale(1.25, 1.25);

    //Item selected
    this->_mediaHandler->addNewSprite(this->_mediaHandler->getTexture("buttons_combat"), "item_button_unselected", sf::IntRect(230, 47, 114, 46));
    this->_mediaHandler->getSprite("item_button_unselected")->setPosition(550, 660);
    this->_mediaHandler->getSprite("item_button_unselected")->setScale(1.25, 1.25);

    //Mercy selected
    this->_mediaHandler->addNewSprite(this->_mediaHandler->getTexture("buttons_combat"), "mercy_button_unselected", sf::IntRect(345, 0, 114, 46));
    this->_mediaHandler->getSprite("mercy_button_unselected")->setPosition(765, 660);
    this->_mediaHandler->getSprite("mercy_button_unselected")->setScale(1.25, 1.25);

    //Mercy selected
    this->_mediaHandler->addNewSprite(this->_mediaHandler->getTexture("buttons_combat"), "mercy_button_selected", sf::IntRect(345, 47, 114, 46));
    this->_mediaHandler->getSprite("mercy_button_selected")->setPosition(765, 660);
    this->_mediaHandler->getSprite("mercy_button_selected")->setScale(1.25, 1.25);

    //Health Bar
    this->_redBar.setSize(sf::Vector2f(40, 30));
    this->_redBar.setPosition(465,615);
    this->_redBar.setFillColor(sf::Color::Red);
    this->_yellowBar.setSize(sf::Vector2f(40, 30));
    this->_yellowBar.setPosition(465,615);
    this->_yellowBar.setFillColor(sf::Color::Yellow);

    /* Combat Box */
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_staticBody;
    myBodyDef.position.Set(0, 0);

    this->_physicsHandler->registerNewBody(this->_physicsHandler->getWorld()->CreateBody(&myBodyDef), "combat_box");
    /*Definition of the boxes properties*/
    //Combat box walls positions
    this->_positionCombatBox.push_back(b2Vec2(1024/2, 400));
    this->_positionCombatBox.push_back(b2Vec2(1024/2, 600));
    this->_positionCombatBox.push_back(b2Vec2(415, 500));
    this->_positionCombatBox.push_back(b2Vec2(610, 500));
    //Combat box walls width and height
    this->_sizeCombatBox.push_back(b2Vec2(100, 2.5));
    this->_sizeCombatBox.push_back(b2Vec2(100, 2.5));
    this->_sizeCombatBox.push_back(b2Vec2(2.5, 102.5));
    this->_sizeCombatBox.push_back(b2Vec2(2.5, 102.5));
    //Dialog box Walls positions
    this->_positionDialogBox.push_back(b2Vec2(510, 400));
    this->_positionDialogBox.push_back(b2Vec2(510, 600));
    this->_positionDialogBox.push_back(b2Vec2(120, 500));
    this->_positionDialogBox.push_back(b2Vec2(904, 500));
    //Dialog box walls width and height
    this->_sizeDialogBox.push_back(b2Vec2(390, 2.5));
    this->_sizeDialogBox.push_back(b2Vec2(390, 2.5));
    this->_sizeDialogBox.push_back(b2Vec2(2.5, 102.5));
    this->_sizeDialogBox.push_back(b2Vec2(2.5, 102.5));

    /* Creation of the physic box */
    //shape definition
    b2PolygonShape polygonShape;
    //fixture definition
    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &polygonShape;
    myFixtureDef.friction = 0;
    //add four walls to the static body
    polygonShape.SetAsBox(this->_sizeDialogBox[0].x, this->_sizeDialogBox[0].y, this->_positionDialogBox[0], 0);//ceiling
    this->_physicsHandler->getBody("combat_box")->CreateFixture(&myFixtureDef);
    polygonShape.SetAsBox(this->_sizeDialogBox[1].x, this->_sizeDialogBox[1].y, this->_positionDialogBox[1], 0);//ground
    this->_physicsHandler->getBody("combat_box")->CreateFixture(&myFixtureDef);
    polygonShape.SetAsBox(this->_sizeDialogBox[2].x, this->_sizeDialogBox[2].y, this->_positionDialogBox[2], 0);//left wall
    this->_physicsHandler->getBody("combat_box")->CreateFixture(&myFixtureDef);
    polygonShape.SetAsBox(this->_sizeDialogBox[3].x, this->_sizeDialogBox[3].y, this->_positionDialogBox[3], 0);//right wall
    this->_physicsHandler->getBody("combat_box")->CreateFixture(&myFixtureDef);

    /* Soul */
    b2BodyDef soulDef;
    soulDef.type = b2_dynamicBody;
    soulDef.position = b2Vec2(1024/2, 500);
    this->_physicsHandler->registerNewBody(this->_physicsHandler->getWorld()->CreateBody(&soulDef), "player_soul");

    b2PolygonShape boxShape;
    boxShape.SetAsBox(9, 9);
    b2FixtureDef soulFixtureDef;
    soulFixtureDef.density = 1.0f;
    soulFixtureDef.friction = 1000.f;
    soulFixtureDef.shape = &boxShape;
    this->_physicsHandler->getBody("player_soul")->CreateFixture(&soulFixtureDef);
    this->_graphicHandler->getPlayer()->setPhysicBody(this->_physicsHandler->getBody("player_soul"), this->_mediaHandler->getSprite("player_soul"));
    this->_graphicHandler->getPlayer()->setXYstandalone(500, 475);
}