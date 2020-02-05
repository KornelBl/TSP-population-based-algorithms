#pragma once
#include "Population.h"
class GeneticAlgorithm
{
	Individual* bestIndividual;

	int populationSize = 50;
	int generations = 1000;
	Matrix* matrix;
	Population* population;


public:
	void algorithm();
	void showResult();
	int getBestCost();
	GeneticAlgorithm(Matrix* m,int populationSize,int eliteSize,int generations, double crossProbability,
	double mutationProbability, CrossoverOperator* crosser, Selector* selector = NULL,int startPath = 0);
	~GeneticAlgorithm();
};

