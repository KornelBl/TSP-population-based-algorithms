#pragma once
#include <string>

class Matrix
{

	int edges = 0;
	static const int max_weight = 100;
	struct connectElem {
		int ind;
		int connected = 0;
	};	
	void swap(connectElem*, int, int);
	void swap(int*, int, int);
	int** AM = NULL;

public:
	std::string name;
	int vertices = 0;
	int cost(int from,int to);
	void generateRandomDirected(int v, int density = 100);
	void deleteAdjMatrix();
	bool readFromFile(std::string fileName);
	int distanceFunction(int v[]);
	void show();
	Matrix();
	~Matrix();
};

