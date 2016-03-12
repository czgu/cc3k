#ifndef _LISTENER_H
#define _LISTENER_H

#include <string>
#include <fstream>
#include <iostream>
#include <assert.h>

class Listener
{
    std::istream* source;
  public:
    Listener();
    ~Listener();
    void setSource(std::string fname);
    
    char getChar();

    template <typename Type>
    Type get()
    {
        Type temp;
        (*source) >> temp;
        return temp;
    }
    
    bool isDone();
};

#endif
