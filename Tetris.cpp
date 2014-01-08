#include <iostream>
#include <vector>
#include <iostream>
#include <conio.h>
#include <time.h>
#include <fstream>

#include "ConsoleGaming.h"

using namespace std;

HANDLE consoleHandle;

typedef vector<GameObject>::iterator randomAccess_iterator;
typedef vector<GameObject>::const_iterator const_iterator;

// Window constants
const int WindowWidth = 70;
const int WindowHeight = 30;
// Shape
const int ShapeSpeed = 1;
const char ShapeSymbol = '*';
// Game variables
unsigned long sleepDuration = 200;
// No need to reference the active shape, since it will always be the last shape in the list
vector<vector<GameObject>> shapes;


void Update()
{
	COORD direction = { 0, 0 };

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
		};
	}

	bool hasReachedFloor = false;
	vector<vector<GameObject>>::iterator activeShape = shapes.end() - 1;
	for (randomAccess_iterator shapeNode = activeShape->begin(); shapeNode != activeShape->end(); ++shapeNode)
	{
		shapeNode->Coordinates.X += direction.X;
		shapeNode->Coordinates.Y += ShapeSpeed;

		// Loop trough all shapes, check if we are colliding. If that's the case, the shape has reached its destination, leave it there and generate a new shape
		typedef vector<vector<GameObject>>::const_iterator it;
		// Since the active shape is always the last, loop until before the active shape, otherwise we'll detect false collision
		for (it shape = shapes.begin(); shape != shapes.end() - 1; ++shape)
		{
			for (const_iterator shapePoint = shape->begin(); shapePoint != shape->end(); ++shapePoint)
			{
				if (shapePoint->Coordinates.X == shapeNode->Coordinates.X && shapePoint->Coordinates.Y == shapeNode->Coordinates.Y)
				{
					hasReachedFloor = true;
					break;
				}
			}
			// This might go in the loop condition, but I believe it's much clear here
			if (hasReachedFloor)
				break;
		}
	}

	// Generate a new shape
	if (hasReachedFloor)
	{
		// Return the coordinates to how they were
		for (randomAccess_iterator shapeNode = activeShape->begin(); shapeNode != activeShape->end(); ++shapeNode)
		{
			shapeNode->Coordinates.X -= direction.X;
			shapeNode->Coordinates.Y -= ShapeSpeed;
		}
		
		vector<GameObject> shape;
		int x = rand() % WindowWidth;
		shape.push_back(GameObject(x, 0, ShapeSymbol));
		shape.push_back(GameObject(x, 1, ShapeSymbol));
		shape.push_back(GameObject(x + 1, 0, ShapeSymbol));
		shape.push_back(GameObject(x + 1, 1, ShapeSymbol));
		// Add it to the list, set it as active
		shapes.push_back(shape);
	}
}

void Draw()
{
	ClearScreen(consoleHandle);

	typedef vector<vector<GameObject>>::const_iterator it;
	for (it shape = shapes.begin(); shape != shapes.end(); ++shape)
	{
		for (const_iterator shapeNode = shape->begin(); shapeNode != shape->end(); ++shapeNode)
		{
			shapeNode->Draw(consoleHandle);
		}
	}
}

void Tetris()
{
	// Prepare rand
	srand(time(NULL));
	
	// Create the floor
	vector<GameObject> floor;
	for (int i = 0; i < WindowWidth - 1; i++)
	{
		floor.push_back(GameObject(i, WindowHeight - 1, ShapeSymbol));
	}
	shapes.push_back(floor);


	// Create the first active shape
	vector<GameObject> shape;
	int x = rand() % WindowWidth;
	shape.push_back(GameObject(x, 0, ShapeSymbol));
	shape.push_back(GameObject(x, 1, ShapeSymbol));
	shape.push_back(GameObject(x + 1, 0, ShapeSymbol));
	shape.push_back(GameObject(x + 1, 1, ShapeSymbol));
	// Add it to the list, setting it as active
	shapes.push_back(shape);

	while (true)
	{
		Update();
		Draw();
		Sleep(sleepDuration);
	}
}

void PrintInstructions()
{
	ClearScreen(consoleHandle);

	cout << "Tetriiiis" << endl;
	cout << "---------------------------------" << endl;
	cout << "Instruction" << endl;
	cout << "---------------------------------" << endl;
	cout << "Keys:" << endl;
	cout << "a - left" << endl;
	cout << "d - right" << endl;
	cout << "Esc - back to menu" << endl;
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
	cout << highestScore << endl;
	cout << "---------------------------------" << endl;
	cout << "Press any key to return to menu" << endl;

	while(!kbhit()) {
		Sleep(sleepDuration);
	}

}


int main() {
	consoleHandle = GetStdHandle( STD_OUTPUT_HANDLE );

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