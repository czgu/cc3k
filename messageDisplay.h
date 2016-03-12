#ifndef _MESSAGEDISPLAY_H
#define _MESSAGEDISPLAY_H

#include "display.h"
#include <sstream>
#include <string>
class MessageDisplay : public Display
{
    std::stringstream s;
    std::string stack;
  public:
    template <typename Type>
    MessageDisplay& operator<<(Type msg)
    {
        s << msg;
        return *this;
    }
    void renderString( std::string s );
    void render();
};

#endif
