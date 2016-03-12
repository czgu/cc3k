#ifndef _FLOOR_H
#define _FLOOR_H

#include "boardDisplay.h"
#include "tile.h"
#include "npc.h"
#include "coord.h"
#include "stairs.h"
#include "potion.h"
#include "item.h"

#include <vector>

class Floor
{
    const int ROW;
    const int COL;
    Tile** theGrid;
    bool nextFloor;
    std::vector<NPC*> enemy;
    std::vector<Item*> item;
    Stairs* stair;
  public:
    Floor(int row, int col, Terrain** terrain);
    ~Floor();
    void setNPC(NPC *s);
    void setStairs(Stairs* s);
    void setItem(Item* i);
    Tile* getTile(Coord p);
    void draw(BoardDisplay& display);
    void update();
    bool levelDone();
    void addNeighbour(int r, int c);
    int enemySize();
    int itemSize();
};

#endif
