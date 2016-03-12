#ifndef _MENUDISPLAY
#define _MENUDISPLAY
#include "display.h"
#include <iostream>
#include <ncurses.h>
#include <fstream>
#include <string>

class MenuDisplay
{
    std::string f;
  public:
    MenuDisplay(std::string fname);
    void render();
};

#endif
