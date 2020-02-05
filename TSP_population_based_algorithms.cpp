// TSP_population_based_algorithms.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <conio.h>
#include "GeneticAlgorithm.h"
#include "Timing.h"
#include <fstream>
using namespace std;


void menu();
//void research();

int main()
{

	srand(time(NULL));
	menu();
}


//void research() {
//	std::string fileName = "DP22.csv";
//	Matrix* matrix = new Matrix;
//	ofstream file;
//	double result, timeResult;
//	Timing counter;
//	string data[8] = { "17","34","45","56","70","100","171","323" };
//
//	int populationSize = 50;
//	int eliteSize = 4;
//	int generations = 1000;
//	double crossProb = 0.80;
//	double mutProb = 0.02;
//	int crosser = 3;
//	int selector = 0;
//	int startPath = 1;
//
//	int popTab[6] = { 0, 2, 4, 6, 8, 10};
//
//	fileName = "eliteSize.csv";
//
//	file.open(fileName, ios_base::out);
//	for (int i = 0; i < 8; i++) {
//		matrix->readFromFile("data" + data[i] + ".txt");
//		file << data[i] << ";";
//		for (int k = 0; k < 6; k++) {
//			result = 0;
//			timeResult = 0;
//
//			eliteSize = popTab[k];
//			for (int j = 0; j < 20; j++) {
//				//ga
//				GeneticAlgorithm ga(matrix,populationSize,eliteSize,generations,crossProb,mutProb,CrossoverOperator::newCrossoverOperatorPtr(crosser,matrix),Selector::newSelectorPtr(selector),startPath);
//				counter.startCount();
//				//mierzony czas
//				ga.algorithm();
//				counter.endCount();
//				result += ga.getBestCost();
//				timeResult += counter.getResult() / 20;
//				std::cout << i << ", " << j << endl;
//			}
//			file << k << ";" << result / 20 << ";" << timeResult << ";";
//		}
//		file << endl;
//	}
//	file.close();
//
//	delete matrix;
//}






void menu() {
	char h;
	Matrix* matrix = new Matrix;
	std::string filename;
	double crossProbability = 0.75;
	double mutationProbability = 0.01;
	int crossType = CrossoverOperator::LINEAR_ORDER;
	int selectorType = Selector::ROULLETE;
	int populationSize = 40;
	int eliteSize = 4;
	int generations = 1000;
	GeneticAlgorithm* ga;


	std::cout << "Podaj nazwe pliku\n";
	std::cin >> filename;
	matrix->readFromFile(filename);
	do {
		system("cls");
		cout << matrix->name << endl;
		//matrix->show();
		cout << "\n1.Zmien graf" <<
			"\n2.Zmien prawdopodobienstwo krzyzowania | " << crossProbability <<
			"\n3.Zmien prawdopodobienstwo mutacji | " << mutationProbability <<
			"\n4.Zmien metodę krzyzowania" << crossType<<
			"\n5.Zmien metodę selekcji" << 
			"\n6.Zmien wielkosc elity | " << eliteSize <<
			"\n7.Zmien wielkosc populacji | " << populationSize <<
			"\n8.Zmien ilosc pokolen | " << generations <<
			"\n9.Czas na kopulacje"<<
			"\n[Esc] Koniec\n";
		fflush(stdin);
		h = _getch();
		switch (h) {
		case '1':
			std::cout << "Podaj nazwe pliku\n";
			std::cin >> filename;
			matrix->readFromFile(filename);
			break;
		case '2':
			cout << "Podaj prawdopodobienstwo krzyzowania:\n";
			cin >> crossProbability;
			break;
		case '3':
			cout << "Podaj prawdopodobienstwo mutacji:\n";
			cin >> mutationProbability;
			break;
		case '4':
			crossType = CrossoverOperator::crossoverMenu();
			break;
		case '5':
			selectorType = Selector::selectorMenu();
			break;
		case '6':
			cout << "Podaj wielkosc elity:\n";
			cin >> eliteSize;
			break;
		case '7':
			cout << "Podaj wielkosc populacji:\n";
			cin >> populationSize;
			break;
		case '8':
			cout << "Podaj ilosc pokolen:\n";
			cin >> generations;
			break;
		case '9':	
			ga = new GeneticAlgorithm(matrix, populationSize, eliteSize, generations, crossProbability,
				mutationProbability, CrossoverOperator::newCrossoverOperatorPtr(crossType, matrix), Selector::newSelectorPtr(selectorType));
			Timing timer;
			timer.startCount();
			ga->algorithm();
			timer.endCount();
			ga->showResult();
			cout << endl << "Czas: " << timer.getResult() / 1000 << " ms";
			_getch();
			delete ga;
			break;
		}
	} while (h != 27);
	system("cls");
	delete matrix;
}

