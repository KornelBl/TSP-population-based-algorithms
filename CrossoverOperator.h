#pragma once
#include "Individual.h"
class CrossoverOperator
{
protected:
	Individual* child1;
	Individual* child2;
	Matrix* m;

public:

	static const int ONE_POINT_LINEAR_ORDER = 0;
	static const int LINEAR_ORDER = 1;
	static const int CYCLE = 2;
	static const int EDGE = 3;


	static int crossoverMenu();
	static CrossoverOperator* newCrossoverOperatorPtr(int crossType, Matrix* matrix);
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


class LinearOrderCrossover
	: public CrossoverOperator
{
public:
	void cross(Individual* parent1, Individual* parent2) override;
	LinearOrderCrossover(Matrix* matrix);
	~LinearOrderCrossover() override;
};



class CycleCross
	: public CrossoverOperator
{
	

public:
	void cross(Individual* parent1, Individual* parent2) override;
	CycleCross(Matrix* matrix);
	~CycleCross() override;
};


class EdgeCrossover
	: public CrossoverOperator
{

public:
	void cross(Individual* parent1, Individual* parent2) override;
	EdgeCrossover(Matrix* matrix);
	~EdgeCrossover() override;
};