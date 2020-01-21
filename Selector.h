#pragma once
#include "Individual.h"

class Selector
{
protected:

public:
	static const int ROULLETE = 0;
	static const int TOURNAMENT = 1;
	static const int RANKING = 2;

	static int selectorMenu();
	static Selector* newSelectorPtr(int selectorType);
	Selector();
	virtual Individual** selectMatingPool(Individual** main,double* fitness, int size) = 0;
	virtual ~Selector();
};


class RouletteSelector
	: public Selector
{
public:
	Individual** selectMatingPool(Individual** main, double* fitness,int size) override;
};


class TournamentSelector
	: public Selector
{
	int tournamentSize = 4;
public:
	TournamentSelector(int tournamentSize = 4);
	Individual** selectMatingPool(Individual** main, double* fitness, int size) override;
};


class RankingSelector
	: public Selector
{
public:
	Individual** selectMatingPool(Individual** main, double* fitness, int size) override;
};

