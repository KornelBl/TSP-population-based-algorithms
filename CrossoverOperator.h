#pragma once
#include "Individual.h"
class CrossoverOperator
{
protected:
	double crossProbability = 0.70;
	Individual* child1;
	Individual* child2;
	Matrix* m;

public:
	virtual void cross(Individual* parent1, Individual* parent2) = 0;
	Individual* getChild1();
	Individual* getChild2();
	CrossoverOperator(Matrix* matrix);
	virtual ~CrossoverOperator();
};

class OnePointOrderCross
	: public CrossoverOperator
{
	int* visited;

public:
	void cross(Individual* parent1, Individual* parent2) override;
	OnePointOrderCross(Matrix* matrix);
	~OnePointOrderCross() override;
};


class TwoPointOrderCross
	: public CrossoverOperator
{
public:
	void cross(Individual* parent1, Individual* parent2) override;
	TwoPointOrderCross(Matrix* matrix);
	~TwoPointOrderCross() override;
};



class CycleCross
	: public CrossoverOperator
{
	

public:
	void cross(Individual* parent1, Individual* parent2) override;
	CycleCross(Matrix* matrix);
	~CycleCross() override;
};