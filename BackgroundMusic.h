#ifndef BACKGROUND_MUSIC
#define BACKGROUND_MUSIC

#include <iostream>       // std::cout
#include <thread>         // std::thread

class BackgroundMusic 
{
private:
	std::thread *thread;
	void StartThread();
public:	
	void Start();
};

#endif