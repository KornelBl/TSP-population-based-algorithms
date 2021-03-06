#include "pch.h"
#include "Population.h"

//usuwanie przy rozmnażaniu



void Population::generateRandomPopulation()
{
	Individual* temp;
	for (int i = 0; i < size; i++) {
		temp = new Individual(matrix);
		for (int j = i; j > -1; j--) {
			if (j == 0) {
				main[0] = temp;
				break;
			}
			if (temp->getCost() < main[j - 1]->getCost()) { //moze to usunac bo po co po koszcie sortowac
				main[j] = main[j - 1];
				continue;
			}
			main[j] = temp;
			break;
		}
	}
	bestIndividual = new Individual(main[0]);
}

void Population::generateNNPopulation()
{
	Individual* temp;
	int* path; 
	int* order = new int[matrix->vertices];
	srand(time(NULL));
	int* helper = new int[matrix->vertices];
	int* visited = new int[matrix->vertices];
	for (int i = 0; i < matrix->vertices; i++) {
		helper[i] = i;
		visited[i] = i;
	}
	int minIndex, index, minCost, cost, zeroAt;
	int at = 0;
	
	for (int i = 0; i < matrix->vertices && i<size ; i++) {
		index = rand() % (matrix->vertices - i);
		cost = 0;
		zeroAt = 0;
		path = new int[matrix->vertices + 1];
		//tworzenie
		order[0] = at = helper[index];
		Individual::swap(visited, matrix->vertices - 1, helper[index]);
		for (int k = 0; k < matrix->vertices - 1; k++) {
			minCost = INT_MAX;
			for (int j = 0; j < matrix->vertices - 1 - k; j++) {
				if (matrix->cost(at, visited[j]) < minCost) {
					minCost = matrix->cost(at, visited[j]);
					minIndex = j;
				}
			}
			at = order[k + 1] = visited[minIndex];
			if (at == 0) zeroAt = k + 1;
			cost += minCost;
			Individual::swap(visited, matrix->vertices - k - 2, minIndex);
		}
		cost += matrix->cost(order[matrix->vertices - 1], order[0]);
		//przepisanie sciezki
		path[0] = path[matrix->vertices] = 0;
		at = 1;
		for (int k = zeroAt + 1; k < matrix->vertices; k++) {
			path[at] = order[k];
			at++;
		}
		for (int k = 0; k < zeroAt; k++) {
			path[at] = order[k];
			at++;
		}

		//wkładanie osobnika do populacji
		temp = new Individual(path, cost, matrix->vertices);
		for (int j = i; j > -1; j--) {
			if (j == 0) {
				main[0] = temp;
				break;
			}
			if (temp->getCost() < main[j - 1]->getCost()) { //moze to usunac bo po co po koszcie sortowac
				main[j] = main[j - 1];
				continue;
			}
			main[j] = temp;
			break;
		}
		Individual::swap(helper, matrix->vertices - i - 1, index);

		for (int k = 0; k < matrix->vertices; k++) {
			visited[k] = k;
		}

	}

	//dodanie losowych osobnikow do populacji
	for (int i = matrix->vertices; i < size; i++) {
		temp = new Individual(matrix);
		for (int j = i; j > -1; j--) {
			if (j == 0) {
				main[0] = temp;
				break;
			}
			if (temp->getCost() < main[j - 1]->getCost()) { //moze to usunac bo po co po koszcie sortowac
				main[j] = main[j - 1];
				continue;
			}
			main[j] = temp;
			break;
		}
	}

	bestIndividual = new Individual(main[0]);

	delete[] helper;
	delete[] visited;
	delete[] order;

}

void Population::print()
{
	for (int i = 0; i < size; i++) {
		main[i]->print();
	}
}

void Population::evaluation()
{
	double maxCost = main[size - 1]->getCost();
	double minCost = main[0]->getCost();
	//wyciagnac maksima i minima z nieposortowanej populacji !!!
	double costDifference = maxCost - minCost;

	double minFit = 1.0;
	double maxFit = 3.0;

	if (costDifference == 0) {
		costDifference = 1;
	}

	for (int i = 0; i < size; i++) {
		fitness[i] = 1.0 / (double)main[i]->getCost();
		//fitness[i] = minFit + (maxFit - minFit) * (maxCost - main[i]->getCost()) / costDifference;
	}

}

void Population::selection()
{
	delete[] matingPool;
	matingPool = selector->selectMatingPool(main, fitness, size);
}

void Population::crossover()
{
	srand(time(NULL));
	//one point crossover

	for (int i = elitism; i < size ; i+=2){
		//probability

		//std::cout << "NOWE OSOBNIKI" << std::endl;
		if ((double)rand() / (RAND_MAX + 1.0) < crossProbability) {
			//one point crossover
			crosser->cross(matingPool[i], matingPool[i + 1]);
			next[i] = crosser->getChild1();
			next[i + 1] = crosser->getChild2();
		}
		else {
			next[i] = new Individual(matingPool[i]);
			next[i+1] = new Individual(matingPool[i + 1]);
		}
	}

}

void Population::mutation()
{
	for (int i = elitism; i < size; i++) {
		mutator->mutate(next[i]);
	}
}

void Population::succesion()
{
	for (int i = elitism; i < size; i++) {
		delete main[i];
		for (int j = i; j > -1; j--) {
			if (j == 0) {
				main[0] = next[i];
				break;
			}
			if (next[i]->getCost() < main[j - 1]->getCost()) { //moze to usunac bo po co po koszcie sortowac
				main[j] = main[j - 1];
				continue;
			}
			main[j] = next[i];
			break;
		}
	}
	if (main[0]->getCost() < bestIndividual->getCost()) {
		delete bestIndividual;
		bestIndividual = new Individual(main[0]);
	}
}

Individual * Population::getBestIndividual()
{
	return bestIndividual;
}

Population::Population(Matrix* matrix, int size, int eliteSize, double crossProbability, double mutationProbability,  CrossoverOperator* crosser, Selector* selector,int startPath)
{
	this->matrix = matrix;
	this->size = size;
	this->elitism = eliteSize;
	this->crossProbability = crossProbability;
	this->mutationProbability = mutationProbability;
	this->main = new Individual*[size];
	this->next = new Individual*[size];
	this->matingPool = new Individual*[size];
	this->fitness = new double[size];
	this->individualSize = matrix->vertices;
	this->mutator = new swapMutator(matrix, mutationProbability);
	this->crosser = crosser;
	this->selector = selector;

	if(startPath == 0)
		generateRandomPopulation();
	else 
		generateNNPopulation();
}

Population::~Population()
{
	for (int i = 0; i < size; i++) {
		delete main[i];
	}
	delete[] main;
	delete[] next;
	delete[] matingPool;
	delete[] fitness;

	delete bestIndividual;
	delete crosser;
	delete mutator;
	delete selector;
}
