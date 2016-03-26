//
// Created by storm on 26/03/16.
//

#include "underkek.h"

Underkek::~Underkek() {
    delete this->_graphicHandler;
}

const int   Underkek::init()
{
    this->_graphicHandler = new GraphicHandler("Underkek", "../media/fonts/DTM-Mono.otf");
    this->_tilesetHandler = this->_graphicHandler->getBaseMap();
    this->_mediaHandler = this->_graphicHandler->getMediaHandler();
    return (0);
}

const int   Underkek::start() {
    if (this->_graphicHandler->init()) {
        std::cout << "There was a problem with the graphical initialization" << std::endl;
        return 1;
    }
    this->_graphicHandler->launch();
    while (this->_graphicHandler->getIsAlive())
    {
        while (this->_graphicHandler->pollEvent())
            if (this->_graphicHandler->eventTriggered(sf::Event::Closed))
                this->_graphicHandler->terminate();
        this->_graphicHandler->loop();
    }
    return (0);
}