#include "pch.h"
#include "Matrix.h"
#include <fstream>


Matrix::Matrix()
{
}


Matrix::~Matrix()
{
	deleteAdjMatrix();
}

void Matrix::swap(connectElem* T, int a, int b) {
	if (b < 0 || a < 0)return;
	int buf = T[a].ind;
	int buf2 = T[a].connected;
	T[a].ind = T[b].ind;
	T[a].connected = T[b].connected;
	T[b].ind = buf;
	T[b].connected = buf2;
	return;
}

void Matrix::swap(int* T, int a, int b) {
	int buf = T[a];
	T[a] = T[b];
	T[b] = buf;
	return;
}

int Matrix::cost(int from, int to)
{
	return AM[from][to];
}

void Matrix::generateRandomDirected(int v, int density)
{
	deleteAdjMatrix();
	vertices = v;
	long long int maxEdges = vertices * (vertices - 1) * density / 100;
	//edges = v - 1;
	edges = 0;
	AM = new int*[vertices];
	for (int i = 0; i < vertices; i++) {
		AM[i] = new int[vertices];
		for (int j = 0; j < vertices; j++) AM[i][j] = max_weight;
	}
	//generowanie drzewa rozpinajacego
	connectElem* connection = new connectElem[vertices];
	for (int i = 0; i < vertices; i++) {
		connection[i].ind = i;
	}
	/*int connected = 1;
	swap(connection, vertices - 1, rand() % vertices);
	while (connected < vertices) {
		int temp = rand() % (vertices - connected);
		int vertex = vertices - rand() % connected - 1;
		connected++;
		int val = rand() % max_weight;
		AM[connection[temp].ind][connection[vertex].ind] = val;
		AM[connection[vertex].ind][connection[temp].ind] = val;
		connection[vertex].connected++;
		connection[temp].connected++;
		swap(connection, temp, vertices - connected);
	}*/
	//dodanie dodatkowych krawedzi
	int possibleV = vertices;
	for (int i = vertices - 1; i >= 0; i--) {
		if (connection[i].connected == vertices - 1) swap(connection, i, --possibleV);
	}
	while (edges < maxEdges && possibleV > 0) {
		int val = rand() % max_weight;
		int ind = rand() % possibleV;
		int ind2 = 0;
		edges++;
		if (connection[ind].connected != vertices - 1)
			ind2 = rand() % (vertices - connection[ind].connected - 1);
		for (int i = 0; i < vertices; i++) {
			if (i != ind && AM[connection[ind].ind][connection[i].ind] == max_weight) {
				if (ind2--)continue;
				connection[ind].connected++;
				AM[connection[ind].ind][connection[i].ind] = val;
				if (connection[ind].connected == vertices - 1) swap(connection, ind, --possibleV);
				break;
			}
		}
	}
	delete[] connection;
	return;
}

void Matrix::deleteAdjMatrix()
{
	if (AM == NULL)return;
	for (int i = 0; i < vertices; i++) {
		delete[] AM[i];
	}
	delete[] AM;
	vertices = 0;
	AM = NULL;
}

bool Matrix::readFromFile(std::string fileName)
{
	deleteAdjMatrix();
	std::ifstream lfile;
	lfile.open(fileName);
	lfile >> name >> vertices;
	AM = new int*[vertices];
	for (int i = 0; i < vertices; i++) {
		AM[i] = new int[vertices];
		for (int j = 0; j < vertices; j++)
			lfile >> AM[i][j];
	}

	lfile.close();
	return true;
}

int Matrix::distanceFunction(int v[]) { 
	int result = 0;
	for (int i = 0; i < vertices; i++) {
		result += cost(v[i],v[i + 1]);
	}
	return result;
}

void Matrix::show()
{
	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			
			std::cout << AM[i][j] << ", ";
		}
		std::cout << std::endl;
	}
}
