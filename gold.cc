#include "gold.h"

#include "character.h"
#include "playerImpl.h"

#include "messageDisplay.h"

#include <assert.h>

Gold::Gold( int value ) :
    Item( value )
{
}

char Gold::draw() const
{
    return 'G';
}

bool Gold::isPassable( const Character& who ) const
{
    return who.isPlayer();
}

bool Gold::getUsedBy( PlayerImpl& player )
{
    assert( value > 0 );
    player.pickUp( *this );
    
    value = 0;
    return true;
    //detach();
}

void Gold::notify( PlayerImpl& player )
{
    Item::notify( player );
    (*display) << "a gold pile ($";
    (*display) << value << "). ";
}
