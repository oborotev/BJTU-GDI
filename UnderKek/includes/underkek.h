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
    const int   hudCombat();
    const int   initCombatMode();
    const int   pollEvents();
    const int   inCombatMovements();
    const int   inHudCombatMovements();
    const int   foeTexts();
    const int   actMenu();
    const int   inActMenuMovements();
    const int   initBeforeCombat();
    const int   initBeforeWanderlust();
private:
    GraphicHandler *_graphicHandler;
    MediaHandler   *_mediaHandler;
    TilesetHandler *_tilesetHandler;
    PhysicsHandler *_physicsHandler;
    std::array<int, 171> _tiledef;
    bool            _combatMode;

    //Combat boxes definitions
    std::vector<b2Vec2> _positionDialogBox;
    std::vector<b2Vec2> _sizeDialogBox;
    std::vector<b2Vec2> _positionCombatBox;
    std::vector<b2Vec2> _sizeCombatBox;

    //Player infos
    std::string     _playerName;
    std::string     _playerLevel;

    //Player GUI Elems
    sf::Text        _namePlayer;
    sf::Text        _levelPlayer;
    sf::Text        _hpText;
    sf::Text        _hpNumbers;
    sf::RectangleShape _redBar;
    sf::RectangleShape _yellowBar;

    /*Dialog Box*/
    sf::Text        _dialogBox;
    sf::Time        _delayText;
    int             _stateDialogBox;
    sf::Text        _foeText;
    //Act menu
    std::vector<sf::Text> _actChoices;
    int             _stateActMenu;

    //Player combat state
    bool            _inCombat;
    int             _inSelection;

    //test
    std::vector<std::string> _empty;

    //x and y position of player before combat
    double          _xPlayerBeforeCombat;
    double          _yPlayerBeforeCombat;
};

#endif //UNDERKEK_UNDERKEK_H
