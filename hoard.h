#ifndef _HOARD_H
#define _HOARD_H

#include "gold.h"

class Character;
class NPC;
class PlayerImpl;

class Hoard : public Gold
{
    NPC* const dragon;
  public:
    Hoard( int value, NPC* dragon );
    ~Hoard();

    bool getUsedBy( PlayerImpl& );
    bool isPassable( const Character& who ) const;
    void notify( PlayerImpl& );
};

#endif
