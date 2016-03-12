#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "object.h"
#include "defaultStat.h"

#include <string>

class Action;
class Item;

class Character : public Object
{   
    protected:
    int currentHP;
    int level;   
    const DefaultStat* baseStat;
    static Action* action;

    int getBetween( int val, int high, int low=0 ) const;

//    private:
//    static void cleanupAction( void );

    public:
    Character( int level );
    Character( const DefaultStat*, int level );
    ~Character();

    // Setup methods
    void setDefaultStat( const DefaultStat* );
    static void setAction( Action* );

    // Query methods
    bool isPassable( const Character& ) const;
    virtual bool isPlayer() const = 0;
    bool isAlive() const;
    std::string getRace() const;
    char draw() const;

    // Action methods
    int getHP() const;
    int getMaxHP() const;
    virtual int getDef() const;
    virtual int getAtk() const;
    int getAbilityFlag( int flag ) const;

    virtual Item* receiveDmg( int dmg );
    virtual void giveDmg( int dmg );
#if 0
    // TODO: implement object pickup function
    void pickUp( Object& );
#endif
};

#endif
