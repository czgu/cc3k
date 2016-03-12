#include "listener.h"

Listener::Listener() : source(NULL) {}
Listener::~Listener()
{
    if(source != &std::cin)
        delete source; 
}

void Listener::setSource(std::string fname)
{
    if(source != &std::cin)
        delete source;

    if(fname == "stdin")
    {
        source = &std::cin;
    }
    else
    {
        source = new std::ifstream(fname.c_str());
    }
}

char Listener::getChar()
{
    return source->get();
}

bool Listener::isDone()
{
    return source->eof();
}
