// TSP_population_based_algorithms.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include "GeneticAlgorithm.h"

int main()
{
	//dodac destruktory
	Matrix* matrix = new Matrix;
	matrix->readFromFile("data17.txt");
	GeneticAlgorithm ga(matrix);
	ga.algorithm();
	ga.showResult();
	delete matrix;
}

