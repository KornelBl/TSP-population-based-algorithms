#include "pch.h"
#include "Timing.h"

void Timing::startCount()
{
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&beginTime);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
}

void Timing::endCount()
{
	LARGE_INTEGER endTime;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&endTime);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	result = (double)(endTime.QuadPart - beginTime.QuadPart) * 1000 / (freq.QuadPart / 1000);
}

double Timing::getResult()
{
	return result;
}

Timing::Timing()
{
	QueryPerformanceFrequency(&freq);

}


Timing::~Timing()
{
}
