#ifndef _NPC_H
#define _NPC_H

#include "character.h"

class PlayerImpl;
class Item;

class NPC : public Character
{
    PlayerImpl* target;
    int notifyCount;
    static bool isMerchantAttacked;
    bool isAttacked;
    
    void attack();
    public:
    NPC( int level );
    NPC( const DefaultStat*, int level );
    ~NPC();
    bool isPlayer() const;

    void update();  // NPC will either move or attack
    void notify( PlayerImpl& );

    // Action class methods call these
    Item* receiveDmg( int dmg );
    void giveDmg( int dmg );
};

#endif
