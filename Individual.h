#pragma once
class Individual
{

	int size;
	//int* whereTo = NULL;
	void generateRandom(Matrix* m);

public:
	int cost;
	int* path = NULL;

	static void swap(int* T, int a, int b);
	int getCost();
	void print();
	Individual(Matrix* m);
	Individual(Individual* pattern);
	Individual(int* path, int cost, int size);
	~Individual();
};

