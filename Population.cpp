#include "pch.h"
#include "Population.h"

//usuwanie przy rozmna¿aniu



void Population::evaluation()
{
	double maxCost = main[size - 1]->getCost();
	double minCost = main[0]->getCost();
	//wyciagnac maksima i minima z nieposortowanej populacji !!!
	double costDifference = maxCost - minCost;

	double minFit = 1.0;
	double maxFit = 2.0;

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
	//roulette
	srand(time(NULL));
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
			}
		}
	}
	delete[] thresholds;
}

void Population::crossover()
{
	srand(time(NULL));
	//one point crossover
	int crossPoint,cost,at;
	int* path = NULL;
	int* visited = new int[individualSize];
	for (int i = 0; i < individualSize; i++)
		visited[i] = 0;


	for (int i = 0; i < size ; i+=2){
		//probability
		if ((double)rand() / (RAND_MAX + 1.0) < crossProbability) {
			//one point crossover
			crossPoint = rand() % (individualSize - 1) + 1;

			//child 1
			path = new int[individualSize + 1];
			cost = 0;
			path[0] = path[individualSize] = 0;
			for (int j = 1; j < crossPoint; j++) {
				path[j] = matingPool[i]->path[j];
				cost += matrix->cost(path[j - 1], path[j]);
				visited[path[j]] = 1;
			}
			at = crossPoint;
			for (int j = 1; j<individualSize; j++) {
				if (visited[matingPool[i + 1]->path[j]]) {
					visited[matingPool[i + 1]->path[j]] = 0;
					continue;
				}
				path[at] = matingPool[i + 1]->path[j];
				cost += matrix->cost(path[at - 1], path[at]);
				at++;
			}
			cost += matrix->cost(path[individualSize - 1], 0);
			next[i] = new Individual(path, cost, individualSize);
			
			
			//child2
			path = new int[individualSize + 1];
			cost = 0;
			path[0] = path[individualSize] = 0;
			for (int j = 1; j < crossPoint; j++) {
				path[j] = matingPool[i+1]->path[j];
				cost += matrix->cost(path[j - 1], path[j]);
				visited[path[j]] = 1;
			}
			at = crossPoint;
			for (int j = 1; at < individualSize; j++) {
				if (visited[matingPool[i]->path[j]]) {
					visited[matingPool[i]->path[j]] = 0;
					continue;
				}
				path[at] = matingPool[i]->path[j];
				cost += matrix->cost(path[at - 1], path[at]);
				at++;
			}
			cost += matrix->cost(path[individualSize - 1], 0);
			next[i+1] = new Individual(path, cost, individualSize);

		}
		else {
			next[i] = new Individual(matingPool[i]);
			next[i+1] = new Individual(matingPool[i + 1]);
		}
	}

	delete[] visited;
}

void Population::mutation()
{
	srand(time(NULL));
	for (int i = 0; i < size; i++) {
		for (int j = 1; j < individualSize; j++)
		{
			if ((double)rand() / RAND_MAX < mutationProbability) {
				int ind1 = j;
				int ind2 = rand() % (individualSize - 1) + 1;

				
				if (ind2 > ind1) {
					int bufor = ind2;
					ind2 = ind1;
					ind1 = bufor;
				}

				if (ind1 - ind2 == 1) {
					next[i]->cost -= matrix->cost(next[i]->path[ind2], next[i]->path[ind1]);
					next[i]->cost += matrix->cost(next[i]->path[ind1], next[i]->path[ind2]);

				}
				else {
					next[i]->cost -= matrix->cost(next[i]->path[ind1 - 1], next[i]->path[ind1]);
					next[i]->cost -= matrix->cost(next[i]->path[ind2], next[i]->path[ind2 + 1]);
					next[i]->cost += matrix->cost(next[i]->path[ind1 - 1], next[i]->path[ind2]);
					next[i]->cost += matrix->cost(next[i]->path[ind1], next[i]->path[ind2 + 1]);
				}

				next[i]->cost -= matrix->cost(next[i]->path[ind2 - 1], next[i]->path[ind2]);
				next[i]->cost += matrix->cost(next[i]->path[ind2 - 1], next[i]->path[ind1]);
				next[i]->cost -= matrix->cost(next[i]->path[ind1], next[i]->path[ind1 + 1]);
				next[i]->cost += matrix->cost(next[i]->path[ind2], next[i]->path[ind1 + 1]);

				Individual::swap(next[i]->path, ind1, ind2);
			}
		}
	}
}

void Population::succesion()
{
	for (int i = 0; i < size; i++) {
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

Population::Population(int size, Matrix* matrix)
{
	this->matrix = matrix;
	this->size = size;
	this->main = new Individual*[size];
	this->next = new Individual*[size];
	this->matingPool = new Individual*[size];
	this->fitness = new double[size];
	this->individualSize = matrix->vertices;
	
	

	int* path = new int[matrix->vertices + 1];

	//losowa droga startowa
	srand(time(NULL));
	int* helper = new int[matrix->vertices - 1];
	for (int i = 0; i < matrix->vertices - 1; i++) {
		helper[i] = i + 1;
	}
	int minIndex;
	int at = 0;
	int minCost = INT_MAX;
	path[0] = path[matrix->vertices] = 0;
	for (int i = 0; i < matrix->vertices - 1; i++) {
		minCost = INT_MAX;
		for (int j = 0; j < matrix->vertices - 1 - i; j++) {
			if (matrix->cost(at, helper[j]) < minCost) {
				minCost = matrix->cost(at, helper[j]);
				minIndex = j;
			}
		}
		at = path[i + 1] = helper[minIndex];
		Individual::swap(helper, matrix->vertices - i - 2, minIndex);
	}

	int cost = matrix->distanceFunction(path);
	delete[] helper;
	main[0] = new Individual(path, cost, individualSize);




	Individual* temp;
	for (int i = 1; i < size; i++) {
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

Population::~Population()
{
	delete bestIndividual;
	for (int i = 0; i < size; i++) {
		delete main[i];
	}
	delete[] main, next, matingPool, fitness;
}
