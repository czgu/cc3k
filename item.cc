#include "item.h"

#include "playerImpl.h"
#include "messageDisplay.h"
#include <assert.h>

Item::Item( int value ) :
    value( value )
{
    assert( value != 0 );
}

void Item::notify( PlayerImpl& player )
{
    (*display) << "Player sees ";
}

int Item::getValue() const
{
    return value;
}
