#include "inputHandler.h"

InputHandler::InputHandler(std::string source, std::string setup){
    setSource(setup);
    while(true)
    {
        char input = get<char>();
        if(isDone()) break;
        std::string output = get<std::string>();
        reference.insert(std::pair<char,std::string>(input,output));
    }
    setSource(source);
}

std::string InputHandler::parse()
{
    std::string cmd = "";
    cmd += reference[get<char>()];
    if(cmd[0] == 'm')
    { 
        std::string tmp = reference[get<char>()];
        tmp[1] = cmd[1];
        cmd = tmp;
    }
    return cmd;
}
