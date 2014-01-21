#ifndef ZBLOCK
#define ZBLOCK

#include "BlockBase.h"
#include "Environment.h"

bool ZMatrix[2][3] = {{1, 1, 0}, 
					  {0, 1, 1}};

class ZBlock : public BlockBase
{	
public:
    ZBlock(int X, int Y, int Rotation, bool flipped, ConsoleColor Color, char Symbol, Environment* Env) : BlockBase(X, Y, Rotation, flipped, Color, Symbol, Env) {
		Width = sizeof(ZMatrix[0])/sizeof(bool);
		Height = sizeof(ZMatrix)/sizeof(ZMatrix[0]);
		shape = new bool *[Height];
		for(int i=0; i<Height; i++)
		{
			shape[i] = new bool[Width];
			for(int j=0; j<Width; j++)
			{
				shape[i][j] = ZMatrix[i][j];
			}
		}
		init();
	}
};

#endif