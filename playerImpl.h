#ifndef _PLAYERIMPL_H
#define _PLAYERIMPL_H

#include "character.h"
#include "action.h"

struct DefaultStat;
class Tile;
class Item;
class Stairs;
class Potion;
class Gold;
//extern enum Direction;

class PlayerImpl : public Character
{
    int gold;
    int currExp;
    // baseStat
    int currentAtk;
    int currentDef;

    void resetStats();
    void broadcast();

    // actions
    public:
    // cannot create Player without DefaultStat
    PlayerImpl( const DefaultStat* baseStat );
    ~PlayerImpl();

    // Setup methods
    void leaveFloor();
    void setTile( Tile* );

    // Query Methods
    bool isPlayer() const;
    int getGoldValue() const;
    int getDef() const;
    int getAtk() const;
    int getLevel() const;
    int getExp() const;
    // Player class calls these
    bool move( Direction );
    bool attack( Direction );
    bool pickUp( Direction );

    // Action class calls these
    Item* receiveDmg( int dmg );
    void giveDmg( int dmg );
    void pickUp( const Potion& );
    void pickUp( const Gold& );
    void gainExp( int exp );
    
    void notify( PlayerImpl& );    // useless function
};

#endif
