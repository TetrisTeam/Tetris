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
public: 
	bool **shape;
	int Width;
	int Height;
	COORD Coordinates;
	int LastDrawingX;
	int LastDrawingY;
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
		LastDrawingX = -1;
		LastDrawingY = -1;
		this->Env = Env;
		Ghost = false;
		this->Flipped = flipped;
	}

	BlockBase::BlockBase(BlockBase* Block)
	{
		Width = Block->Width;
		Height = Block->Height;

		shape = new bool *[Height];
		for(int i=0; i<Height; i++)
		{
			shape[i] = new bool[Width];
			for(int j=0; j<Width; j++)
			{
				shape[i][j] = Block->shape[i][j];
			}
		}

		Coordinates.X = Block->Coordinates.X;
		Coordinates.Y = Block->Coordinates.Y;
		LastDrawingX = Block->LastDrawingX;
		LastDrawingY = Block->LastDrawingY;
		Rotation = Block->Rotation;
		Symbol = Block->Symbol;
		Color = Block->Color;
		Env = Block->Env;
		Ghost = false;		
	}

	/*	If block is destroyed, clear its last draw so it disappears 
		from screen (used only by the ghost block) */
	BlockBase::~BlockBase()
	{
		ClearLastDraw();

		for(int i=0; i<Height; i++)
			delete[] shape[i];
		delete shape;

		shape = NULL;
		Env = NULL;
	}

	/* Adjust initial rotation and flipping if there is one. */
	void BlockBase::init() 
	{
		if(Flipped)
		{
			bool **temp = new bool *[Height];
			for(int i=0; i<Height; i++)
			{
				temp[i] = new bool[Width];
				for(int j=0; j<Width; j++)
				{
					temp[i][j] = shape[i][j];
				}
			}

			for(int i=0; i<Height; i++)
			{
				for(int j=0; j<Width; j++)
				{
					shape[i][j] = temp[i][Width-j-1];
				}
				delete[] temp[i];
			}
			
			delete[] temp;
		}

		int t = Rotation;
		Rotation = 0;
		RotateBy(t);
	}

	void BlockBase::RotateBy(int angle) 
	{
		if(angle == 0)
			return;

		Rotation += angle;
		
		while(Rotation >= 360)
			Rotation -= 360;
		
		while(Rotation < 0)
			Rotation += 360;

		bool **temp = new bool *[Height];
		for(int i=0; i<Height; i++)
		{
			temp[i] = new bool[Width];
			
			for(int j=0; j<Width; j++)
			{
				temp[i][j] = shape[i][j];
			}
			delete[] shape[i];
		}
		delete[] shape;

		for(int i=0; i<angle/90; i++)
		{
			int t = Width;
			Width = Height;
			Height = t;

			shape = new bool *[Height];
			for(int i=0; i<Height; i++)
			{
				shape[i] = new bool[Width];
				for(int j=0; j<Width; j++)
				{
					shape[i][j] = temp[Width-j-1][i];
				}
			}
		}

		for(int i=0; i<Width; i++)
		{
			delete[] temp[i];
		}
		delete[] temp;
	}

	void BlockBase::UpdateCoordinates(const COORD& value)
	{
		this->Coordinates.X = value.X;
		this->Coordinates.Y = value.Y;
	}

	/*	The so-very-complicated collision detection.
		Uses a global matrix, called CollisionMatrix, 
		where each inactive block is outlined by ones.*/
	bool BlockBase::CollidesEnvironment()
	{
		for(int i=0; i<Height; i++)
		{
			for(int j=0; j<Width; j++) 
			{
				if(shape[i][j])
				{
					
					int GlobalX = Coordinates.X+j;
					int GlobalY = Coordinates.Y+i;
					if(Env->CollisionMatrix[GlobalY][GlobalX])
						return true;
				}
			}
		}

		return false;
	}

	/*	Removes figure from screen */
	void BlockBase::ClearLastDraw() 
	{
		for(int i=0; i<Height; i++)
		{
			for(int j=0; j<Width; j++)
			{
				if(shape[i][j])
				{
					COORD coord = {LastDrawingX+j, LastDrawingY+i};
					SetConsoleCursorPosition(Env->ConsoleHandle, coord);
					std::cout << ' ';
				}
			}
		}
	}

	/*	First removes figure from screen and then draws it on its new position.
		Note that if the coordinates of the last draw are the same as now, no drawing is made.*/
	void BlockBase::Draw(HANDLE consoleOutputHandle, char **screenMatrix)
	{
		if(LastDrawingX != -1)
		{
			if(LastDrawingX == Coordinates.X && LastDrawingY == Coordinates.Y)
				return;

			ClearLastDraw();
		}

		for(int i=0; i<Height; i++)
		{
			for(int j=0; j<Width; j++)
			{
				if(shape[i][j])
				{
					COORD coord = {Coordinates.X+j, Coordinates.Y+i};
					SetConsoleCursorPosition(consoleOutputHandle, coord);
					SetConsoleTextAttribute(consoleOutputHandle, (!Ghost ? Color : 8));
					std::cout << (!Ghost ? Symbol : '#');
				}
			}
		}

		LastDrawingX = Coordinates.X;
		LastDrawingY = Coordinates.Y;
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