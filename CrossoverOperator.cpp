#include "pch.h"
#include "CrossoverOperator.h"


Individual * CrossoverOperator::getChild1()
{
	return child1;
}

Individual * CrossoverOperator::getChild2()
{
	return child2;
}

CrossoverOperator::CrossoverOperator(Matrix* matrix)
{
	this->m = matrix;
}


CrossoverOperator::~CrossoverOperator()
{
}

void OnePointOrderCross::cross(Individual * parent1, Individual * parent2)
{
	//one point crossover
	int crossPoint = rand() % (m->vertices - 1) + 1;
	int cost = 0;
	int* path;

	//child 1
	path = new int[m->vertices + 1];
	path[0] = path[m->vertices] = 0;
	for (int j = 1; j < crossPoint; j++) {
		path[j] = parent1->path[j];
		cost += m->cost(path[j - 1], path[j]);
		visited[path[j]] = 1;
	}
	int at = crossPoint;
	for (int j = 1; j < m->vertices; j++) {
		if (visited[parent2->path[j]]) {
			visited[parent2->path[j]] = 0;
			continue;
		}
		path[at] = parent2->path[j];
		cost += m->cost(path[at - 1], path[at]);
		at++;
	}
	cost += m->cost(path[m->vertices - 1], 0);
	child1 = new Individual(path, cost, m->vertices);


	//child2
	path = new int[m->vertices + 1];
	cost = 0;
	path[0] = path[m->vertices] = 0;
	for (int j = 1; j < crossPoint; j++) {
		path[j] = parent2->path[j];
		cost += m->cost(path[j - 1], path[j]);
		visited[path[j]] = 1;
	}
	at = crossPoint;
	for (int j = 1; j < m->vertices; j++) {
		if (visited[parent1->path[j]]) {
			visited[parent1->path[j]] = 0;
			continue;
		}
		path[at] = parent1->path[j];
		cost += m->cost(path[at - 1], path[at]);
		at++;
	}
	cost += m->cost(path[m->vertices - 1], 0);
	child2 = new Individual(path, cost, m->vertices);
}

OnePointOrderCross::OnePointOrderCross(Matrix * matrix)
	: CrossoverOperator(matrix)
{
	visited = new int[m->vertices];
	for (int i = 0; i < m->vertices; i++)
		visited[i] = 0;
}

OnePointOrderCross::~OnePointOrderCross()
{
	delete[] visited;
}

void TwoPointOrderCross::cross(Individual * parent1, Individual * parent2)
{
	int* visited = new int[m->vertices];
	for (int i = 0; i < m->vertices; i++)
		visited[i] = 0;
	//two point crossover
	int crossPoint1 = rand() % (m->vertices - 1) + 1;
	int crossPoint2;
	do {
		crossPoint2 = rand() % (m->vertices - 1) + 1;
	} while (crossPoint1 == crossPoint2);
	
	if (crossPoint1 > crossPoint2) {
		int bufor = crossPoint1;
		crossPoint1 = crossPoint2;
		crossPoint2 = bufor;
	}

	//child 1
	int cost = 0;
	int* path = new int[m->vertices + 1];
	path[0] = path[m->vertices] = 0;
	
	for (int i = crossPoint1; i <= crossPoint2; i++) {
		path[i] = parent1->path[i];
		visited[path[i]] = 1;
	}
	
	int at = 1;
	for (int i = 1; i < crossPoint1; i++) {
		while (visited[parent2->path[at]]) {
			at++;
		}
		path[i] = parent2->path[at];
		at++;
	}

	for (int i = crossPoint2 + 1; i < m->vertices; i++) {
		while (visited[parent2->path[at]]) {
			at++;
		}
		path[i] = parent2->path[at];
		at++;
	}

	cost = m->distanceFunction(path);
	child1 = new Individual(path, cost, m->vertices);

	//child2
	for (int i = 0; i < m->vertices; i++)
		visited[i] = 0;
	path = new int[m->vertices + 1];
	path[0] = path[m->vertices] = 0;

	for (int i = crossPoint1; i <= crossPoint2; i++) {
		path[i] = parent2->path[i];
		visited[path[i]] = 1;
	}

	at = 1;
	for (int i = 1; i < crossPoint1; i++) {
		while (visited[parent1->path[at]]) {
			at++;
		}
		path[i] = parent1->path[at];
		at++;
	}

	for (int i = crossPoint2 + 1; i < m->vertices; i++) {
		while (visited[parent1->path[at]]) {
			at++;
		}
		path[i] = parent1->path[at];
		at++;
	}

	cost = m->distanceFunction(path);
	child2 = new Individual(path, cost, m->vertices);


	/*std::cout << crossPoint1 << "   " << crossPoint2 << std::endl;
	parent1->print();
	parent2->print();
	child1->print();
	child2->print();*/

	delete[] visited;
}

TwoPointOrderCross::TwoPointOrderCross(Matrix * matrix)
	: CrossoverOperator(matrix)
{

}

TwoPointOrderCross::~TwoPointOrderCross()
{
}

void CycleCross::cross(Individual * parent1, Individual * parent2)
{
	int* filledPos = new int[m->vertices];
	int* position1 = new int[m->vertices];
	int* position2 = new int[m->vertices]; 
	int* path1 = new int[m->vertices + 1];
	int* path2 = new int[m->vertices + 1];
	path1[0] = path1[m->vertices] = path2[0] = path2[m->vertices] = 0;

	for (int i = 1; i < m->vertices; i++) {
		position1[parent1->path[i]] = i;
		position2[parent2->path[i]] = i;
		filledPos[i] = 0;
	}




	int first = path1[1] = parent1->path[1];
	int next = path2[1] = parent2->path[1];


	do {
		path1[position1[next]] = next;
	

		filledPos[position1[next]] = 1;
		next = parent2->path[position1[next]];
		path2[position2[next]] = next;
	} while (next != first);

	for (int i = 2; i < m->vertices; i++) {
		if (filledPos[i] == 0) {
			path1[i] = parent2->path[i];
			path2[i] = parent1->path[i];
		}
	}

	child1 = new Individual(path1, m->distanceFunction(path1), m->vertices);
	child2 = new Individual(path2, m->distanceFunction(path2), m->vertices);
	
	

	/*parent1->print();
	parent2->print();
	child1->print();
	child2->print();*/

	delete[] filledPos, position1, position2;
}

CycleCross::CycleCross(Matrix * matrix)
	: CrossoverOperator(matrix)
{
}

CycleCross::~CycleCross()
{
}
