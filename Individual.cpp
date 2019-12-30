#include "pch.h"
#include "Individual.h"


void Individual::swap(int * T, int a, int b)
{
	int buf = T[a];
	T[a] = T[b];
	T[b] = buf;
}

void Individual::generateRandom(Matrix* m)
{
	this->size = m->vertices;
	path = new int[size + 1];
	cost = 0;

	//losowa droga startowa
	srand(time(NULL));
	int* helper = new int[size - 1];
	for (int i = 0; i < size - 1; i++) {
		helper[i] = i + 1;
	}
	int index;
	path[0] = path[size] = 0;
	for (int i = 0; i < size - 1; i++) {
		index = rand() % (size - i - 1);
		path[i + 1] = helper[index];
		cost += m->cost(path[i], path[i + 1]);
		swap(helper, size - i - 2, index);
	}
	cost += m->cost(path[size - 1],0);
	delete[] helper;
}

int Individual::getCost()
{
	return cost;
}

Individual::Individual(Matrix* m)
{
	generateRandom(m);
}

Individual::Individual(Individual * pattern)
{
	this->size = pattern->size;
	this->cost = pattern->cost;
	this->path = new int[size + 1];
	path[0] = path[size] = 0;
	for (int i = 1; i < size; i++)
		path[i] = pattern->path[i];
}

Individual::Individual(int * path, int cost, int size)
{
	this->size = size;
	this->path = path;
	this->cost = cost;
}


Individual::~Individual()
{
	delete[] path;
}
