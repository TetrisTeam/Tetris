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

HANDLE consoleHandle;

// Window constants
<<<<<<< HEAD
const int WindowWidth = 75;
const int WindowHeight = 25;
char **ScreenMatrix;
char **PrevScreenMatrix;

=======
const int WindowWidth = 8;
const int WindowHeight = 30;
>>>>>>> 31692bfe7e47199954c31a38c37b3b413711f6ba
// Shape
int ShapeSpeed = 1;
const char ShapeSymbol = '*';
// Game variables
unsigned long sleepDuration = 200;
// No need to reference the active shape, since it will always be the last shape in the list
vector<vector<GameObject>> shapes;
vector<BlockBase*> blocks;
BlockBase* ghostBlock;

BackgroundMusic backgroundMusic;
Environment *Env;
int Level = 1;
int CurrentScore = 0;
int HighestScore = 0;
int Rows = 0;

CONSOLE_SCREEN_BUFFER_INFO csbi;


void RecalcGhost(BlockBase* activeBlock)
{
	ghostBlock->Coordinates.X = activeBlock->Coordinates.X;
	ghostBlock->Coordinates.Y = activeBlock->Coordinates.Y;

	while(true)
	{
		bool colliding = false;

		for(std::vector<BlockBase*>::iterator it = blocks.begin(); it != blocks.end(); ++it) 
		{
			if((*it) == activeBlock)
				continue;

			if(ghostBlock->CollidesWith(*it))
			{
				colliding = true;
				break;
			}
		}

		if(!ghostBlock->CollidesFloor() && !colliding) 
		{
			ghostBlock->Coordinates.Y += 1;
		}
		else
		{			
			break;
		}
	};
}

