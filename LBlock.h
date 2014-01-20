#ifndef LBLOCK
#define LBLOCK

#include "BlockBase.h"
#include "Environment.h"

static const bool LMatrix[3][3] = {{1, 0, 0}, 
							      {1, 0, 0}, 
							      {1, 1, 0}};

class LBlock : public BlockBase
{	
public:
    LBlock(int X, int Y, int Rotation, bool flipped, ConsoleColor Color, char Symbol, Environment* Env) : BlockBase(X, Y, Rotation, flipped, Color, Symbol, Env) {
		memcpy(shape, LMatrix, sizeof (bool) * 3 * 3);
		init();
	}
};

#endif