#ifndef _DISPLAY_H
#define _DISPLAY_H

#include <iostream>
#include <ncurses.h>
class Display
{
  public:
    virtual void render() = 0;
};
     
#endif
