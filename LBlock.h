#ifndef LBLOCK
#define LBLOCK

#include "BlockBase.h"
#include "Environment.h"

bool LMatrix[3][2] = {{1, 0}, 
					  {1, 0}, 
					  {1, 1}};

class LBlock : public BlockBase
{	
private:

public:
    LBlock(int X, int Y, int Rotation, bool flipped, ConsoleColor Color, char Symbol, Environment* Env) : BlockBase(X, Y, Rotation, flipped, Color, Symbol, Env) {
		Width = sizeof(LMatrix[0])/sizeof(bool);
		Height = sizeof(LMatrix)/sizeof(LMatrix[0]);
		shape = new bool *[Height];
		for(int i=0; i<Height; i++)
		{
			shape[i] = new bool[Width];
			for(int j=0; j<Width; j++)
			{
				shape[i][j] = LMatrix[i][j];
			}
		}
		init();
	}
};

#endif