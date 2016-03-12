#include "gameSession.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <sstream>

GameSession::GameSession(int row, int col,int mode, char *fname): currFloor(NULL),currentLevel(0),quitStatus(0),mapMode(mode)
{
    system("clear");
    action = new Action();
    p = NULL;
    in = new InputHandler("stdin","control.txt");
    makeMap = new MapGenerator();
    stats = new StatsCollector("race.txt");
    mapDisplay = new BoardDisplay(row,col,&std::cout
    #ifdef _NCURSE
    ,"color.txt"
    #endif
    );
    message = new MessageDisplay();
    map = new Listener();
    if(mapMode)
    {   
        map->setSource(fname);
    }
    Listener l;
    l.setSource("potion.txt");
    while(true)
    {
        int n = l.get<int>();
        if(l.isDone()) break;
        potionSetting.push_back(n);
    }
    l.setSource("gold.txt");
    while(true)
    {
        int first = l.get<int>();
        if(l.isDone()) break;
        int second = l.get<int>();
        Tuple t = {first,second};
        goldSetting.push_back(t);
    }
    Character::setAction ( action );
    Object::setMessageDisplay( message );

}

GameSession::~GameSession()
{
    delete action;
    delete currFloor;
    delete mapDisplay;
    delete message;
    delete makeMap;
    delete stats;
    delete in;
    if(p) delete p;
    delete map;
}

int GameSession::run(int &score)
{
    while(!p)
    {   
        #ifdef _NCURSE
        clear();
        printw("Select a race: ");
        printw("%s\n",stats->printPlayable().c_str());
        refresh();
        clear();
        #else
        std::cout << "Select a race: ";
        std::cout << stats->printPlayable() << std::endl;
        #endif
        char select = in->get<char>();
        if(stats->statsExists("pc",select))
        {       
            p = new Player( stats->getStats("pc",select) );
        }
        system("clear");
    }
    startNewLevel();
    while(!isGameDone())
    {  
        updateDisplay();
        message->renderString( updatePlayerInfo() );
        message->render();
        #ifdef _NCURSE
        clear();
        #endif
        step();
        if(currFloor->levelDone())
            startNewLevel();
    }
    score = p->getGold() * (p->getRace() == "human"?1.5:1);   
    return quitStatus;
}

bool GameSession::isGameDone()
{

    //case 1: player wants to 
    if (quitStatus > 0)
    {  
        return true;
    }

    //case 2: player has beaten the game
    if(currentLevel > 8) 
    {
        quitStatus = -1;
        return true;
    }
    if(!p->isAlive())
    {
        quitStatus = 0;
        return true;
    }
    return false;
}

void GameSession::step()
{   
    int playerMoved = false;
    while(!playerMoved)
    {
        std::string input = in->parse();
        if(input[0] == 's')
        {
            if(input[1] == 'q') quitStatus = 1;
            if(input[1] == 'r') quitStatus = 2;
            return;
        }
        if(input[0] == 'p')
        {   
            playerMoved = p->input(input.substr(1));
        }
        if(currFloor->levelDone()) return;
    }  
    currFloor->update();
}

void GameSession::startNewLevel()
{
    if(currFloor) delete currFloor;
    p->leaveFloor();
    if(mapMode == 0)
    {
        currFloor = makeMap->createMap("map.txt",p,stats,currentLevel+1,20,20,20,potionSetting,goldSetting);
    }
    else
        currFloor = makeMap->createStaticMap(*map,p,stats,currentLevel+1,potionSetting,goldSetting);
    action->changeFloor(currFloor);
    currentLevel++;
}

void GameSession::updateDisplay()
{
    currFloor->draw(*mapDisplay);
    system("clear");
    mapDisplay->render();
}

std::string GameSession::updatePlayerInfo()
{
    std::ostringstream oss;
        
    oss << std::left << "Race: " << p->getRace() 
        << "    Gold: " << p->getGold() 
    #ifdef _LEVEL 
       << "    Level: " << p->getLevel()
    #endif
        << std::right << std::setw(44) << "Floor: " << currentLevel << std::endl;
    oss  << "HP: " << std::setw(5) << p->getHP() << "/" << p->getMaxHP();
    #ifdef _LEVEL
    oss << "   Exp: " << std::setw(5) << p->getExp() << "/" << p->getLevel()*200;
    #endif
    oss << std::left << "    Atk: " << std::setw(5) << p->getAtk() << "Def: " << std::setw(5) << p->getDef() << '\n';
    oss << "Action: ";
    return oss.str();
}
