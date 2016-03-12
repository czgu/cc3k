#include "stairs.h"

#include "character.h"
#include "playerImpl.h"

#include <assert.h>

Stairs::Stairs() :
    reached( false )
{
}

Stairs::~Stairs()
{
}

void Stairs::reach()
{
    assert( !reached );
    reached = true;
}

bool Stairs::isReached() const
{
    return reached;
}

bool Stairs::isPassable( const Character& who ) const
{
    return who.isPlayer();
}

char Stairs::draw() const
{
    return '\\';
}

void Stairs::notify( PlayerImpl& player )
{
    // TODO: print some meaningful message to display
}
