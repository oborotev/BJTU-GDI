//
// Created by storm on 26/03/16.
//

#include "underkek.h"

Underkek::~Underkek() {
    delete this->_graphicHandler;
}

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
    this->playerInit();
    this->_tilesetHandler->init(this->_mediaHandler->getTexture("map_tileset"), sf::Vector2u(32, 32), "../media/maps/base", 0, 0, _tiledef.data());
    if (this->_graphicHandler->init()) {
        std::cout << "There was a problem with the graphical initialization" << std::endl;
        return 1;
    }
    this->_physicsHandler = this->_graphicHandler->getPhysicsHandler();
    this->initCombatMode();
    return (0);
}

void Underkek::drawPolygon(b2Fixture*  fixtures, int32 vertexCount)
{
    for (b2Fixture* f = fixtures; f; f = f->GetNext())
    {
        sf::ConvexShape polygon;
        polygon.setPointCount(4);
        b2PolygonShape* polygonShape = (b2PolygonShape*)f->GetShape();
        for (int i=0; i < polygonShape->GetVertexCount(); i++)
        {
            //std::cout << i << std::endl;
            b2Vec2 vertex = polygonShape->GetVertex(i);
            polygon.setPoint(i, sf::Vector2f(vertex.x*RATIO, vertex.y*RATIO));
            std::cout << vertex.x*RATIO << std::endl;
        }
        polygon.setOutlineThickness(1.0f);
        polygon.setFillColor(sf::Color::White);
        this->_graphicHandler->draw(polygon);
    }
}

const int Underkek::initCombatMode()
{
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_staticBody;
    myBodyDef.position.Set(0, 0);
    this->_physicsHandler->registerNewBody(this->_physicsHandler->getWorld()->CreateBody(&myBodyDef), "combat_box");
    //shape definition
    b2PolygonShape polygonShape;
    //fixture definition
    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &polygonShape;
    //add four walls to the static body
    polygonShape.SetAsBox(92/RATIO, 2.5/RATIO, b2Vec2(0, 0), 0);//ground
    this->_physicsHandler->getBody("combat_box")->CreateFixture(&myFixtureDef);
    polygonShape.SetAsBox(92/RATIO, 2.5/RATIO, b2Vec2(0, 6), 0);//ceiling
    this->_physicsHandler->getBody("combat_box")->CreateFixture(&myFixtureDef);
    polygonShape.SetAsBox(2.5/RATIO, 92/RATIO, b2Vec2(-3, 3), 0);//left wall
    this->_physicsHandler->getBody("combat_box")->CreateFixture(&myFixtureDef);
    polygonShape.SetAsBox(2.5/RATIO, 92/RATIO, b2Vec2(3, 3), 0);//right wall
    this->_physicsHandler->getBody("combat_box")->CreateFixture(&myFixtureDef);
}

const int        Underkek::wanderlust()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        this->_graphicHandler->moveLivingEntity(this->_graphicHandler->getPlayer(), LivingEntity::Direction::LEFT, true, true);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        this->_graphicHandler->moveLivingEntity(this->_graphicHandler->getPlayer(), LivingEntity::Direction::RIGHT, true, true);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        this->_graphicHandler->moveLivingEntity(this->_graphicHandler->getPlayer(), LivingEntity::Direction::UP, true, true);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        this->_graphicHandler->moveLivingEntity(this->_graphicHandler->getPlayer(), LivingEntity::Direction::DOWN, true, true);
    this->_graphicHandler->drawBaseMap();
    this->_graphicHandler->getPlayer()->update(this->_graphicHandler->getClock()->getLastFrameTime());
    this->_graphicHandler->draw(*this->_graphicHandler->getPlayer()->getAnimation());
    return (0);
}

const int   Underkek::start() {
    this->_graphicHandler->launch();
    while (this->_graphicHandler->getIsAlive())
    {
        while (this->_graphicHandler->pollEvent())
            if (this->_graphicHandler->eventTriggered(sf::Event::Closed))
                this->_graphicHandler->terminate();
        if (this->_graphicHandler->getIsAlive()) {
            if (!this->_combatMode)
                this->drawPolygon(this->_physicsHandler->getBody("combat_box")->GetFixtureList(),
                                  0);//this->wanderlust();
            this->_graphicHandler->loop();
        }
    }
    return (0);
}