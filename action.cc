#include "action.h"

#include "tile.h"
#include "floor.h"

#include "coord.h"
#include "character.h"
#include "npc.h"
#include "playerImpl.h"

#include "stairs.h"
#include "item.h"
#include "gold.h"

#include "randomizer.h"

#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <math.h>

Action::Action()
{
    srand( time(NULL) );
}

Action::~Action(){}

namespace
{
    Coord getCoordInDir( Direction dir, Coord orig )
    {
        if( dir < 4 && dir > 0 )   // move north
            --orig.row;
        else if( dir > 4 )         // move south
            ++orig.row;
        if( dir > 2 && dir < 6 )    // move west
            --orig.col;
        else if( !( dir == 2 || dir == 6 )) // move east
            ++orig.col;
        return orig;
    }
    
    inline int calcDmg( int atk, int def )
    {
        return ceil( ( 100.0/(100.0 + def) ) * atk );
    }
}


void Action::changeFloor( Floor* nFloor )
{
    assert( nFloor );
    floor = nFloor;
}


Tile* Action::getValidTile( Character& player, Direction dir, Coord& nCoord )
{
    nCoord = getCoordInDir( dir, player.getCoords() );
    Tile* dest = floor->getTile( nCoord ); 

    if( !dest )     // invalid direction to move in
        return NULL;
    
    return dest;
}

// call after certain this is valid move
Object* Action::moveChar( Character& player, 
                          Tile& dest, 
                          Coord nCoord )
{
    // move in specified direction
    Tile& orig = player.getTile();

    orig.removeObject();
    Object* obj = dest.replaceObject( &player );

    // update object's location info
    player.setTile( &dest );
    player.setCoords( nCoord ); 

    if( player.getAbilityFlag(4) )
    {
        player.Character::receiveDmg( -1 );
    }

    return obj;
}

bool Action::moveChar( Character& player, Direction dir,
                       Object*& obj )
{
    Coord nCoord;
    Tile* dest = getValidTile( player, dir, nCoord );
    if( !dest )   
        return false;
    if( !(dest->isPassable( player )) ) // can't move there
        return false;

    obj = moveChar( player, *dest, nCoord );
    return true;
}

bool Action::move( NPC& enemy )
{
    Object* obj = NULL;

#if 1
    Randomizer random;
    random.createRandomSeq( 0, 7, 8, true );
    
    bool success = false;
    
    for( int i = 0 ; i < 8 ; ++i )
    {
        Direction dir = static_cast<Direction>( random.getFirstNum() );
        success = moveChar( enemy, dir, obj );
        if( success )
            break;
    }
    return success;
#endif
}

bool Action::runAway( NPC& enemy, PlayerImpl& player )
{
    Coord coord;
    bool success = false;
    Object* obj = NULL;
    Coord pCoords = player.getCoords();
    
    for( int dir = 0 ; dir < 8 ; ++dir )
    {
        
        Direction direct = static_cast<Direction>( dir );
        coord = getCoordInDir( direct, enemy.getCoords() );

        if( abs( coord.row - pCoords.row ) > 1 ||
            abs( coord.col - pCoords.col ) > 1 )
        {
            success = moveChar( enemy, direct, obj );
            if( success )
                break;
        }
    }
    
    return success;
}

bool Action::move( PlayerImpl& player, Direction dir )
{
    Object* obj = NULL;
    bool success = moveChar( player, dir, obj );

    if( obj )
    {
        Stairs* stairs = dynamic_cast<Stairs*>( obj );
        if( stairs )
            stairs->reach();
#if 1
        else
        {
            Item* item  = dynamic_cast<Item*>( obj );
            assert( item );

            item->getUsedBy( player );
            item->setTileToNull();
        }
#endif
    }

    return success;
}



bool Action::attack( NPC& enemy, PlayerImpl& player )
{
    // Enemies have 50% chance of missing
    if( rand() % 2 )
        return false;
     
    int atk = enemy.getAtk();
    int def = player.getDef();
  
    int dmg = calcDmg( atk, def );
    enemy.giveDmg( dmg );
    player.receiveDmg( dmg );

    // Goblin ability: steal gold
    if( enemy.getAbilityFlag( 5 ) )
    {
        Gold loss( -1 );
        player.pickUp( loss );
    }

    return true;
}

bool Action::attack( PlayerImpl& player, Direction dir )
{
    Coord coord;
    Tile* dest = getValidTile( player, dir, coord );
    if( !dest )   
        return false;

    NPC* enemy = dynamic_cast<NPC*>( dest->getObject() );
    if( !enemy )
        return false;
    
    int atk = player.getAtk();
    int def = enemy->getDef();

    int dmg = calcDmg( atk, def );
    player.giveDmg( dmg );
    Item* spoils = enemy->receiveDmg( dmg );
    
#ifdef _LEVEL
    // enemy is killed
    if( !enemy->isAlive() )
    {
        player.gainExp( enemy->getMaxHP() + 
                        enemy->getDef() +
                        enemy->getAtk() );
    }
#endif
    if( spoils )
        floor->setItem( spoils );

    return true;
}

bool Action::pickUp( PlayerImpl& player, Direction dir )
{
    Coord coord;
    Tile* tile = getValidTile( player, dir, coord );
    if( !tile )  return false;

    Object* obj = tile->getObject();
    if( !obj )  return false;

    Item* item = dynamic_cast<Item*>( obj );
    if( !item ) return false;

    bool success = item->getUsedBy( player );
    if( !success )
        return false;

    item->detach();
    return true;
}


