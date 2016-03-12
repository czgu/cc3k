#ifndef _BOARDDISPLAY_H
#define _BOARDDISPLAY_H

#include <ncurses.h>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include "display.h"

class BoardDisplay : public Display
{   
  private:
    const int ROW;
    const int COL;
    char** theGrid;
    std::ostream* source;
    #ifdef _NCURSE
    std::map<char,std::string> colorMap;
    #endif
  public:
    void render();
    void draw(int x, int y, char ch);   
    BoardDisplay(const int row,const int col, std::ostream* s
    #ifdef _NCURSE
    ,std::string color
    #endif
    );
    ~BoardDisplay();
    #ifdef _NCURSE
    void printChColor(int i, int j,char ch);
    void initColor(); 
    #endif
};

#endif
