#include "pch.h"
#include "CrossoverOperator.h"
#include <conio.h>
#include <algorithm>
#include <list>


int CrossoverOperator::crossoverMenu()
{
	char h;
	do {
		system("cls");
		std::cout << "Wybierz metodê krzy¿owania: ";
		std::cout << "\n1.One point linear" <<
			"\n2.Two point linear" <<
			"\n3.Cycle" <<
			"\n4.Edge" <<
			"\n5.polepszony niby edge" <<
			"\n[Esc] Koniec\n";
		fflush(stdin);
		h = _getch();
		switch (h) {
		case '1':
			return ONE_POINT_LINEAR_ORDER;
			break;
		case '2':
			return LINEAR_ORDER;
			break;
		case '3':
			return CYCLE;
			break;
		case '4':
			return EDGE;
			break;
		case '5':
			return IMP_EDGE;
			break;
		}
	} while (h != 27);
}

CrossoverOperator* CrossoverOperator::newCrossoverOperatorPtr(int crossType, Matrix* matrix)
{
	switch (crossType)
	{
	case 0:
		return new OnePointOrderCross(matrix);
		break;
	case 1:
		return new LinearOrderCrossover(matrix);
		break;
	case 2:
		return new CycleCross(matrix);
		break;
	case 3:
		return new EdgeCrossover(matrix);
		break;
	case 4:
		return new ImprovedEdgeCrossover(matrix);
		break;
	default:
		return new LinearOrderCrossover(matrix);
		break;
	}
}

Individual* CrossoverOperator::getChild1()
{
	return child1;
}

Individual* CrossoverOperator::getChild2()
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



void LinearOrderCrossover::cross(Individual * parent1, Individual * parent2)
{
	//parent1->print();
	//parent2->print();
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

LinearOrderCrossover::LinearOrderCrossover(Matrix * matrix)
	: CrossoverOperator(matrix)
{

}

LinearOrderCrossover::~LinearOrderCrossover()
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

	delete[] filledPos;
	delete[] position1;
	delete[] position2;
}

CycleCross::CycleCross(Matrix * matrix)
	: CrossoverOperator(matrix)
{
}

CycleCross::~CycleCross()
{
}

