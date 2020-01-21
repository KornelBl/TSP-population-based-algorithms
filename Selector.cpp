#include "pch.h"
#include "Selector.h"
#include <conio.h>


int Selector::selectorMenu()
{
	char h;
	do {
		system("cls");
		std::cout << "Wybierz metodê krzy¿owania: ";
		std::cout << "\n1.Ruletka" <<
			"\n2.Tournament" <<
			"\n3.Ranking" <<
			//"\n4.Edge" <<
			//"\n4.Zmien metodê krzyzowania" <<
			"\n[Esc] Koniec\n";
		fflush(stdin);
		h = _getch();
		switch (h) {
		case '1':
			return ROULLETE;
			break;
		case '2':
			return TOURNAMENT;
			break;
		case '3':
			return RANKING;
			break;
		case '4':
			break;
		}
	} while (h != 27);
}

Selector * Selector::newSelectorPtr(int selectorType)
{

	switch (selectorType)
	{
	case 0:
		return new RouletteSelector();
		break;
	case 1:
		return new TournamentSelector();
		break;
	case 2:
		return new RankingSelector();
		break;
	default:
		return new RouletteSelector();
		break;
	}
}

Selector::Selector()
{
}


Selector::~Selector()
{
}

Individual** RouletteSelector::selectMatingPool(Individual** main, double * fitness, int size)
{
	//roulette
	Individual** matingPool = new Individual*[size];
	double* thresholds = new double[size];
	thresholds[0] = fitness[0];
	for (int i = 1; i < size; i++) {
		thresholds[i] = thresholds[i - 1] + fitness[i];
	}

	for (int i = 0; i < size; i++) {
		double ball = ((double)rand() / (RAND_MAX + 1.0)) * thresholds[size - 1];
		for (int j = 0; j < size; j++) {
			if (ball < thresholds[j]) {
				matingPool[i] = main[j];
				break;
			}
		}
	}
	delete[] thresholds;
	return matingPool;
}

TournamentSelector::TournamentSelector(int tournamentSize)
	: Selector()
{
	this->tournamentSize = tournamentSize;
}

Individual ** TournamentSelector::selectMatingPool(Individual ** main, double * fitness, int size)
{
	//tournament
	Individual** matingPool = new Individual*[size];
	for (int i = 0; i < size; i++) {
		int leading = rand() % size;
		for (int j = 1; j < tournamentSize; j++) {
			int challenger = rand() % size;
			if (fitness[challenger] > fitness[leading]) leading = challenger;
		}
		matingPool[i] = main[leading];
	}
	return matingPool;
}

Individual** RankingSelector::selectMatingPool(Individual ** main, double * fitness, int size)
{
	Individual** matingPool = new Individual*[size];
	double* thresholds = new double[size];
	for (int i = 0; i < size; i++) {
		thresholds[i] = size - i;
	}

	for (int i = 0; i < size; i++) {
		double ball = ((double)rand() / (RAND_MAX + 1.0)) * thresholds[size - 1];
		for (int j = 0; j < size; j++) {
			if (ball < thresholds[j]) {
				matingPool[i] = main[j];
				break;
			}
		}
	}
	delete[] thresholds;


	return matingPool;
}
