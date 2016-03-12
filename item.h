#ifndef _ITEM_H
#define _ITEM_H

#include "object.h"

class PlayerImpl;

class Item : public Object
{
  protected:
    int value;

  public:
    Item( int value );

    virtual bool getUsedBy( PlayerImpl& ) = 0;
    void notify( PlayerImpl& );
    int getValue() const;
};

#endif