void EdgeCrossover::cross(Individual * parent1, Individual * parent2)
{
	int* left = new int[m->vertices];
	int* commonLeft = new int[m->vertices];
	int* visited = new int[m->vertices];
	int* helper = new int[m->vertices];
	std::list<int>* commonEdges = new std::list<int>[m->vertices];
	std::list<int>* edges = new std::list<int>[m->vertices];

	edges[0].push_front(parent1->path[1]);
	edges[0].push_front(parent1->path[m->vertices - 1]);
	//dodawanie do listy krawedzi pierwszego rodzica
	for (int i = 1; i < m->vertices; i++) {
		edges[parent1->path[i]].push_front(parent1->path[i + 1]);
		edges[parent1->path[i]].push_front(parent1->path[i - 1]);
	}
	//dodawanie drugiego rodzica
	bool prevSame = false;
	bool nextSame = false;
	for (auto it = edges[0].cbegin(); it != edges[0].cend();) {
		if (*it == parent2->path[m->vertices - 1]) {
			it = edges[0].erase(it);
			commonEdges[0].push_front(parent2->path[m->vertices - 1]);
			prevSame = true;
			continue;
		}
		if (*it == parent2->path[1]) {
			it = edges[0].erase(it);
			commonEdges[0].push_front(parent2->path[1]);
			nextSame = true;
			continue;
		}
		++it;
	}
	if (!nextSame)
		edges[0].push_front(parent2->path[1]);
	else
		nextSame = false;
	if (!prevSame) 
		edges[0].push_front(parent2->path[m->vertices - 1]);
	else
		prevSame = false;

	for (int i = 1; i < m->vertices; i++) {
		for (auto it = edges[parent2->path[i]].cbegin(); it != edges[parent2->path[i]].cend();) {
			if (*it == parent2->path[i - 1]) {
				it = edges[parent2->path[i]].erase(it);
				commonEdges[parent2->path[i]].push_front(parent2->path[i - 1]);
				prevSame = true;
				continue;
			}
			if (*it == parent2->path[i + 1]) {
				it = edges[parent2->path[i]].erase(it);
				commonEdges[parent2->path[i]].push_front(parent2->path[i + 1]);
				nextSame = true;
				continue;
			}
			++it;
		}
		if (!nextSame) 
			edges[parent2->path[i]].push_front(parent2->path[i + 1]);
		else
			nextSame = false;
		if (!prevSame)			
			edges[parent2->path[i]].push_front(parent2->path[i - 1]);
		else
			prevSame = false;
	}


	//przygotowanie do first child
	for (int i = 0; i < m->vertices; i++) {
		left[i] = edges[i].size();
		commonLeft[i] = commonEdges[i].size();
		visited[i] = 0;
		helper[i] = i;
	}

	//first child
	int* path = new int[m->vertices + 1];
	int zeroAt;


	int first = rand() % m->vertices;
	path[0] = path[m->vertices] = first;
	visited[first] = 1;
	//
	Individual::swap(helper, first, m->vertices - 1);
	for (int val : edges[first]) {
		left[val]--;
	}
	for (int val : commonEdges[first]) {
		commonLeft[val]--;
	}
	left[first]--;
	commonLeft[first]--;
	if (first == 0)zeroAt = 0;
	for (int i = 1; i < m->vertices; i++) {
		int next;
		int nextEdgeNumber = INT_MAX;
		int modulo;
		int index;
		if (commonLeft[path[i - 1]] > 0) {
			//porownujemy wierzhcolki z commonedges
			for (int val : commonEdges[path[i - 1]]) {
				if (visited[val] == 0) {
					int edgeNumber = left[val] + commonLeft[val];
					if (edgeNumber < nextEdgeNumber) {
						next = val;
						nextEdgeNumber = edgeNumber;
						modulo = 1;
					}
					else if (edgeNumber == nextEdgeNumber) {
						modulo++;
						if (rand() % modulo == 1) {
							next = val;
							nextEdgeNumber = edgeNumber;
						}
					}
				}
			}
			index = next;
		}else if (left[path[i - 1]] > 0) {
			//porownujemy wierzcholki z edges
			for (int val : edges[path[i - 1]]) {
				if (visited[val] == 0) {
					int edgeNumber = left[val] + commonLeft[val];
					if (edgeNumber < nextEdgeNumber) {
						next = val;
						nextEdgeNumber = edgeNumber;
						modulo = 1;
					}else if (edgeNumber == nextEdgeNumber) {
						modulo++;
						if (rand() % modulo == 1) {
							next = val;
							nextEdgeNumber = edgeNumber;
						}
					}
				}
			}
			index = next;
		}
		else {
			// losujemy jeden z nieodwiedzonych wierzcholkow
			index = rand() % (m->vertices - i);
			next = helper[index];
		}

		if (next == 0)
			zeroAt = i;
		path[i] = next;
		left[next]--;
		commonLeft[next]--;
		for (int val : edges[next]) {
			left[val]--;
		}
		for (int val : commonEdges[next]) {
			commonLeft[val]--;
		}
		visited[next] = 1;

		//swap w helperze
		while (helper[index] != next) {
			index = helper[index];
		}
		Individual::swap(helper, index, m->vertices - i - 1);
	}
	int* realPath = new int[m->vertices + 1];
	realPath[0] = realPath[m->vertices] = 0;

	for (int i = 1; i < m->vertices; i++) {
		if (zeroAt == m->vertices - 1)
			zeroAt = 0;
		else
			zeroAt++;
		realPath[i] = path[zeroAt];
	}




	child1 = new Individual(realPath, m->distanceFunction(path), m->vertices);


	//przygotowanie do drugiego dziecka
	for (int i = 0; i < m->vertices; i++) {
		left[i] = edges[i].size();
		commonLeft[i] = commonEdges[i].size();
		visited[i] = 0;
		helper[i] = i;
	}

	//second child

	first = rand() % m->vertices;

	path[0] = path[m->vertices] = first;
	visited[first] = 1;
	Individual::swap(helper, first, m->vertices - 1);
	for (int val : edges[first]) {
		left[val]--;
	}
	for (int val : commonEdges[first]) {
		commonLeft[val]--;
	}
	left[first]--;
	commonLeft[first]--;
	if (first == 0)
		zeroAt = 0;
	for (int i = 1; i < m->vertices; i++) {
		int next;
		int nextEdgeNumber = INT_MAX;
		int modulo;
		int index;
		if (commonLeft[path[i - 1]] > 0) {
			//porownujemy wierzhcolki z commonedges
			for (int val : commonEdges[path[i - 1]]) {
				if (visited[val] == 0) {
					int edgeNumber = left[val] + commonLeft[val];
					if (edgeNumber < nextEdgeNumber) {
						next = val;
						nextEdgeNumber = edgeNumber;
						modulo = 1;
					}
					else if (edgeNumber == nextEdgeNumber) {
						modulo++;
						if (rand() % modulo == 1) {
							next = val;
							nextEdgeNumber = edgeNumber;
						}
					}
				}
			}
			index = next;
		}
		else if (left[path[i - 1]] > 0) {
			//porownujemy wierzcholki z edges
			for (int val : edges[path[i - 1]]) {
				if (visited[val] == 0) {
					int edgeNumber = left[val] + commonLeft[val];
					if (edgeNumber < nextEdgeNumber) {
						next = val;
						nextEdgeNumber = edgeNumber;
						modulo = 1;
					}
					else if (edgeNumber == nextEdgeNumber) {
						modulo++;
						if (rand() % modulo == 1) {
							next = val;
							nextEdgeNumber = edgeNumber;
						}
					}
				}
			}
			index = next;
		}
		else {
			// losujemy jeden z nieodwiedzonych wierzcholkow
			index = rand() % (m->vertices - i);
			next = helper[index];
		}



		left[next]--;
		commonLeft[next]--;
		if (next == 0)zeroAt = i;
		path[i] = next;
		for (int val : edges[next]) {
			left[val]--;
		}
		for (int val : commonEdges[next]) {
			commonLeft[val]--;
		}
		visited[next] = 1;

		//swap w helperze
		while (helper[index] != next) {
			index = helper[index];
		}
		Individual::swap(helper, index, m->vertices - i - 1);
	}
	realPath = new int[m->vertices + 1];
	realPath[0] = realPath[m->vertices] = 0;

	for (int i = 1; i < m->vertices; i++) {
		if (zeroAt == m->vertices - 1)
			zeroAt = 0;
		else
			zeroAt++;
		realPath[i] = path[zeroAt];
	}




	child2 = new Individual(realPath, m->distanceFunction(path), m->vertices);


	/*std::cout << "KRZYZOWANIE" << std::endl;
	parent1->print();
	parent2->print();
	child1->print();
	child2->print();*/

	/*for (int i = 0; i < m->vertices; i++) {
		commonEdges[i].clear();
		commonEdges[i].~list();
		edges[i].clear();
		edges[i].~list();
	}*/
	
	delete[] path;
	delete[] left;
	delete[] commonLeft;
	delete[] visited;
	delete[] helper;
	delete[] commonEdges;
	delete[] edges;
}

