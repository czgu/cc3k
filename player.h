#ifndef _PLAYER_H
#define _PLAYER_H

#include <string>
#include "action.h"

class PlayerImpl;
class Tile;
struct DefaultStat;
struct Coord;

class Player
{
    PlayerImpl* player;

  public:
    Player( const DefaultStat* );
    ~Player();

    // setTile:
    // can only do once per floor
    void setLocation( Coord, Tile* );
    
    // leaveFloor:
    // Call this when leaving floor
    // resets baseStats, sets Tile to null
    void leaveFloor(); 

    int getHP() const;
    int getMaxHP() const;
    int getLevel() const;
    int getExp() const;
    int getDef() const;
    int getAtk() const;
    int getGold() const;
    std::string getRace() const;
    bool isAlive() const;

    // move/attack:
    // moves/attacks in specified direction
    // returns true if valid move, false if invalid
    bool move( Direction );
    bool attack( Direction );
    bool pickUp( Direction );
    bool input(std::string command);
};

#endif
