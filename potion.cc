#include "potion.h"

#include "playerImpl.h"
#include "messageDisplay.h"

#include <sstream>
#include <cstdlib>
#include <assert.h>

PotionKnowledge::PotionKnowledge() :
    seenRH( false ),
    seenBA( false ),
    seenBD( false ),
    seenPH( false ),
    seenWA( false ),
    seenWD( false )
{
}

PotionKnowledge* Potion::usage = 0;

void Potion::cleanup( void )
{
    delete usage;
}

Potion::Potion( PotionEffect type, int value ) :
    Item( value ), type( type )
{
    switch( type )
    {
        case HEALTH :
            name = std::string( "elixir of " );
            name += ( value > 0 )? "health" : "venom";
            break;
        case ATTACK :
            name = std::string( "blade " );
            name += ( value > 0 )? "oil" : "rust";
            break;
        case DEFENSE :
            name += ( value > 0 )? "potion of harder skin" : "acid";
            break;
        default :
            name = "unknown";
    }
    // PotionKnowledge not yet initialized
    if( !usage )
    {
        usage = new PotionKnowledge();
        atexit( cleanup );
    }
}

void Potion::use()
{
    switch( type )
    {
        case HEALTH :
            if( value > 0 )
                usage->seenRH = true;
            else
                usage->seenPH = true;
            break;
        
        case ATTACK :
            if( value > 0 )
                usage->seenBA = true;
            else
                usage->seenWA = true;
            break;

        case DEFENSE :
            if( value > 0 )
                usage->seenBD = true;
            else
                usage->seenWD = true;
            break;
        default :
            assert( 0 );
    }  
}

bool Potion::getUsedBy( PlayerImpl& player )
{
    assert( value != 0 );
    use();
    player.pickUp( *this );
    
    (*display) << "a " << name << ". ";
    value = 0;
    
    return true;
    //detach();
}

PotionEffect Potion::getPotionEffect() const
{
    return type;
}

namespace
{
    using namespace std;
    
    string intToString( int num )
    {
        ostringstream ss;
        ss << num;
        return ss.str();
    }
}

void Potion::notify( PlayerImpl& player )
{
    using namespace std;

    Item::notify( player );

    string msg( "an unknown potion" );    
    if( HEALTH == type )
    {
        if( (usage->seenRH && value > 0) 
            || (usage->seenPH && value < 0) )
            msg = name + string( " (" )
                  + intToString( value ) 
                  + string( "HP)" );
    }
    else if( ATTACK == type )
    {
        if( (usage->seenBA && value > 0) 
            || (usage->seenWA && value < 0) )
            msg = name + string( " (" )
                  + intToString( value ) 
                  + string( "ATK)" );
    }
    else if( DEFENSE == type )
    {
        if( (usage->seenBD && value > 0) 
            || (usage->seenWD && value < 0) )
            msg = name + string( " (" )
                  + intToString( value ) + 
                  string( "DEF)" );
    }
    (*display) << msg << ". ";
}

char Potion::draw() const
{
    return 'P';
}

bool Potion::isPassable( const Character& who ) const
{
    return false;
}
