// TSP_population_based_algorithms.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <conio.h>
#include "GeneticAlgorithm.h"
using namespace std;


void menu();


int main()
{
	//dodac destruktory
	srand(time(NULL));
	menu();
	Matrix* matrix = new Matrix;
	matrix->readFromFile("data17.txt");

	delete matrix;
}



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
			//Timing timer;
			//timer.startCount();
			ga->algorithm();
			//timer.endCount();
			ga->showResult();
			//cout << endl << "Czas: " << timer.getResult() / 1000 << " ms";
			_getch();
			delete ga;
			break;
		}
	} while (h != 27);
	system("cls");
	delete matrix;
}

