#ifndef _INPUTHANDLER_H
#define _INPUTHANDLER_H

#include "listener.h"
#include <string>
#include <map>

class InputHandler : public Listener
{
    std::map <char,std::string> reference;
  public:
    InputHandler(std::string source, std::string setup);
    std::string parse();
};

#endif
