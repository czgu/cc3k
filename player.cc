#include "player.h"
#include "playerImpl.h"

#include "action.h"
#include "tile.h"
#include "coord.h"
#include <iostream>

Player::Player( const DefaultStat* stats ) :
    player( new PlayerImpl( stats ))
{
    
}

Player::~Player()
{
    delete player;
}

bool Player::move( Direction dir )
{
    return player->move( dir );
}

bool Player::attack( Direction dir )
{
    return player->attack( dir );
}

bool Player::pickUp( Direction dir )
{
    return player->pickUp( dir );
}

void Player::leaveFloor()
{
    player->leaveFloor();
}

void Player::setLocation( Coord coord, Tile* tile )
{
    player->setLocation( coord, tile );
}

int Player::getHP() const
{
    return player->getHP();
}

int Player::getDef() const
{
    return player->getDef();
}

int Player::getAtk() const
{
    return player->getAtk();
}

int Player::getGold() const
{
    return player->getGoldValue();
}

std::string Player::getRace() const
{
    return player->getRace();
}

bool Player::isAlive() const
{
    return player->isAlive();
}

bool Player::input(std::string command)
{
    bool success;
    if(command[0] == 'm' || command[0] == 'g')
    {
       success = move(static_cast<Direction>(command[1] - '0'));
       if(success) return success;
    }
    if(command[0] == 'a' || command[0] == 'g')
    {
       success = attack(static_cast<Direction>(command[1] - '0'));
       if(success) return success;
    }
    if(command[0] == 'p' || command[0] == 'g')
    {
        success = pickUp(static_cast<Direction>(command[1] - '0'));
        if(success) return success;
    }
    return false;
}

int Player::getMaxHP() const
{
    return player->getMaxHP();
}

int Player::getLevel() const
{
    return player->getLevel();
}

int Player::getExp() const
{
    return player->getExp();
}

