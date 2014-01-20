#ifndef SQUAREBLOCK
#define SQUAREBLOCK

#include "BlockBase.h"
#include "Environment.h"

static const bool SquareMatrix[3][3] = {{1, 1, 0}, 
							      {1, 1, 0}, 
							      {0, 0, 0}};

class SquareBlock : public BlockBase
{	
public:
    SquareBlock(int X, int Y, int Rotation, bool flipped, ConsoleColor Color, char Symbol, Environment* Env) : BlockBase(X, Y, Rotation, flipped, Color, Symbol, Env) {
		memcpy(shape, SquareMatrix, sizeof (bool) * 3 * 3);
		init();
	}
};

#endif