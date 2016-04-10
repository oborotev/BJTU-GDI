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
    this->_mediaHandler->addNewTexture("../media/textures/tileset.gif", "map_tileset");
    this->_mediaHandler->addNewTexture("../media/textures/heart.jpe", "soul_heart");
    this->_mediaHandler->addNewSprite(this->_mediaHandler->getTexture("soul_heart"), "player_soul");
    this->playerInit();
    this->_tilesetHandler->init(this->_mediaHandler->getTexture("map_tileset"), sf::Vector2u(32, 32), "../media/maps/base", 0, 0, _tiledef.data());
    if (this->_graphicHandler->init()) {
        std::cout << "There was a problem with the graphical initialization" << std::endl;
        return 1;
    }
    this->_physicsHandler = this->_graphicHandler->getPhysicsHandler();
    this->_graphicHandler->getCamera()->updatePositionCenter(1024/2, 768/2);
    this->initCombatMode();
    return (0);
}

const int Underkek::initCombatMode()
{
    /* Combat Box */
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_staticBody;
    myBodyDef.position.Set(0, 0);
    myBodyDef.userData = (void *)new sf::Vector2f(1024/2, 500);
    this->_physicsHandler->registerNewBody(this->_physicsHandler->getWorld()->CreateBody(&myBodyDef), "combat_box");
    //shape definition
    b2PolygonShape polygonShape;
    //fixture definition
    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &polygonShape;
    myFixtureDef.friction = 0;
    //add four walls to the static body
    polygonShape.SetAsBox(92, 2.5, b2Vec2(1024/2, 400), 0);//ceiling
    this->_physicsHandler->getBody("combat_box")->CreateFixture(&myFixtureDef);
    polygonShape.SetAsBox(92, 2.5, b2Vec2(1024/2, 600), 0);//ground
    this->_physicsHandler->getBody("combat_box")->CreateFixture(&myFixtureDef);
    polygonShape.SetAsBox(2.5, 102.5, b2Vec2(417, 500), 0);//left wall
    this->_physicsHandler->getBody("combat_box")->CreateFixture(&myFixtureDef);
    polygonShape.SetAsBox(2.5, 102.5, b2Vec2(608, 500), 0);//right wall
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