#ifndef _OBJECT_H
#define _OBJECT_H

#include "coord.h"

class Tile;
class Character;
class PlayerImpl;
class MessageDisplay;

class Object
{
    Coord coords;  // XY coordinates

    protected:
    Tile* isOn;
    static MessageDisplay* display;

    public:
    virtual ~Object();

    static void setMessageDisplay( MessageDisplay* );
    void setLocation( Coord, Tile* );

    Coord getCoords();
    void setCoords( Coord );

    Tile* getTilePtr();
    Tile& getTile();
    void setTile( Tile* );
    void setTileToNull();
    void detach();

    virtual bool isPassable( const Character& who ) const = 0;
    virtual char draw() const = 0;
    virtual void notify( PlayerImpl& ) = 0;
};

#endif
