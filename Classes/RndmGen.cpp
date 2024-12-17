#include "RndmGen.h"

RndmGen::RndmGen(int upperLimit)
{
	this->upperLimit = upperLimit;

}

int RndmGen::generate(int seed)
{							///	initiating a seed using a time variable									/// giving a time dependent seed
	int randomseed = rand();						/// randomised num
	srand(randomseed);								/// giving a randomised seed as a new seed to generate a new random number with no direct dependencies
	int generated_num = 1 + rand() % upperLimit;	/// generated num

	/// checking if the generated num has a scenario or not
	///if ((generated_num < 10) || (generated_num >= 25 && generated_num < 30) || (generated_num >= 45 && generated_num < 70) || (generated_num >= 75 && generated_num < 80) || (generated_num == 90) || (generated_num >= 95 && generated_num <= 100))
	//{
		////validFlag = false;
	//}
	//else
	//{
		///validFlag = true;
	//}

	//if (validFlag)					/// base case
	//{
	return generated_num;
	//}
	//else
	//{
		//return generate();			/// recursive call, so it never stops generating nums till the num has a given scenario
	//}
}