#include "npc.h"

#include "defaultStat.h"
#include "action.h" 
#include "item.h"

#include "messageDisplay.h"
#include <assert.h>
#include <iostream>

bool NPC::isMerchantAttacked = false;

NPC::NPC( int level ) :
    Character( level ),
    target(NULL), 
    notifyCount(0), 
    isAttacked( false )
{
}


NPC::NPC( const DefaultStat* baseStat, int level ) :
    Character( baseStat, level ), target(NULL), 
    notifyCount(0), isAttacked( false )
{
    assert( baseStat->shape != '@' );
}

NPC::~NPC()
{
}

void NPC::attack()
{
    assert( target );
    bool hit = action->attack( *this, *target );

    if( !hit )
        (*display) << "The " << baseStat->race 
                   << " missed! ";
}

void NPC::update()
{
    assert( action );
    assert( isAlive() );
   
    // not a dragon
    //std::string dragon( "dragon" );
    //if( getRace().compare( dragon ) )
    if( 'D' != baseStat->shape )
    {
        // engage in combat
        bool isMerchantAngry = ('M' == baseStat->shape 
                                  && isMerchantAttacked )
                                || 'M' != baseStat->shape;
        if( notifyCount > 0 && isMerchantAngry )
        {
            bool ran = false;
            // run away
            if( getHP() < getMaxHP() / 4 )
            {
                assert( target );
                ran = action->runAway( *this, *target );
                if( ran )
                    (*display) << "The " << getRace()
                               << " is running! ";
                else
                    (*display) << "The " << getRace() << " can't run! ";
            }
            if( !ran )
                attack();
        }
        else
        {
            action->move( *this );
        }
        isAttacked = false;
    }
    else    // dragon
    {
        if( notifyCount > 1 || ( isAttacked && target ) )
            attack();
    }
    target = NULL;
    notifyCount = 0;
}


void NPC::notify( PlayerImpl& player )
{
    // TODO: this runs when Character notifies Tile
    // print message to display
    assert( notifyCount < 3 );
    ++notifyCount;
    target = &player;
}

bool NPC::isPlayer() const
{
    return false;
}

Item* NPC::receiveDmg( int dmg )
{
    Item* spoils = Character::receiveDmg( dmg );

    isAttacked = true;
    // if Merchant is attacked
    if( baseStat->race == "merchant" )
        isMerchantAttacked = true;

    (*display) << baseStat->race;
    (*display) << " (" << currentHP << " HP). ";
    return spoils;
}

void NPC::giveDmg( int dmg )
{
    (*display) << "The " << baseStat->race << " deals ";
    (*display) << dmg << " damage to ";
    Character::giveDmg( dmg );
}
