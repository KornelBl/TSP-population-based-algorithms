#pragma once
#include "Individual.h"
#include "CrossoverOperator.h"
#include <math.h>

class Population
{
	double crossProbability = 0.75;
	double mutationProbability = 0.02;

	Individual* bestIndividual;
	CrossoverOperator* crosser;
	
	int size;
	int individualSize;
	Matrix* matrix;
	Individual** main;
	Individual** next;
	Individual** matingPool;
	double* fitness;
	
	void generateRandomPopulation();
	void generateNNPopulation();


public:
	void print();
	void evaluation();
	void selection();
	void crossover();
	void mutation();
	void succesion();
	Individual* getBestIndividual();
	Population(int size, Matrix* matrix);
	~Population(); 
};

