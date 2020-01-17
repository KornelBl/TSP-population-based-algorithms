#include "pch.h"
#include "Mutator.h"


Mutator::Mutator(Matrix* m,double mutationProbability)
{
	this->mutationProbability = mutationProbability;
	this->m = m;
}


Mutator::~Mutator()
{
}

void swapMutator::mutate(Individual* individual, double probability)
{
	if (probability == -1) probability = mutationProbability;
	for (int j = 1; j < m->vertices; j++)
	{
		if ((double)rand() / RAND_MAX < probability) {
			int ind1 = j;
			int ind2 = rand() % (m->vertices - 1) + 1;


			if (ind2 > ind1) {
				int bufor = ind2;
				ind2 = ind1;
				ind1 = bufor;
			}

			if (ind1 - ind2 == 1) {
				individual->cost -= m->cost(individual->path[ind2], individual->path[ind1]);
				individual->cost += m->cost(individual->path[ind1], individual->path[ind2]);

			}
			else {
				individual->cost -= m->cost(individual->path[ind1 - 1], individual->path[ind1]);
				individual->cost -= m->cost(individual->path[ind2], individual->path[ind2 + 1]);
				individual->cost += m->cost(individual->path[ind1 - 1], individual->path[ind2]);
				individual->cost += m->cost(individual->path[ind1], individual->path[ind2 + 1]);
			}

			individual->cost -= m->cost(individual->path[ind2 - 1], individual->path[ind2]);
			individual->cost += m->cost(individual->path[ind2 - 1], individual->path[ind1]);
			individual->cost -= m->cost(individual->path[ind1], individual->path[ind1 + 1]);
			individual->cost += m->cost(individual->path[ind2], individual->path[ind1 + 1]);

			Individual::swap(individual->path, ind1, ind2);
		}
	}


	for (int _ = 0; _ < 2; _++) {
		if ((double)rand() / RAND_MAX < probability) {
			//zastepuje wylosowanie 0
			int ind = rand() % (m->vertices - 1) + 1;
			//koszt

			if (ind == 1) {
				individual->cost -= m->cost(individual->path[m->vertices - 1], 0);
				individual->cost -= m->cost(individual->path[ind], individual->path[ind + 1]);

				individual->cost += m->cost(0, individual->path[ind + 1]);
				individual->cost += m->cost(individual->path[m->vertices - 1], individual->path[ind]);

			}
			else if (ind == m->vertices - 1) {
				individual->cost -= m->cost(0, individual->path[1]);
				individual->cost -= m->cost(individual->path[ind - 1], individual->path[ind]);

				individual->cost += m->cost(individual->path[ind], individual->path[1]);
				individual->cost += m->cost(individual->path[ind - 1], 0);
			}
			else {

				individual->cost -= m->cost(0, individual->path[1]);
				individual->cost -= m->cost(individual->path[m->vertices - 1], 0);

				individual->cost -= m->cost(individual->path[ind], individual->path[ind + 1]);
				individual->cost -= m->cost(individual->path[ind - 1], individual->path[ind]);


				individual->cost += m->cost(0, individual->path[ind + 1]);
				individual->cost += m->cost(individual->path[ind - 1], 0);

				individual->cost += m->cost(individual->path[ind], individual->path[1]);
				individual->cost += m->cost(individual->path[m->vertices - 1], individual->path[ind]);
			}

			int* path = new int[m->vertices + 1];
			Individual::swap(individual->path, 0, ind);
			path[0] = path[m->vertices] = 0;
			for (int i = 1; i < m->vertices; i++) {
				if (ind == m->vertices - 1)
					ind = 0;
				else
					ind++;
				path[i] = individual->path[ind];
			}

			delete individual->path;
			individual->path = path;
		}
	}
}

swapMutator::swapMutator(Matrix * m, double mutationProbability)
	: Mutator(m,mutationProbability)
{
}

void insertMutator::mutate(Individual * individual, double probability)
{
}

insertMutator::insertMutator(Matrix * m, double mutationProbability)
	: Mutator::Mutator(m,mutationProbability)
{

}
