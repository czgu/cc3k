#ifndef _RANDOMIZER_H
#define _RANDOMIZER_H

#include <cstdlib>
#include <vector>
#include <time.h>

class Randomizer
{
    std::vector<int> stack;
    bool stackHas(int n);
    
  public:
    Randomizer();
    ~Randomizer();
    // creates a sequence of random numbers
    // if num == 0 (default) then nothing is added to stack
    // if num > 0, stack is cleared, a sequence of number is generated
    // up to (up - low). they can be distinct if flag is turned on
    int num( int low,int up );
    void createRandomSeq( int low, int up, 
                          int num, bool distinct );
    // pops the first num from the stack
    int getFirstNum();
    int stackSize();
    void clearStack();
};

#endif
