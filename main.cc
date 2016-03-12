#include "game.h"
#include <cstdlib>
#include <time.h>
#include <ncurses.h>
int main(int argc,char **argv)
{
    srand(time(0));

    #ifdef _NCURSE
    initscr();
    cbreak();
    noecho();

    if(has_colors() == FALSE)
    {   endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }
    start_color();
    #endif

    Game* g;
    if(argc <= 1)
    {
        g = new Game();
    }
    else
        g = new Game(argv[1]);
    g->run();
    delete g;
        

    #ifdef _NCURSE
    endwin();
    #endif
    return 0;
}
