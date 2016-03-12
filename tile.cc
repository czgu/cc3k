#include "tile.h"
#include "object.h"
#include "character.h"
#include "playerImpl.h"

#include <iostream>
#include <assert.h>

Tile::Tile() :
    contains( 0 ), nNeighbours( 0 )
{
}

Tile::Tile( Terrain type ) :
    terrain( type ), contains( 0 ), nNeighbours( 0 )
{
}

Tile::~Tile()
{
}

void Tile::setTerrain( Terrain type )
{
    terrain = type;
}


void Tile::addNeighbour( Tile* neigh )
{
    assert( neigh );
    neighbours[nNeighbours] = neigh;
    ++nNeighbours;
}

void Tile::notifyEnemies( PlayerImpl& charac )
{
    for( int i = 0 ; i < nNeighbours ; ++i )
        neighbours[i]->notifyEnemy( charac );
}

void Tile::notifyEnemy( PlayerImpl& charac )
{
    if( contains )
        contains->notify( charac );
}

bool Tile::isPassable( const Character& who ) const
{
    if( terrain == SPOT )   // normal space
    {
        if( contains )  return contains->isPassable( who );
        return true;
    }
    else if( terrain < 3 )  // empty or wall
        return false;
    else                    // door or hallway
        return who.isPlayer();
}

bool Tile::hasSomethingOn() const
{
    if( contains ) 
        return true;
    return false;
}

Object* Tile::replaceObject( Object* newObj )
{
    Object* old = contains;
    contains = newObj;
    return old;
}


Object* Tile::getObject()
{
    return contains;
}


void Tile::removeObject()
{
    contains = NULL;
}


char Tile::draw() const
{
    if( contains )  return contains->draw();

    switch( terrain )
    {
        case EMPTY :
            return ' ';
        case WALLV :
            return '|';
        case WALLH :
            return '-';
        case HALL :
            return '#';
        case DOOR :
            return '+';
        case SPOT :
            return '.';
    }
    return '!';
}

Tile* Tile::getNeighbour(int i)
{
    if (i < 0 || i >= nNeighbours)  return NULL; 
    return neighbours[i]; 
}

bool Tile::isGeneratable()
{
    if ( !contains && terrain == SPOT ) return true;
    return false;
}
