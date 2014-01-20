#include "BackgroundMusic.h"
#include <Windows.h>

void BackgroundMusic::StartThread()
{
	while(true)
	{
		int takt=220;
		float c2=523.251;
		float d2=587.330;
		float e2=622.254;
		float f2=698.456;
		float g2=783.991;
		float a2=830.609;
		float h2=932.328;
		float c3=1046.50;

		Beep(g2,takt*2);
		Beep(d2,takt*1);
		Beep(e2,takt*1);

		Beep(f2,takt*2);
		Beep(e2,takt*1);
		Beep(d2,takt*1);

		Beep(c2,takt*2);
		Beep(c2,takt*1);
		Beep(e2,takt*1);

		Beep(g2,takt*2);
		Beep(f2,takt*1);
		Beep(e2,takt*1);

		Beep(d2,takt*3);
		Beep(e2,takt*1);

		Beep(f2,takt*2);
		Beep(g2,takt*2);

		Beep(e2,takt*2);
		Beep(c2,takt*2);

		Beep(c2,takt*2);
		Sleep(takt*2);

		Sleep(takt*1);
		Beep(f2,takt*2);
		Beep(a2,takt*1);

		Beep(c3,takt*2);
		Beep(h2,takt*1);
		Beep(a2,takt*1);

		Beep(g2,takt*3);
		Beep(e2,takt*1);

		Beep(g2,takt*2);
		Beep(f2,takt*1);
		Beep(e2,takt*1);

		Beep(d2,takt*2);
		Beep(d2,takt*1);
		Beep(e2,takt*1);

		Beep(f2,takt*2);
		Beep(g2,takt*2);

		Beep(e2,takt*2);
		Beep(c2,takt*2);

		Beep(c2,takt*2);
		Sleep(takt*2);
	}
}

void BackgroundMusic::Start() 
{
	thread = new std::thread(&BackgroundMusic::StartThread, this);
}