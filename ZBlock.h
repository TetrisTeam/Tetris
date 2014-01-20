#ifndef ZBLOCK
#define ZBLOCK

#include "BlockBase.h"
#include "Environment.h"

static const bool ZMatrix[3][3] = {{1, 1, 0}, 
							      {0, 1, 1}, 
							      {0, 0, 0}};

class ZBlock : public BlockBase
{	
public:
    ZBlock(int X, int Y, int Rotation, bool flipped, ConsoleColor Color, char Symbol, Environment* Env) : BlockBase(X, Y, Rotation, flipped, Color, Symbol, Env) {
		memcpy(shape, ZMatrix, sizeof (bool) * 3 * 3);
		init();
	}
};

#endif