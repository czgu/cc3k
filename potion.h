#ifndef _POTION_H
#define _POTION_H

#include "item.h"
#include <string>

enum PotionEffect
{
    HEALTH = 0,
    ATTACK,
    DEFENSE
};

struct PotionKnowledge
{
    bool seenRH;
    bool seenBA;
    bool seenBD;

    bool seenPH;
    bool seenWA;
    bool seenWD;

    PotionKnowledge();
};

class Potion : public Item
{
    static PotionKnowledge* usage;
    const PotionEffect type;
    std::string name;

    static void cleanup( void );
    void use();
  public:
    Potion( PotionEffect, int value );

    bool getUsedBy( PlayerImpl& );
    PotionEffect getPotionEffect() const;

    // Virtual functions from Object to implement
    void notify( PlayerImpl& );
    char draw() const;
    bool isPassable( const Character& who ) const;
};

#endif
