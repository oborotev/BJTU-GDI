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
private:
    GraphicHandler *_graphicHandler;
    MediaHandler   *_mediaHandler;
    TilesetHandler *_tilesetHandler;
};

#endif //UNDERKEK_UNDERKEK_H
