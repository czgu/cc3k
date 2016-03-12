#include "boardDisplay.h"

BoardDisplay::BoardDisplay(const int row, const int col, std::ostream* s
#ifdef _NCURSE
,std::string color
#endif
)
: ROW(row) ,COL(col), source(s)
{
    theGrid = new char*[ROW];
    for(int i = 0; i < ROW; i++)
    {
        theGrid[i] = new char[COL];
    }
    #ifdef _NCURSE
    std::ifstream f(color.c_str());
    while(!f.eof())
    {
        char ch;
        std::string name;
        f >> ch >> name;
        colorMap.insert(std::pair<char,std::string>(ch,name));
    }
    initColor();
    #endif
}

BoardDisplay::~BoardDisplay()
{
    for(int i = 0; i < ROW; i++)
    {
        delete [] theGrid[i];
    }
    delete [] theGrid;
}

void BoardDisplay::render()
{
    for(int i = 0; i < ROW; i++)
    {
        for(int j = 0; j < COL; j++)
        {
            #ifdef _NCURSE
            printChColor(i,j,theGrid[i][j]); 
            #else
            (*source) << theGrid[i][j];     
            #endif  
        }
        #ifndef _NCURSE
        (*source) << std::endl;
        #endif
    }
    #ifdef _NCURSE
    printw("\n");
    refresh();
    #endif
}

void BoardDisplay::draw(int x, int y, char ch)
{
    theGrid[x][y] = ch;
}
#ifdef _NCURSE
void BoardDisplay::printChColor(int i,int j, char ch)
{
    std::map<char,std::string>::iterator it = colorMap.find(ch);
    if(it == colorMap.end())
    {
        attron(COLOR_PAIR(7));
        mvaddch(i,j,ch);
        attroff(COLOR_PAIR(7));
    }
    else
    {
        std::string color = it->second;
        if(color == "RED")
        {        
            attron(COLOR_PAIR(1));
            mvaddch(i,j,ch); refresh();
            attroff(COLOR_PAIR(1));
        }
        else if(color == "YELLOW")
        {
            attron(COLOR_PAIR(2));
            mvaddch(i,j,ch); refresh();
            attroff(COLOR_PAIR(2));
        }
        else if(color == "BLUE")
        {
            attron(COLOR_PAIR(3));
            mvaddch(i,j,ch); refresh();
            attroff(COLOR_PAIR(3));
        }
        else if(color == "GREEN")
        {
            attron(COLOR_PAIR(4));
            mvaddch(i,j,ch);
            attroff(COLOR_PAIR(4));
        }
        else if(color == "MAGENTA")
        {
            attron(COLOR_PAIR(5));
            mvaddch(i,j,ch);
            attroff(COLOR_PAIR(5));
        }
        else if(color == "CYAN")
        {
            attron(COLOR_PAIR(6));
            mvaddch(i,j,ch);
            attroff(COLOR_PAIR(6));
        }
    
    }
}

void BoardDisplay::initColor()
{
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);
}
#endif 
