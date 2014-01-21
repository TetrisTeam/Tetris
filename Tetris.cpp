#include <iostream>
#include <vector>
#include <iostream>
#include <conio.h>
#include <time.h>
#include <fstream>

#include "ConsoleGaming.h"
#include "BackgroundMusic.h"
#include "BlockBase.h"
#include "TBlock.h"
#include "LBlock.h"
#include "ZBlock.h"
#include "SquareBlock.h"
#include "LineBlock.h"
#include "Environment.h"

using namespace std;

HANDLE ConsoleHandle;

// Window constants
const int WindowWidth = 8;
const int WindowHeight = 25;
char **ScreenMatrix;
bool **CollisionMatrix;
char **PrevScreenMatrix;

// Shape
int ShapeSpeed = 1;
const char ShapeSymbol = '*';
// Game variables
unsigned long SleepDuration = 200;
BlockBase* CurrentBlock;
BlockBase* GhostBlock;

BackgroundMusic BgMusic;
Environment *Env;
int Level = 1;
int CurrentScore = 0;
int HighestScore = 0;
int Rows = 0;

CONSOLE_SCREEN_BUFFER_INFO csbi;

void RecalcGhost(BlockBase* CurrentBlock)
{
	GhostBlock->Coordinates.X = CurrentBlock->Coordinates.X;
	GhostBlock->Coordinates.Y = CurrentBlock->Coordinates.Y;

	while(true)
	{
		GhostBlock->Coordinates.Y += 1;

		if(GhostBlock->CollidesEnvironment())
		{
			GhostBlock->Coordinates.Y -= 1;
			break;
		}
	};
}

void AddBlock() {
	int x = rand() % (WindowWidth-4);
	int color = rand() % 7 + 9;
	int rotation = rand() % 4;
	int type = rand() % 5;

	BlockBase* t;
	type = 4;

	switch(type)
	{
	case 0:
		t = new TBlock(x, 0, rotation*90, false, color, ShapeSymbol, Env);
		break;
	case 1:
		t = new LBlock(x, 0, rotation*90, rand()%3, color, ShapeSymbol, Env);
		break;
	case 2:
		t = new ZBlock(x, 0, rotation*90, rand()%3, color, ShapeSymbol, Env);
		break;
	case 3:
		t = new LineBlock(x, 0, rotation*90, false, color, ShapeSymbol, Env);
		break;
	case 4:
		t = new SquareBlock(x, 0, rotation*90, false, color, ShapeSymbol, Env);
		break;
	}

	//Blocks.push_back(t);
	CurrentBlock = t;
	GhostBlock = new BlockBase(t);
	GhostBlock->Ghost = true;
	RecalcGhost(t);
}

void CheckForCombo() 
{
	for(int i=0; i<WindowHeight-1; i++)
	{
		bool hasCombo = true;
		for(int j=0; j<WindowWidth; j++)
		{
			if(ScreenMatrix[i][j] == 0 || ScreenMatrix[i][j] == 8)
				hasCombo = false;
		}

		if(hasCombo)
		{
			CurrentScore += 40;
			if(CurrentScore > HighestScore)
					HighestScore = CurrentScore;

			if(++Rows == 3)
				Level++;

			for(int j=0; j<WindowWidth; j++)
			{
				ScreenMatrix[i][j] = 8;				
			}
		}
	}
}

bool CheckIfFull()
{
	for(int i=0; i<WindowWidth; i++)
	{
		if(ScreenMatrix[2][i] >= 9 && ScreenMatrix[2][i] <= 15)
		{
			char str[] = "GAME OVER!";
			ClearScreen(ConsoleHandle);
			int stX = WindowWidth/2-sizeof(str)/(sizeof(char)*2);
			int stY = WindowHeight/2;

			COORD coord = {stX, stY};
			SetConsoleCursorPosition(ConsoleHandle, coord);
			std::cout << str;

			Sleep(5000);
			return true;
		}
	}

	return false;
}

bool Update()
{
	COORD direction = { 0, 0 };
	ShapeSpeed = 1;

	if (kbhit())
	{
		char key = getch();
		switch (key)
		{
		case 'a':
			direction.X = -1;
			break;
		case 'd':
			direction.X = 1;
			break;
		case 's':
			CurrentBlock->RotateBy(90);
			if(GhostBlock != NULL) {
				GhostBlock->RotateBy(90);
				RecalcGhost(CurrentBlock);
			}
			break;
		case ' ':
			ShapeSpeed = 2;
			break;
		case 27:
			SetConsoleTextAttribute(ConsoleHandle, 15);
			return true;
		};
	}	
	
	for(int i=0; i<ShapeSpeed; i++)
	{
		CurrentBlock->Coordinates.Y += 1;
		if(!CurrentBlock->CollidesEnvironment())
		{
			if(direction.X != 0)
			{
				CurrentBlock->Coordinates.X += direction.X;
				if(CurrentBlock->CollidesEnvironment())
				{
					CurrentBlock->Coordinates.X -= direction.X;
				}
				else if(GhostBlock != NULL)
				{
					RecalcGhost(CurrentBlock);
				}
			}

			if(GhostBlock != NULL && GhostBlock->Coordinates.Y - CurrentBlock->Coordinates.Y < 6) {
				delete GhostBlock;
				GhostBlock = NULL;
			}
		}
		else 
		{
			CurrentBlock->Coordinates.Y -= 1;

			int GlobalX = CurrentBlock->Coordinates.X;
			int GlobalY = CurrentBlock->Coordinates.Y;

			for(int i=0; i<CurrentBlock->Height; i++)
			{
				for(int j=0; j<CurrentBlock->Width; j++)
				{
					 if(CurrentBlock->shape[i][j])
					 {
						 CollisionMatrix[GlobalY+i][GlobalX+j] = 1;
					 }
				}
			}

			if(CheckIfFull())
				return true;
			CheckForCombo();
			AddBlock();
			break;
		}
	}

	return false;
}

