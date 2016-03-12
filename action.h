#ifndef _ACTION_H
#define _ACTION_H

class Object;
class Character;
class NPC;
class PlayerImpl;

class Floor;
class Tile;

struct Coord;

/*

 3  2  1
  \ | /
4-------0
  / | \
 5  6  7

*/


enum Direction
{
    EAST = 0,
    NORTHEAST,
    NORTH,
    NORTHWEST,
    WEST,
    SOUTHWEST,
    SOUTH,
    SOUTHEAST
};

class Action
{
    Floor* floor;

    Tile* getValidTile( Character&, Direction, Coord& );
    Object* moveChar( Character&, Tile&, Coord );
    bool moveChar( Character&, Direction, Object*& );

    public:
    Action();
    ~Action();

    void changeFloor( Floor* );

    bool move( NPC& );
    bool runAway( NPC& enemy, PlayerImpl& player );
    bool move( PlayerImpl&, Direction );
    
    bool attack( PlayerImpl&, Direction );
    bool attack( NPC&, PlayerImpl& );

    bool pickUp( PlayerImpl&, Direction );
};

#endif
