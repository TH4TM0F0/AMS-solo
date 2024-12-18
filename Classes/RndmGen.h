#pragma once
#include <stdlib.h>
#include <ctime>
class RndmGen
{
private:
	int upperLimit;					/// limit to generate a num between 1 to upperlimit

public:
	RndmGen(int upperLimit = 100);	/// Default Constructor initiated with 100, upperlimit is always 100 but i decided to pass an initialized var in case i wanted to generate a num between 1 to another upperlimit
	int generate(int seed);					/// Func responsible to generate the num	
};

