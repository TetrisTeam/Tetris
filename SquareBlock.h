#ifndef SQUAREBLOCK
#define SQUAREBLOCK

#include "BlockBase.h"
#include "Environment.h"

bool SquareMatrix[2][2] = {{1, 1}, 
					       {1, 1}};

class SquareBlock : public BlockBase
{	
public:
    SquareBlock(int X, int Y, int Rotation, bool flipped, ConsoleColor Color, char Symbol, Environment* Env) : BlockBase(X, Y, Rotation, flipped, Color, Symbol, Env) {
		Width = sizeof(SquareMatrix[0])/sizeof(bool);
		Height = sizeof(SquareMatrix)/sizeof(SquareMatrix[0]);

		shape = new bool *[Height];
		for(int i=0; i<Height; i++)
		{
			shape[i] = new bool[Width];
			for(int j=0; j<Width; j++)
			{
				shape[i][j] = SquareMatrix[i][j];
			}
		}
		init();
	}
};

#endif