#include "pch.h"
#include "Selector.h"


Selector::Selector()
{
}


Selector::~Selector()
{
}

Individual** RouletteSelector::selectMatingPool(Individual** main, float * fitness, int size)
{
	//roulette
	Individual** matingPool = new Individual*[size];
	double* thresholds = new double[size];
	thresholds[0] = fitness[0];
	for (int i = 1; i < size; i++) {
		thresholds[i] = thresholds[i - 1] + fitness[i];
	}

	for (int i = 0; i < size; i++) {
		double ball = ((double)rand() / (RAND_MAX + 1.0)) * thresholds[size - 1];
		for (int j = 0; j < size; j++) {
			if (ball < thresholds[j]) {
				matingPool[i] = main[j];
				break;
			}
		}
	}
	delete[] thresholds;
	return matingPool;
}
