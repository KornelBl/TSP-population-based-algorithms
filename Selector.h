#pragma once
#include "Individual.h"

class Selector
{
protected:

public:
	Selector();
	virtual Individual** selectMatingPool(Individual** main,float* fitness, int size) = 0;
	virtual ~Selector();
};


class RouletteSelector
	: public Selector
{
public:
	Individual** selectMatingPool(Individual** main, float* fitness,int size) override;
};

