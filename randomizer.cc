#include "randomizer.h"

Randomizer::Randomizer(){
}

Randomizer::~Randomizer(){}

int Randomizer::num(int low, int up)
{   
    if(up <= low) up = low;
    return rand()%(up-low+1) + low;
}

void Randomizer::createRandomSeq(int low,int up, int num, bool distinct)
{
    clearStack();
    while(num > 0 && stackSize() <= (up - low) )
    {
        int n = rand()%(up - low+1) + low;
        if(distinct && !stackHas(n))
        {
            stack.push_back(n);
            num --;
        }
        else if(!distinct)
        {
            stack.push_back(n);
            num --;
        }
        n = rand()%(up - low) + low;
    }
}

bool Randomizer::stackHas(int n)
{
    for(unsigned int i = 0; i < stack.size(); i++)
    {
        if(stack[i] == n) return true;
    }
    return false;
}

int Randomizer::getFirstNum()
{
    int n = stack.back();
    stack.pop_back();
    return n;
}

int Randomizer::stackSize()
{
    return stack.size();
}

void Randomizer::clearStack()
{
    stack.resize(0); 
}
