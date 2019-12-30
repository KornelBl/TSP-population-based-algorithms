#pragma once
#include "Individual.h"
#include <math.h>

class Population
{
	double crossProbability = 0.70;
	double mutationProbability = 0.05;

	Individual* bestIndividual;

	int size;
	int individualSize;
	Matrix* matrix;
	Individual** main;
	Individual** next;
	Individual** matingPool;
	double* fitness = NULL;
	

public:
	void evaluation();
	void selection();
	void crossover();
	void mutation();
	void succesion();
	Individual* getBestIndividual();
	Population(int size, Matrix* matrix);
	~Population(); 
};

