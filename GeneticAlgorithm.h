#pragma once
#include "Population.h"
class GeneticAlgorithm
{
	Individual* bestIndividual;

	int populationSize = 20;
	int generations = 20'000;
	Matrix* matrix;
	Population* population;


public:
	void algorithm();
	void showResult();
	GeneticAlgorithm(Matrix* m);
	~GeneticAlgorithm();
};

