#include "pch.h"
#include "GeneticAlgorithm.h"


void GeneticAlgorithm::algorithm()
{

	//population->print();

	for (int k = 0; k < generations; k++) {
		population->evaluation();
		population->selection();
		population->crossover();
		population->mutation();
		population->succesion();
	}
	bestIndividual = new Individual(population->getBestIndividual());
	//population->print();
}

void GeneticAlgorithm::showResult()
{
	std::cout << "Najkrotsza sciezka: ";
	for (int i = 0; i < matrix->vertices; i++) {
		std::cout << bestIndividual->path[i] << "->";
	}
	std::cout << "0\nKoszt: " << bestIndividual->getCost() << std::endl;
}

GeneticAlgorithm::GeneticAlgorithm(Matrix* m, int populationSize, int eliteSize, int generations,
	double crossProbability, double mutationProbability, CrossoverOperator* crosser, Selector* selector)
{
	matrix = m;
	this->generations = generations;
	//generate new population
	population = new Population(matrix,populationSize,eliteSize,crossProbability,mutationProbability, crosser, selector);
}


GeneticAlgorithm::~GeneticAlgorithm()
{
	delete bestIndividual;
	delete population;
}
