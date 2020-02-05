#pragma once
#include <Windows.h>

class Timing
{
private:
	LARGE_INTEGER freq;
	LARGE_INTEGER beginTime;
	double result; // mikrosekundy
public:
	void startCount();
	void endCount();
	double getResult();
	Timing();
	~Timing();
};

