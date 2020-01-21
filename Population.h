#pragma once
#include "Individual.h"
#include "CrossoverOperator.h"
#include "Mutator.h"
#include "Selector.h"
#include <math.h>

class Population
{
	double crossProbability = 0.75;
	double mutationProbability = 0.03;
	int elitism = 2;



	Individual* bestIndividual;
	CrossoverOperator* crosser;
	Mutator* mutator;
	Selector* selector;


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
	Population(Matrix* matrix, int size, int eliteSize,double crossProbability, double mutationProbability, CrossoverOperator* crosser = NULL, Selector* selector = NULL);
	~Population(); 
};