EdgeCrossover::EdgeCrossover(Matrix * matrix)
	: CrossoverOperator(matrix)
{

}

EdgeCrossover::~EdgeCrossover()
{
}


void ImprovedEdgeCrossover::cross(Individual * parent1, Individual * parent2)
{
	std::list<int>* commonEdges = new std::list<int>[m->vertices];
	std::list<int>* edges = new std::list<int>[m->vertices];
	int* helper = new int[m->vertices];


	edges[0].push_front(parent1->path[1]);
	edges[0].push_front(parent1->path[m->vertices - 1]);
	//dodawanie do listy krawedzi pierwszego rodzica
	for (int i = 1; i < m->vertices; i++) {
		edges[parent1->path[i]].push_front(parent1->path[i + 1]);
		edges[parent1->path[i]].push_front(parent1->path[i - 1]);
	}
	//dodawanie drugiego rodzica
	bool prevSame = false;
	bool nextSame = false;
	for (auto it = edges[0].cbegin(); it != edges[0].cend();) {
		if (*it == parent2->path[m->vertices - 1]) {
			it = edges[0].erase(it);
			commonEdges[0].push_front(parent2->path[m->vertices - 1]);
			prevSame = true;
			continue;
		}
		if (*it == parent2->path[1]) {
			it = edges[0].erase(it);
			commonEdges[0].push_front(parent2->path[1]);
			nextSame = true;
			continue;
		}
		++it;
	}
	if (!nextSame)
		edges[0].push_front(parent2->path[1]);
	else
		nextSame = false;
	if (!prevSame)
		edges[0].push_front(parent2->path[m->vertices - 1]);
	else
		prevSame = false;

	for (int i = 1; i < m->vertices; i++) {
		for (auto it = edges[parent2->path[i]].cbegin(); it != edges[parent2->path[i]].cend();) {
			if (*it == parent2->path[i - 1]) {
				it = edges[parent2->path[i]].erase(it);
				commonEdges[parent2->path[i]].push_front(parent2->path[i - 1]);
				prevSame = true;
				continue;
			}
			if (*it == parent2->path[i + 1]) {
				it = edges[parent2->path[i]].erase(it);
				commonEdges[parent2->path[i]].push_front(parent2->path[i + 1]);
				nextSame = true;
				continue;
			}
			++it;
		}
		if (!nextSame)
			edges[parent2->path[i]].push_front(parent2->path[i + 1]);
		else
			nextSame = false;
		if (!prevSame)
			edges[parent2->path[i]].push_front(parent2->path[i - 1]);
		else
			prevSame = false;
	}
	
	std::list<int>* commonEdges2 = new std::list<int>[m->vertices];
	std::list<int>* edges2 = new std::list<int>[m->vertices];

	for (int i = 0; i < m->vertices; i++) {
		commonEdges2[i].assign(commonEdges[i].begin(), commonEdges[i].end());
		edges2[i].assign(edges[i].begin(), edges[i].end());
	}

	//przygotowanie do first child
	for (int i = 0; i < m->vertices; i++) {
		helper[i] = i;
	}


	//child1
	int* path = new int[m->vertices + 1];
	int zeroAt;


	int first = rand() % m->vertices;
	path[0] = path[m->vertices] = first;

	Individual::swap(helper, first, m->vertices - 1);

	//usuniecie z innych list first
	for (int val : commonEdges[first]) {
		for (auto it = commonEdges[val].cbegin(); it != commonEdges[val].cend(); it++) {
			if (*it == first) {
				commonEdges[val].erase(it);
				break;
			}
		}
	}
	for (int val : edges[first]) {
		for (auto it = edges[val].cbegin(); it != edges[val].cend(); it++) {
			if (*it == first) {
				edges[val].erase(it);
				break;
			}
		}
	}



	if (first == 0)zeroAt = 0;
	for (int i = 1; i < m->vertices; i++) {
		int next;
		int nextEdgeNumber = INT_MAX;
		int modulo;
		int index;
		if (!commonEdges[path[i-1]].empty()) {
			//porownujemy wierzhcolki z commonedges
			for (int val : commonEdges[path[i - 1]]) {
				int edgeNumber = commonEdges[val].size() + edges[val].size();
				if (edgeNumber < nextEdgeNumber) {
					next = val;
					nextEdgeNumber = edgeNumber;
					modulo = 1;
				}
				else if (edgeNumber == nextEdgeNumber) {
					modulo++;
					if (rand() % modulo == 1) {
						next = val;
						nextEdgeNumber = edgeNumber;
					}
				}
			}
			index = next;
		}
		else if (!edges[path[i - 1]].empty()) {
			//porownujemy wierzcholki z edges
			for (int val : edges[path[i - 1]]) {
				int edgeNumber = edges[val].size() + commonEdges[val].size();
				if (edgeNumber < nextEdgeNumber) {
					next = val;
					nextEdgeNumber = edgeNumber;
					modulo = 1;
				}
				else if (edgeNumber == nextEdgeNumber) {
					modulo++;
					if (rand() % modulo == 1) {
						next = val;
						nextEdgeNumber = edgeNumber;
					}
				}
			}
			index = next;
		}
		else {
			// losujemy jeden z nieodwiedzonych wierzcholkow
			index = rand() % (m->vertices - i);
			next = helper[index];
		}

		if (next == 0)
			zeroAt = i;
		path[i] = next;
		//usuwanie z kolegów
		for (int val : commonEdges[path[i]]) {
			for (auto it = commonEdges[val].cbegin(); it != commonEdges[val].cend();it++) {
				if (*it == path[i]) {
					commonEdges[val].erase(it);
					break;
				}
			}
		}
		for (int val : edges[path[i]]) {
			for (auto it = edges[val].cbegin(); it != edges[val].cend(); it++) {
				if (*it == path[i]) {
					edges[val].erase(it);
					break;
				}
			}
		}

		//swap w helperze
		while (helper[index] != next) {
			index = helper[index];
		}
		Individual::swap(helper, index, m->vertices - i - 1);
	}
	int* realPath = new int[m->vertices + 1];
	realPath[0] = realPath[m->vertices] = 0;

	for (int i = 1; i < m->vertices; i++) {
		if (zeroAt == m->vertices - 1)
			zeroAt = 0;
		else
			zeroAt++;
		realPath[i] = path[zeroAt];
	}


	child1 = new Individual(realPath, m->distanceFunction(realPath), m->vertices);


	//przygotowanie do first child
	for (int i = 0; i < m->vertices; i++) {
		helper[i] = i;
	}


	//child2

	first = rand() % m->vertices;
	path[0] = path[m->vertices] = first;

	Individual::swap(helper, first, m->vertices - 1);

	//usuniecie z innych list first
	for (int val : commonEdges2[first]) {
		for (auto it = commonEdges2[val].cbegin(); it != commonEdges2[val].cend(); it++) {
			if (*it == first) {
				commonEdges2[val].erase(it);
				break;
			}
		}
	}
	for (int val : edges2[first]) {
		for (auto it = edges2[val].cbegin(); it != edges2[val].cend(); it++) {
			if (*it == first) {
				edges2[val].erase(it);
				break;
			}
		}
	}

	if (first == 0)zeroAt = 0;
	for (int i = 1; i < m->vertices; i++) {
		int next;
		int nextEdgeNumber = INT_MAX;
		int modulo;
		int index;
		if (!commonEdges2[path[i - 1]].empty()) {
			//porownujemy wierzhcolki z commonedges2
			for (int val : commonEdges2[path[i - 1]]) {
				int edgeNumber = commonEdges2[val].size() + edges2[val].size();
				if (edgeNumber < nextEdgeNumber) {
					next = val;
					nextEdgeNumber = edgeNumber;
					modulo = 1;
				}
				else if (edgeNumber == nextEdgeNumber) {
					modulo++;
					if (rand() % modulo == 1) {
						next = val;
						nextEdgeNumber = edgeNumber;
					}
				}
			}
			index = next;
		}
		else if (!edges2[path[i - 1]].empty()) {
			//porownujemy wierzcholki z edges2
			for (int val : edges2[path[i - 1]]) {
				int edgeNumber = edges2[val].size() + commonEdges2[val].size();
				if (edgeNumber < nextEdgeNumber) {
					next = val;
					nextEdgeNumber = edgeNumber;
					modulo = 1;
				}
				else if (edgeNumber == nextEdgeNumber) {
					modulo++;
					if (rand() % modulo == 1) {
						next = val;
						nextEdgeNumber = edgeNumber;
					}
				}
			}
			index = next;
		}
		else {
			// losujemy jeden z nieodwiedzonych wierzcholkow
			index = rand() % (m->vertices - i);
			next = helper[index];
		}

		if (next == 0)
			zeroAt = i;
		path[i] = next;
		//usuwanie z kolegów
		for (int val : commonEdges2[path[i]]) {
			for (auto it = commonEdges2[val].cbegin(); it != commonEdges2[val].cend(); it++) {
				if (*it == path[i]) {
					commonEdges2[val].erase(it);
					break;
				}
			}
		}
		for (int val : edges2[path[i]]) {
			for (auto it = edges2[val].cbegin(); it != edges2[val].cend(); it++) {
				if (*it == path[i]) {
					edges2[val].erase(it);
					break;
				}
			}
		}

		//swap w helperze
		while (helper[index] != next) {
			index = helper[index];
		}
		Individual::swap(helper, index, m->vertices - i - 1);
	}
	int* realPath2 = new int[m->vertices + 1];
	realPath2[0] = realPath2[m->vertices] = 0;

	for (int i = 1; i < m->vertices; i++) {
		if (zeroAt == m->vertices - 1)
			zeroAt = 0;
		else
			zeroAt++;
		realPath2[i] = path[zeroAt];
	}


	child2 = new Individual(realPath2, m->distanceFunction(realPath2), m->vertices);

	delete[] helper;
	delete[] edges;
	delete[] edges2;
	delete[] commonEdges;
	delete[] commonEdges2;
	delete[] path;
}

ImprovedEdgeCrossover::ImprovedEdgeCrossover(Matrix * matrix)
	: CrossoverOperator(matrix)
{

}

ImprovedEdgeCrossover::~ImprovedEdgeCrossover()
{
}