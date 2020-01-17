#pragma once
#include "Individual.h"

class Mutator
{
protected:
	double mutationProbability;
	Matrix* m;

public:
	virtual void mutate(Individual* individual, double probability = -1) = 0;
	Mutator(Matrix* m, double mutationProbability);
	virtual ~Mutator();
};


class swapMutator
	: public Mutator
{
public:
	void mutate(Individual* individual, double probability = -1) override;
	swapMutator(Matrix* m, double mutationProbability);
};


class insertMutator
	: public Mutator
{
public:
	void mutate(Individual* individual, double probability = -1) override;
	insertMutator(Matrix* m, double mutationProbability);
};