void AddBlock() {
	int x = rand() % (WindowWidth-3);
	int color = rand() % 7 + 9;
	int rotation = rand() % 4;
	int type = rand() % 5;

	BlockBase* t;

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

<<<<<<< HEAD
	blocks.push_back(t);
	ghostBlock = new BlockBase(t);
	ghostBlock->Ghost = true;
	RecalcGhost(t);
}
=======
// Row status
int rowCounters[WindowHeight];
>>>>>>> 31692bfe7e47199954c31a38c37b3b413711f6ba

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
			ClearScreen(consoleHandle);
			int stX = WindowWidth/2-sizeof(str)/(sizeof(char)*2);
			int stY = WindowHeight/2;

			COORD coord = {stX, stY};
			SetConsoleCursorPosition(consoleHandle, coord);
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
	BlockBase* activeBlock = blocks[blocks.size()-1];
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
			activeBlock->RotateBy(90);
			if(ghostBlock != NULL) {
				ghostBlock->RotateBy(90);
				RecalcGhost(activeBlock);
			}
			break;
		case ' ':
			ShapeSpeed = 2;
			break;
		case 27:
			SetConsoleTextAttribute(consoleHandle, 15);
			return true;
		};
	}	
	
	for(int i=0; i<ShapeSpeed; i++)
	{
		bool colliding = false;

		for(std::vector<BlockBase*>::iterator it = blocks.begin(); it != blocks.end(); ++it) 
		{
			if((*it) == activeBlock)
				continue;

			if(activeBlock->CollidesWith(*it))
			{
				colliding = true;
				break;
			}
		}

<<<<<<< HEAD
		if(!activeBlock->CollidesFloor() && !colliding) 
=======
	if (hasReachedFloor)
	{
		// Return the coordinates to how they were
		for (randomAccess_iterator shapeNode = activeShape->begin(); shapeNode != activeShape->end(); ++shapeNode)
>>>>>>> 31692bfe7e47199954c31a38c37b3b413711f6ba
		{
			activeBlock->Coordinates.Y += 1;
			if(direction.X != 0 && activeBlock->CanGoSideways(direction.X)) {
				activeBlock->Coordinates.X += direction.X;
				if(ghostBlock != NULL)
					RecalcGhost(activeBlock);
			}

			if(ghostBlock != NULL && ghostBlock->Coordinates.Y - activeBlock->Coordinates.Y < 6)
				ghostBlock = NULL;
		}
		else
		{
			if(CheckIfFull())
				return true;
			CheckForCombo();
			AddBlock();
			break;
		}
<<<<<<< HEAD
=======
		
		// Update row counters
		for (randomAccess_iterator shapeNode = activeShape->begin(); shapeNode != activeShape->end(); ++shapeNode)
		{
			++rowCounters[shapeNode->Coordinates.Y];
		}
		
		// Check for full rows from bottom to top
		for (int i = WindowHeight - 1; i >= 0; --i)
		{
			if (rowCounters[i] == WindowWidth)
			{
				// Delete all parts of shapes in the current row
				// Move higher parts with one position down
				// (The shapes[0] is the floor, so we must skip it
				for (int shapeIndex = 1; shapeIndex < shapes.size(); ++shapeIndex) 
				{
					for (int shapePartIndex = shapes[shapeIndex].size() - 1; shapePartIndex >= 0; --shapePartIndex)
					{
						if (shapes[shapeIndex][shapePartIndex].Coordinates.Y == i)
						{
							// Replace it with the last one
							shapes[shapeIndex][shapePartIndex] = shapes[shapeIndex].back();
							// Remove the last one
							shapes[shapeIndex].pop_back();
						}
						else if (shapes[shapeIndex][shapePartIndex].Coordinates.Y < i)
						{
							++shapes[shapeIndex][shapePartIndex].Coordinates.Y;
						}
					}
				}
				
				// Move row counters
				for (int j = i; j > 0; --j)
				{
					rowCounters[j] = rowCounters[j - 1];
				}
				rowCounters[0] = 0;
				
				// Force second check for the same row
				++i;
			}
		}
		
		// Generate a new shape
		vector<GameObject> shape;
		int x = rand() % WindowWidth;
		shape.push_back(GameObject(x, 0, ShapeSymbol));
		shape.push_back(GameObject(x, 1, ShapeSymbol));
		shape.push_back(GameObject(x + 1, 0, ShapeSymbol));
		shape.push_back(GameObject(x + 1, 1, ShapeSymbol));
		// Add it to the list, set it as active
		shapes.push_back(shape);
>>>>>>> 31692bfe7e47199954c31a38c37b3b413711f6ba
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

	for(std::vector<BlockBase*>::iterator it = blocks.begin(); it != blocks.end(); ++it) 
	{
		(*it)->Draw(consoleHandle, ScreenMatrix);
	}

	if(ghostBlock != NULL)
		ghostBlock->Draw(consoleHandle, ScreenMatrix);

	for(int i=0; i<WindowHeight-1; i++) 
	{
		for(int j=0; j<WindowWidth; j++) 
		{
			if(ScreenMatrix[i][j] != PrevScreenMatrix[i][j]) 
			{
				COORD coord = {j, i};
				SetConsoleCursorPosition(consoleHandle, coord);				
				// its -1 if this is the ghost block
				if(ScreenMatrix[i][j] != -1) {
					ConsoleColor color = ScreenMatrix[i][j];
					SetConsoleTextAttribute(consoleHandle, color);
					std::cout << (ScreenMatrix[i][j] > 0 ? ShapeSymbol : ' ');
				}
				else {
					SetConsoleTextAttribute(consoleHandle, 8);
					std::cout << '#';
				}
			}
		}
	}

	COORD coord = {1, 1};
	SetConsoleCursorPosition(consoleHandle, coord);
	SetConsoleTextAttribute(consoleHandle, 15);
	std::cout << "Level: " << Level << " Score: "<<CurrentScore;

	COORD coord2 = {WindowWidth, WindowHeight-1};
	SetConsoleCursorPosition(consoleHandle, coord2);
}

void Tetris()
{
	ClearScreen(consoleHandle);
	// Prepare rand
	srand(time(NULL));
<<<<<<< HEAD

	Env = new Environment(ScreenMatrix, WindowWidth, WindowHeight);
		
	for(int i=0; i<WindowHeight; i++) 
=======
	
	// Create the floor
	vector<GameObject> floor;
	for (int i = 0; i < WindowWidth; i++)
>>>>>>> 31692bfe7e47199954c31a38c37b3b413711f6ba
	{
		for(int j=0; j<WindowWidth; j++) 
		{
			PrevScreenMatrix[i][j] = 0;
			ScreenMatrix[i][j] = 0;
		}
	}
<<<<<<< HEAD

	// Create the floor
	for(int i=0; i<WindowWidth; i++) 
	{
		ScreenMatrix[WindowHeight - 1][i] = ShapeSymbol;
		COORD coord = {i, WindowHeight - 1};
		SetConsoleCursorPosition(consoleHandle, coord);
		ConsoleColor color = 8;
		SetConsoleTextAttribute(consoleHandle, color);
		std::cout << ScreenMatrix[WindowHeight - 1][i];
		SetConsoleTextAttribute(consoleHandle, 7);
=======
	shapes.push_back(floor);
	
	// Init row counters
	for (int i = 0; i < WindowHeight; ++i)
	{
		rowCounters[i] = 0;
>>>>>>> 31692bfe7e47199954c31a38c37b3b413711f6ba
	}

	// Create the first active shape
	AddBlock();

	while (true)
	{
		if(Update())
			return;
		Draw();
		Sleep(sleepDuration);
	}
}

GameObject* GetShapeFromCoords(int x, int y) {
	return NULL;
}

void PrintInstructions()
{
	ClearScreen(consoleHandle);

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
		Sleep(sleepDuration);
	}
}

void PrintHighestScore()
{
	int highestScore;
	
	ifstream ifs("score.txt");
	ifs >> highestScore;
	ifs.close();

	ClearScreen(consoleHandle);

	cout << "Tetriiiis" << endl;
	cout << "---------------------------------" << endl;
	
	cout << "Highest Score: " << endl;
	cout << HighestScore << endl;
	cout << "---------------------------------" << endl;
	cout << "Press any key to return to menu" << endl;

	while(!kbhit()) {
		Sleep(sleepDuration);
	}
}

int main() 
{
	consoleHandle = GetStdHandle( STD_OUTPUT_HANDLE );

	ScreenMatrix = new char *[WindowHeight];
	PrevScreenMatrix = new char *[WindowHeight];
	for(int i = 0; i <WindowHeight; i++) {
		ScreenMatrix[i] = new char[WindowWidth];
		PrevScreenMatrix[i] = new char[WindowWidth];
	}

	backgroundMusic.Start();
	int cellCount = csbi.dwSize.X *csbi.dwSize.Y;
	DWORD count;
	COORD homeCoords = { 0, 0 };

	FillConsoleOutputCharacter(
			consoleHandle,
			(TCHAR) ' ',
			cellCount,
			homeCoords,
			&count);

	while(true) 
	{
		ClearScreen(consoleHandle);

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
			Sleep(sleepDuration);
		}
	}

	return 0;
}