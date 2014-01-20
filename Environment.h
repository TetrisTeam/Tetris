#ifndef ENVIRONMENT
#define ENVIRONMENT

class Environment {
public:
	char **ScreenMatrix;
	int WindowWidth;
	int WindowHeight;

	Environment::Environment(char** ScreenMatrix, int WindowWidth, int WindowHeight) : 
		ScreenMatrix(ScreenMatrix), WindowWidth(WindowWidth), WindowHeight(WindowHeight) {

	}

};

#endif