void Draw()
{
	//Draws only the different symbols from the current frame and the last frame to remove blinking.

	for(int i=0; i<WindowHeight-1; i++) 
	{
		for(int j=0; j<WindowWidth; j++) 
		{
			PrevScreenMatrix[i][j] = ScreenMatrix[i][j];
			ScreenMatrix[i][j] = 0;
		}
	}

	/*for(std::vector<BlockBase*>::iterator it = Blocks.begin(); it != Blocks.end(); ++it) 
	{
		(*it)->Draw(ConsoleHandle, ScreenMatrix);
	}*/

	CurrentBlock->Draw(ConsoleHandle, ScreenMatrix);

	if(GhostBlock != NULL)
		GhostBlock->Draw(ConsoleHandle, ScreenMatrix);

	COORD coord = {1, 1};
	SetConsoleCursorPosition(ConsoleHandle, coord);
	SetConsoleTextAttribute(ConsoleHandle, 15);
	std::cout << "Level: " << Level << " Score: "<<CurrentScore;

	COORD coord2 = {WindowWidth, WindowHeight-1};
	SetConsoleCursorPosition(ConsoleHandle, coord2);
}

void Tetris()
{
	ClearScreen(ConsoleHandle);
	// Prepare rand
	srand(time(NULL));

	Env = new Environment(ScreenMatrix, CollisionMatrix, ConsoleHandle, WindowWidth, WindowHeight);
		
	for(int i=0; i<WindowHeight; i++) 
	{
		for(int j=0; j<WindowWidth; j++) 
		{
			PrevScreenMatrix[i][j] = 0;
			ScreenMatrix[i][j] = 0;
			CollisionMatrix[i][j] = 0;
		}
	}

	// Create the floor
	for(int i=0; i<WindowWidth; i++) 
	{
		ScreenMatrix[WindowHeight - 1][i] = ShapeSymbol;
		COORD coord = {i, WindowHeight - 1};
		SetConsoleCursorPosition(ConsoleHandle, coord);
		ConsoleColor color = 8;
		SetConsoleTextAttribute(ConsoleHandle, color);
		std::cout << ScreenMatrix[WindowHeight - 1][i];
		SetConsoleTextAttribute(ConsoleHandle, 7);

		CollisionMatrix[WindowHeight - 1][i] = 1;
	}
	
	// Create the first active shape
	AddBlock();

	while (true)
	{
		if(Update())
			return;
		Draw();
		Sleep(SleepDuration);
	}
}

void PrintInstructions()
{
	ClearScreen(ConsoleHandle);

	cout << "Tetriiiis" << endl;
	cout << "---------------------------------" << endl;
	cout << "Instruction" << endl;
	cout << "---------------------------------" << endl;
	cout << "Keys:" << endl;
	cout << "A - Left" << endl;
	cout << "D - Right" << endl;
	cout << "S - Rotate" << endl;
	cout << "SPACE - Speed Up" << endl;
	cout << "Esc - Back to menu" << endl;
	cout << "---------------------------------" << endl;
	cout << "Press any key to return to menu" << endl;

	while(!kbhit()) {
		Sleep(SleepDuration);
	}
}

void PrintHighestScore()
{
	int highestScore;
	
	ifstream ifs("score.txt");
	ifs >> highestScore;
	ifs.close();

	ClearScreen(ConsoleHandle);

	cout << "Tetriiiis" << endl;
	cout << "---------------------------------" << endl;
	
	cout << "Highest Score: " << endl;
	cout << HighestScore << endl;
	cout << "---------------------------------" << endl;
	cout << "Press any key to return to menu" << endl;

	while(!kbhit()) {
		Sleep(SleepDuration);
	}
}

int main() 
{
	ConsoleHandle = GetStdHandle( STD_OUTPUT_HANDLE );

	ScreenMatrix = new char *[WindowHeight];
	PrevScreenMatrix = new char *[WindowHeight];
	CollisionMatrix = new bool *[WindowHeight];
	for(int i = 0; i <WindowHeight; i++) {
		ScreenMatrix[i] = new char[WindowWidth];
		PrevScreenMatrix[i] = new char[WindowWidth];
		CollisionMatrix[i] = new bool[WindowWidth];
	}

	BgMusic.Start();
	int cellCount = csbi.dwSize.X *csbi.dwSize.Y;
	DWORD count;
	COORD homeCoords = { 0, 0 };

	FillConsoleOutputCharacter(
			ConsoleHandle,
			(TCHAR) ' ',
			cellCount,
			homeCoords,
			&count);

	while(true) 
	{
		ClearScreen(ConsoleHandle);

		cout << "Tetriiiis" << endl;
		cout << "---------------------------------" << endl;
		cout << "Menu" << endl;
		cout << "---------------------------------" << endl;
		cout << "1 - Start the game" << endl;
		cout << "2 - See instructions about the game" << endl;
		cout << "3 - Show the highest score the player has achieved in this session" << endl;
		cout << "4 - Exit the game" << endl;

		bool isMenuActive = true;
		while(isMenuActive)
		{
			if (kbhit())
			{
				char key = getch();
				switch (key)
				{
					case '1':
						Tetris();
						isMenuActive = false;
						break;
					case '2':
						PrintInstructions();
						isMenuActive = false;
						break;
					case '3':
						PrintHighestScore();
						isMenuActive = false;
						break;
					case '4':
						return 0;
				}
			}	
			Sleep(SleepDuration);
		}
	}

	return 0;
}