#pragma once
#include "Population.h"
class GeneticAlgorithm
{
	Individual* bestIndividual;

	int populationSize = 40;
	int generations = 100;
	Matrix* matrix;
	Population* population;


public:
	void algorithm();
	void showResult();
	GeneticAlgorithm(Matrix* m);
	~GeneticAlgorithm();
};

