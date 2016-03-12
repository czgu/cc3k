#include "hoard.h"

#include "character.h"
#include "npc.h"

#include <assert.h>

Hoard::Hoard( int value ,NPC* dragon ) :
    Gold( value ), dragon( dragon )
{
    assert( dragon );
}

Hoard::~Hoard()
{
}

bool Hoard::getUsedBy( PlayerImpl& player )
{
    if( dragon->isAlive() )
        return false;
    return Gold::getUsedBy( player );
}

bool Hoard::isPassable( const Character& who ) const
{
    if( dragon->isAlive() )
        return false;
    return Gold::isPassable( who );
}

void Hoard::notify( PlayerImpl& player )
{
    Gold::notify( player );
    if( dragon->isAlive() )
        dragon->notify( player );
}
