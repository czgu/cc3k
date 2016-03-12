#ifndef _GAMESESSION_H
#define _GAMESESSION_H

#include "floor.h"
#include "boardDisplay.h"
#include "mapGenerator.h"
#include "player.h"
#include "inputHandler.h"
#include "statsCollector.h"
#include "action.h"
#include "character.h"
#include "messageDisplay.h"
#include "listener.h"

#include <iostream>
#include <vector>

class GameSession
{
    Action *action;    
    Floor* currFloor;
    BoardDisplay* mapDisplay;
    MessageDisplay* message;
    MapGenerator* makeMap;    
    int currentLevel;
    Player* p; 
    InputHandler* in;
    StatsCollector* stats;
    int quitStatus;
    std::vector<int> potionSetting;
    std::vector<Tuple> goldSetting;
    int mapMode;
    Listener* map;
  public:
    int run(int &score);
    GameSession(int row, int col,int mode, char* fname);
    ~GameSession();
  private:
    bool isGameDone();
    void step();
    void startNewLevel();
    void updateDisplay();
    std::string updatePlayerInfo();
};

#endif
