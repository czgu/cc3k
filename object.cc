#include "object.h"
#include "tile.h"
#include "messageDisplay.h"
#include <assert.h>

MessageDisplay* Object::display = NULL;

Object::~Object()
{
}

void Object::setMessageDisplay( MessageDisplay* disp )
{
    assert( disp );
    display = disp;
}

void Object::setLocation( Coord coord, Tile* tile )
{
    setCoords( coord );
    setTile( tile );
}

Coord Object::getCoords()
{
    return coords;
}

void Object::setCoords( Coord xy )
{
    coords = xy;
}

Tile& Object::getTile()
{
    return *isOn;
}

Tile* Object::getTilePtr()
{
    return isOn;
}

void Object::setTileToNull()
{
    isOn = NULL;
}

void Object::setTile( Tile* tile )
{
    assert( tile );

    isOn = tile;
    tile->replaceObject( this );
}

void Object::detach()
{
    if( isOn ) 
        isOn->removeObject();
    isOn = NULL;
}
