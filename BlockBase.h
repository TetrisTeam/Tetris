#ifndef TETRIS_SHAPE
#define TETRIS_SHAPE

#include <iostream>
#include <Windows.h>

#include "Environment.h"

class BlockBase
{
private:
	typedef unsigned char GameColor;
	static const GameColor DefaultColor = 0xF;
	static GameColor BackgroundColor;
protected:
	bool shape[3][3];
public: 
	COORD Coordinates;
	int Rotation;
	char Symbol;
	ConsoleColor Color;
	Environment *Env;
	bool Ghost;
	bool Flipped;

	BlockBase::BlockBase(int x, int y, int Rotation, bool flipped, ConsoleColor Color, char Symbol, Environment *Env) :
		Rotation(Rotation), Color(Color), Symbol(Symbol)
	{
		COORD coordinates = { x, y };
		this->Coordinates = coordinates;
		this->Env = Env;
		Ghost = false;
		this->Flipped = flipped;
	}

	BlockBase::BlockBase(BlockBase* Block)
	{
		//memcpy(shape, Block->shape, sizeof (bool) * 3 * 3);
		for(int i=0; i<3; i++) 
		{
			for(int j=0; j<3; j++)
			{
				shape[i][j] = Block->shape[i][j];
			}
		}
		Coordinates.X = Block->Coordinates.X;
		Coordinates.Y = Block->Coordinates.Y;
		Rotation = Block->Rotation;
		Symbol = Block->Symbol;
		Color = Block->Color;
		Env = Block->Env;
		Ghost = false;
	}

	void BlockBase::init() 
	{
		if(Flipped)
		{
			char temp[3][3];
			memcpy(temp, shape, sizeof (bool) * 3 * 3);
			for(int i=0; i<3; i++)
			{
				for(int j=0; j<3; j++)
				{
					shape[i][j] = temp[i][2-j];
				}
			}
		}

		int t = Rotation;
		Rotation = 0;
		RotateBy(t);
	}

	void BlockBase::RotateBy(int angle) 
	{
		Rotation += angle;
		
		while(Rotation >= 360)
			Rotation -= 360;
		
		while(Rotation < 0)
			Rotation += 360;

		char temp[3][3];

		switch(angle) 
		{
		case 0:
			break;
		//rotate clockwise
		case 90:
			memcpy(temp, shape, sizeof (bool) * 3 * 3);

			for(int i=0; i<3; i++)
				for(int j=0; j<3; j++)
					shape[j][2-i] = temp[i][j];
			break;

		case 180:
			memcpy(temp, shape, sizeof (bool) * 3 * 3);

			for(int i=0; i<3; i++)
				for(int j=0; j<3; j++)
					shape[2-i][2-j] = temp[i][j];
			break;

		case 270:
			
			memcpy(temp, shape, sizeof (bool) * 3 * 3);

			for(int i=0; i<3; i++)
				for(int j=0; j<3; j++)
					shape[2-j][i] = temp[i][j];
			break;
		
		}
	}

	void BlockBase::UpdateCoordinates(const COORD& value)
	{
		this->Coordinates.X = value.X;
		this->Coordinates.Y = value.Y;
	}

	bool BlockBase::CanGoSideways(int by) 
	{
		int leftMost = 2;

		for(int i=0; i<3; i++)
		{
			for(int j=0; j<3; j++)
			{
				if(shape[i][j]) {
					if(j < leftMost)
						leftMost = j;
					break;
				}
			}
		}

		if(leftMost + Coordinates.X + by < 0)
			return false;

		int rightMost = 0;

		for(int i=0; i<3; i++)
		{
			for(int j=2; j>=0; j--)
			{
				if(shape[i][j]) {
					if(rightMost < j)
						rightMost = j;
					break;
				}
			}
		}

		if(rightMost + Coordinates.X + by >= Env->WindowWidth)
			return false;

		for(int i=0; i<3; i++)
		{
			for(int j=0; j<3; j++)
			{
				if(shape[i][j]) 
				{
					// right side
					if((j == 2 || !shape[i][j+1]) && Coordinates.X+j+1 < Env->WindowWidth && Env->ScreenMatrix[Coordinates.Y+i][Coordinates.X+j+1] == '*')
					{
						return false;
					}

					// left side
					if((j == 0 || !shape[i][j-1]) && Coordinates.X+j-1 >= 0 && Env->ScreenMatrix[Coordinates.Y+i][Coordinates.X+j-1] == '*')
					{ 
						return false;
					}
				}
			}
		}

		return true;
	}

	bool BlockBase::CollidesWith(BlockBase* Block)
	{
		for(int i=0; i<3; i++)
		{
			for(int j=0; j<3; j++) 
			{
				if(Block->shape[i][j])
				{
					if(CollidesPoint(Block->Coordinates.X+j, Block->Coordinates.Y+i))
						return true;
				}
			}
		}

		return false;
	}

	bool BlockBase::CollidesFloor() 
	{
		for(int i=0; i<3; i++)
		{
			bool b = CollidesPoint(Coordinates.X+i, Env->WindowHeight-1);
			if(b)
				return true;
		}

		return false;
	}

	bool BlockBase::CollidesPoint(int X, int Y) 
	{
		for(int i=0; i<3; i++)
		{
			for(int j=0; j<3; j++)
			{
				if(shape[i][j] &&  Coordinates.Y+i+1 == Y && Coordinates.X+j == X)
				{
					return true;
				}
			}
		}

		return false;
	}

	void BlockBase::Move(int DirX, int DirY) 
	{
		Coordinates.X += DirX;
		Coordinates.Y += DirY;
	}

	void BlockBase::Draw(HANDLE consoleOutputHandle, char **screenMatrix) const
	{
		for(int i=0; i<3; i++)
		{
			for(int j=0; j<3; j++)
			{
				if(shape[i][j])
				{
					if(!Ghost)
						screenMatrix[Coordinates.Y+i][Coordinates.X+j] = Color;
					else
						screenMatrix[Coordinates.Y+i][Coordinates.X+j] = -1;
				}
			}
		}
	}
	
	static void SetBackgroundColor(GameColor backgroundColor)
	{
		BackgroundColor = (backgroundColor & 0x0F) << 4;
	}
};

namespace GameColors
{
	enum Colors
	{
		// Color space is ARGB
		Blue = 9,
		Green = 10,
		Red = 12,
		Yellow = 14,
		Purple = 13,
		Cyan = 11,
		Black = 0,
		White = 15
	};
};

#endif