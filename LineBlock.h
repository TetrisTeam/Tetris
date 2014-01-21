#ifndef LINEBLOCK
#define LINEBLOCK

#include "BlockBase.h"
#include "Environment.h"

bool LineMatrix[4][1] = {{1}, 
					     {1}, 
					     {1},
					     {1}};

class LineBlock : public BlockBase
{	
public:
    LineBlock(int X, int Y, int Rotation, bool flipped, ConsoleColor Color, char Symbol, Environment* Env) : BlockBase(X, Y, Rotation, flipped, Color, Symbol, Env) {
		Width = sizeof(LineMatrix[0])/sizeof(bool);
		Height = sizeof(LineMatrix)/sizeof(LineMatrix[0]);
		shape = new bool *[Height];
		for(int i=0; i<Height; i++)
		{
			shape[i] = new bool[Width];
			for(int j=0; j<Width; j++)
			{
				shape[i][j] = LineMatrix[i][j];
			}
		}
		init();
	}
};

#endif