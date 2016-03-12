#ifndef _STAIRS_H
#define _STAIRS_H

#include "object.h"

class Character;
class PlayerImpl;

class Stairs : public Object
{
    bool reached;
  public:
    Stairs();
    ~Stairs();

    bool isReached() const; 
    void reach();

    bool isPassable( const Character& who ) const;
    char draw() const;
    void notify( PlayerImpl& );
};

#endif
