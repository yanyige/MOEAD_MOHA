#pragma once
#include "Individual.h"
#include "WeightVector.h"

class SubProblem {
public:
	SubProblem();
	~SubProblem();

public:
	Individual    CurrentSolution;
	WeightVector  WeightVector;
	vector<int>    IndexOfNeighbor;

private:

};
