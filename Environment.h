#ifndef ENVIRONMENT
#define ENVIRONMENT

class Environment {
public:
	char **ScreenMatrix;
	bool** CollisionMatrix;
	int WindowWidth;
	int WindowHeight;
	HANDLE ConsoleHandle;

	Environment::Environment(char** ScreenMatrix, bool** CollisionMatrix, HANDLE ConsoleHandle, int WindowWidth, int WindowHeight) : 
		ScreenMatrix(ScreenMatrix), CollisionMatrix(CollisionMatrix), ConsoleHandle(ConsoleHandle), WindowWidth(WindowWidth), 
		WindowHeight(WindowHeight) {

	}

};

#endif