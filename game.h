#ifndef _GAME_H
#define _GAME_H

#include "gameSession.h"

class Game
{
    GameSession *session;
    int mode;
    char* fname;
  public:
    Game();
    Game(char* fname);
    ~Game();
    void run();    
};

#endif
