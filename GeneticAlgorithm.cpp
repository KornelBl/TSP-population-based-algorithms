#include "pch.h"
#include "GeneticAlgorithm.h"


void GeneticAlgorithm::algorithm()
{
	//generate new population
	population = new Population(populationSize, matrix);
	
	for (int k = 0; k < generations; k++) {
		population->evaluation();
		population->selection();
		population->crossover();
		population->mutation();
		population->succesion();
	}
	bestIndividual = new Individual(population->getBestIndividual());

}

void GeneticAlgorithm::showResult()
{
	std::cout << "Najkrotsza sciezka: ";
	for (int i = 0; i < matrix->vertices; i++) {
		std::cout << bestIndividual->path[i] << "->";
	}
	std::cout << "0\nKoszt: " << bestIndividual->getCost() << std::endl;
}

GeneticAlgorithm::GeneticAlgorithm(Matrix* m)
{
	matrix = m;
}


GeneticAlgorithm::~GeneticAlgorithm()
{
	delete bestIndividual, population;
}
