#include "playerImpl.h"
#include "defaultStat.h"

#include "action.h"
#include "tile.h"
#include "item.h"
#include "potion.h"
#include "gold.h"

#include "messageDisplay.h"
#include <string>

#include <assert.h>
#include <iostream>


PlayerImpl::PlayerImpl( const DefaultStat* baseStat ) :
    Character( baseStat, 1 ), gold( 0 ), currExp(0)
{
    assert( baseStat->shape == '@' );

    resetStats();
    (*display) << "Player character has spawned. ";
}

PlayerImpl::~PlayerImpl()
{
}

void PlayerImpl::leaveFloor()
{
    resetStats();
    isOn = NULL;
}

void PlayerImpl::setTile( Tile* tile )
{
    // Cannot reset player tile
    //assert( !isOn );
    //isOn = tile;
    Object::setTile( tile );
}

int PlayerImpl::getGoldValue() const
{
    int money = gold;
    
    // Abilities
    // Dwarf: double value
    // Orc: halve value
    if( getAbilityFlag( 0 ) )   // dwarf
        money*=2;
    if( getAbilityFlag( 1 ) )   // orc
        money/=2;

    return money;
}

/*
char PlayerImpl::draw() const
{
    return baseStat->shape;
}*/

// basically never occurs
void PlayerImpl::notify( PlayerImpl& )
{
    assert( 0 );
}

bool PlayerImpl::isPlayer() const
{
    return true;
}

int PlayerImpl::getDef() const
{
    return currentDef + Character::getDef();
}

int PlayerImpl::getAtk() const
{
    return currentAtk + Character::getAtk();
}

void PlayerImpl::resetStats()
{
    currentAtk = 0;
    currentDef = 0;
}

void PlayerImpl::broadcast()
{
    assert( isOn );
    isOn->notifyEnemies( *this );
}

bool PlayerImpl::move( Direction dir )
{
    assert( action );
    bool success = action->move( *this, dir );
    if( success )
    {
        std::string movedTo;
        switch(dir)
        {
            case EAST: movedTo = "East" ; break;
            case NORTHEAST: movedTo = "Northeast" ; break;
            case NORTH : movedTo = "North"; break;
            case NORTHWEST : movedTo = "Northwest"; break;
            case WEST : movedTo = "West"; break;
            case SOUTHWEST : movedTo = "Southwest"; break;
            case SOUTH : movedTo = "South"; break;
            case SOUTHEAST : movedTo = "Southeast"; break;
        }
        (*display) << "Player moves " << movedTo << ". ";

        broadcast();
    }
    return success;
}

bool PlayerImpl::attack( Direction dir )
{
    assert( action );
    bool success = action->attack( *this, dir );
    if( success )
        broadcast();
    return success;
}

bool PlayerImpl::pickUp( Direction dir )
{
    assert( action );
    bool success = action->pickUp( *this, dir );
    if( success )
        broadcast();
    return success;
}

Item* PlayerImpl::receiveDmg( int dmg )
{
    Item* spoils = Character::receiveDmg( dmg );

    // print out something here, "You got hit"
    (*display) << "Player. ";
    return spoils;
}

void PlayerImpl::giveDmg( int dmg )
{
    Character::giveDmg( dmg );
    // print out something here, "You landed a hit"
    (*display) << "Player deals " << dmg << " damage to the ";
}


void PlayerImpl::pickUp( const Potion& potion )
{
    int value = potion.getValue();
    PotionEffect type = potion.getPotionEffect();

    // Elf ability: absolute value effects
    if( getAbilityFlag( 2 ))
        value = ( value < 0 )? -value : value;

    switch( type )
    {
        case HEALTH :
            Character::receiveDmg( -value );
            break;
        case ATTACK :
            currentAtk += value;
            currentAtk = ( getAtk() < 0 )? -Character::getAtk() : currentAtk;
            break;
        case DEFENSE :
            currentDef += value;
            currentDef = ( getDef() < 0 )? -Character::getDef() : currentDef;
            break;
        default :
            assert( 0 );
    }
    (*display) << "Player uses ";
}

void PlayerImpl::pickUp( const Gold& money )
{
    gold+=money.getValue();
    if( gold < 0 )
        gold = 0;
}

void PlayerImpl::gainExp( int exp )
{
    
    assert ( exp >= 0 );
    (*display) << "Player gained " <<  exp << " exp! ";
    currExp += exp;
    if( currExp >= level * 200 )
    {
        currExp -= level * 200;
        ++level;
        currentHP = getMaxHP();
        (*display) << "Player leveled up! ";
    }
}

int PlayerImpl::getLevel() const
{
    return level;
}   

int PlayerImpl::getExp() const
{
    return currExp;
}

