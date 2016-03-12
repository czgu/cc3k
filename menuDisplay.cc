#include "menuDisplay.h"

MenuDisplay::MenuDisplay(std::string fname)
{
    f = fname;
}

void MenuDisplay::render()
{
    #ifdef _NCURSE
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    #endif
    std::ifstream menu(f.c_str());
    int i = 0;
    while(!menu.eof())
    {
        std::string s;
        getline(menu,s);
        #ifdef _NCURSE
        for(unsigned int j = 0; j < s.length(); j++)
        {
            if(s[j] == '\\' || s[j] == '/')
            {
                attron(COLOR_PAIR(1));
                mvaddch(i,j,s[j]);
                attroff(COLOR_PAIR(1));
            }
            else if(s[j] == '<' || s[j] == '>')
            {
                attron(COLOR_PAIR(2));
                mvaddch(i,j,s[j]);
                attroff(COLOR_PAIR(2));
            }
            else
            {
                mvaddch(i,j,s[j]);
            }

        }
        #else
        std::cout << s << std::endl;
        #endif

        i++;
    }
}
