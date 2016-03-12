#include "character.h"
#include "defaultStat.h"
#include "action.h"
#include "messageDisplay.h"
#include "gold.h"
#include "tile.h"

#include <assert.h>
//#include <cstdlib>
#include <iostream>

using namespace std;

Action* Character::action = NULL;

Character::Character( int level ) :
    level( level )
{
}

Character::Character( const DefaultStat* baseStat, int level ) :
    level( level ), baseStat( baseStat )

{
    assert( baseStat );
    currentHP = getMaxHP();
}

Character::~Character()
{
}

int Character::getBetween( int val, 
                           int high, 
                           int low ) const
{
    if( val > high )        return high;
    else if( val < low )    return low;
    else                    return val;
}

void Character::setDefaultStat( const DefaultStat* stats )
{
    assert( stats );
    baseStat = stats;
    currentHP = getMaxHP();
}

void Character::setAction( Action* act )
{
    assert( act );
    action = act;
}

bool Character::isPassable( const Character& who ) const
{
    return false;
}

bool Character::isAlive() const
{
    return currentHP > 0;
}


char Character::draw() const
{
    return baseStat->shape;
}

std::string Character::getRace() const
{
    return baseStat->race;
}

int Character::getHP() const
{
    return currentHP;
}

int Character::getMaxHP() const
{
    return baseStat->maxHP 
    #ifdef _LEVEL
        + (level-1) * 20
    #endif
    ;
}
int Character::getDef() const
{
    return baseStat->baseDef
    #ifdef _LEVEL
         + (level-1) * 5
    #endif
    ;
}

int Character::getAtk() const
{
    return baseStat->baseAtk
    #ifdef _LEVEL
         + (level-1) * 5
    #endif
    ;
}

int Character::getAbilityFlag( int flag ) const
{
    return baseStat->abilities[flag];
}

Item* Character::receiveDmg( int dmg )
{
    // so Charlie can stop being lazy :)
    assert( currentHP > 0 );
    
    currentHP-=dmg;
    currentHP = getBetween( currentHP, getMaxHP() );
    if( currentHP <= 0 )
    {
        // remove Character from tile and drop gold
        if( baseStat->gold > 0 )
        {
            Gold* spoils = new Gold( baseStat->gold + level - 1 );
            spoils->setLocation( getCoords(), isOn );
            isOn->replaceObject( spoils );
            setTileToNull();
            return spoils;
        }
        detach();
    }
    return NULL;
}

void Character::giveDmg( int dmg )
{
    // Abilities
    // Vampire ability restores health half of dmg dealt
    if( getAbilityFlag( 3 ) )
    {
        currentHP+=(dmg / 4);
        currentHP = getBetween( currentHP, getMaxHP() );
        (*display) << "The " << getRace()
                   << " restored " << (int) dmg/4 << "HP!\n";
    }

}
