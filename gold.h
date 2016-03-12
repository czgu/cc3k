#ifndef _GOLD_H
#define _GOLD_H

#include "item.h"

class Character;
class PlayerImpl;

class Gold : public Item
{
  public:
    // Virtual functions to implement
    Gold( int value );

    char draw() const;
    bool isPassable( const Character& who ) const;
    void notify( PlayerImpl& );
    bool getUsedBy( PlayerImpl& );
};

#endif
