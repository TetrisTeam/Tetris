#ifndef TBLOCK
#define TBLOCK

#include "BlockBase.h"
#include "Environment.h"

bool TMatrix[2][3] = {{1, 1, 1}, 
					  {0, 1, 0}};

class TBlock : public BlockBase
{	
public:
    TBlock(int X, int Y, int Rotation, bool flipped, ConsoleColor Color, char Symbol, Environment* Env) : BlockBase(X, Y, Rotation, flipped, Color, Symbol, Env) {
		
		Width = sizeof(TMatrix[0])/sizeof(bool);
		Height = sizeof(TMatrix)/sizeof(TMatrix[0]);
		shape = new bool *[Height];
		for(int i=0; i<Height; i++)
		{
			shape[i] = new bool[Width];
			for(int j=0; j<Width; j++)
			{
				shape[i][j] = TMatrix[i][j];
			}
		}
		init();
	}
};

#endif