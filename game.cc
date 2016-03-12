#include "game.h"
#include <iostream>
#include <cstdio>
#include "menuDisplay.h"
Game::Game(): session(NULL),mode(0),fname(NULL) {}
Game::Game(char* fname): session(NULL),mode(1),fname(fname) {}

Game::~Game()
{
    if(session) delete session;
}



void Game::run()
{
    int status = 0;
    int score = 0;
    MenuDisplay menu("menu.txt");
    menu.render();
    #ifdef _NCURSE
    refresh();
    #endif
    getchar();
    while(true)
    {
        session = new GameSession(25,79,mode,fname);
        status = session->run(score);
        if(status < 1)
        { 
            char in;
            if(status == -1)
            {
                #ifdef _NCURSE
                printw("You have beaten the game, congratz!\n");
                printw("Score %d\n",score);
                #else
                std::cout << "You have beaten the game, congratz!" << std::endl;
                std::cout << "Score: " << score << std::endl;
                #endif
            }
            else
            #ifdef _NCURSE
                printw("Game Over. ");
            printw("Do you want to play again? (y/n)");
            refresh();
            #else
                std::cout << "Game Over." << std::endl;
            std::cout << "Do you want to play again? (y/n)" << std::endl;
            #endif
            std::cin >> in;
            if(in == 'y' || in == 'Y') 
                status = 2;
        }

        if(status < 2) break;
        delete session;
    }
}
