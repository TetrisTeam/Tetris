#ifndef TBLOCK
#define TBLOCK

#include "BlockBase.h"
#include "Environment.h"

static const bool matrix[3][3] = {{0, 0, 0}, 
							      {1, 1, 1}, 
							      {0, 1, 0}};

class TBlock : public BlockBase
{	
public:
    TBlock(int X, int Y, int Rotation, bool flipped, ConsoleColor Color, char Symbol, Environment* Env) : BlockBase(X, Y, Rotation, flipped, Color, Symbol, Env) {
		memcpy(shape, matrix, sizeof (bool) * 3 * 3);
		init();
	}
};

#endif