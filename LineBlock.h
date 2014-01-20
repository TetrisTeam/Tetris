#ifndef LINEBLOCK
#define LINEBLOCK

#include "BlockBase.h"
#include "Environment.h"

static const bool LineMatrix[3][3] = {{1, 0, 0}, 
							      {1, 0, 0}, 
							      {1, 0, 0}};

class LineBlock : public BlockBase
{	
public:
    LineBlock(int X, int Y, int Rotation, bool flipped, ConsoleColor Color, char Symbol, Environment* Env) : BlockBase(X, Y, Rotation, flipped, Color, Symbol, Env) {
		memcpy(shape, LineMatrix, sizeof (bool) * 3 * 3);
		init();
	}
};

#endif