#pragma once

#include "RandomNumber.h"	// Added by ClassView

#include  "global.h"
#include  "Individual.h"
#include  "WeightVector.h"
#include  "SubProblem.h"

class MOEAD {
public:
	MOEAD();
	~MOEAD();

public:
	vector<SubProblem> CurrentPopulation;  //  population of subproblems

	vector<Individual> SecondPopulation;  //  external population containing all nondominated solutions found 

public:
	int MaxNumOfFuncEvals;                  //  the maximal number of function evaluations
	int PopulationSize;                     //  population size
	int NeighborhoodSize;					//  neighborhood size
	int NumberOfFuncEvals;					//  counter for function evaluations

	CRandomNumber Rnd;                      //  uniform random number generator

public:
	void Run(int fevals);
	void InitializeReferencePoint();
	void UpdateReferencePoint(Individual &ind);
	void InitializeWeightVector();
	void InitializeNeighborhood();
	void InitializePopulation();

	void UpdateSecondPopulation(Individual &ind);
	void UpdateNeighboringSolution(Individual &ind, int iPop);
	void SaveSecondPopulation();
	void ShowSecondPopulation();


	void MinFastSort(vector<double> &dist, vector<int> &indx, int n, int m);


private:

};

