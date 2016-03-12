#include "messageDisplay.h"
#include <iostream>
void MessageDisplay::render()
{
    std::string line;
    while(!s.eof())
    {
        std::getline(s,line);
        if(line != "")
        {
            #ifdef _NCURSE
            printw("%s\n",line.c_str());
            #else
            std::cout << line << std::endl;
            #endif
        }
    }
    #ifdef _NCURSE
    refresh();
    #endif
    s.clear();
}

void MessageDisplay::renderString( std::string s)
{
    #ifdef _NCURSE
    printw("%s",s.c_str());
    refresh();
    #else
    std::cout << s;
    #endif
}
