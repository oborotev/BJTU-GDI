//
// Created by storm on 26/03/16.
//

#ifndef UNDERKEK_UNDERKEK_H
#define UNDERKEK_UNDERKEK_H

# include "graphicHandler.h"

class Underkek
{
public:
    Underkek() {};
    ~Underkek();
    const int   init();
    const int   start();
    const int   playerInit();
    const int   wanderlust();
    const int   combat();
    const int   initCombatMode();
private:
    GraphicHandler *_graphicHandler;
    MediaHandler   *_mediaHandler;
    TilesetHandler *_tilesetHandler;
    PhysicsHandler *_physicsHandler;
    std::array<int, 171> _tiledef;
    bool            _combatMode;
};

#endif //UNDERKEK_UNDERKEK_H
