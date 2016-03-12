#ifndef _MAPGENERATOR_H
#define _MAPGENERATOR_H

#include <string>
#include <vector>
#include <utility>
#include "coord.h"
#include "floor.h"
#include "listener.h"
#include "tile.h"
#include "player.h"
#include "npc.h"
#include "statsCollector.h"
#include "randomizer.h"
#include "stairs.h"
#include "potion.h"
#include "gold.h"
#include "hoard.h"
class MapGenerator
{
  public:
    Floor* createMap(std::string fname,Player *p, StatsCollector* s, 
                     int currLevel, int enemySize, int potionSize, int goldSize, 
                     std::vector<int>& potionSetting, std::vector<Tuple >& goldSetting);
    Floor* createStaticMap(Listener &in, Player *p, StatsCollector* s,int currLevel, std::vector<int>& potionSetting, std::vector<Tuple >&        goldSetting);
  private:
    Floor* addObjects(Floor* basicFloor,Player *p,std::vector<Coord>* chambers,int roomNum, StatsCollector *s,int currLevel, int enemySize,int potionSize, int goldSize ,std::vector<int>& potionSetting, std::vector<Tuple>& goldSetting);    
    Floor* mapRead(Listener &in,int row,int col, int roomNum ,std::vector<Coord>* chambers);
};

#endif
