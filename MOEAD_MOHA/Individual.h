#pragma once


#include "global.h"
#include "ScheduleProblem.h"
#include "RandomNumber.h"
//#include "RandomNumber.h"

class Individual {
public:
	Individual();
	~Individual();

public:
	vector< vector<int> > machine;
	double workload; //object 1
	double makespan; //object 2

	bool operator==(const Individual& ind);
	bool operator>(const  Individual& ind);
	bool operator<(const  Individual& ind);

	bool dominated;
	CRandomNumber    Rnd;

public:
	void Randomize();
	void Repair();
	void Evaluate();
	void Show();

	void UniformCrossover(Individual &parent1, Individual &parent2);

	double ComputingFitnessValue(vector<double> &lambda, char *strFuncType);

private:
	/***************Warning******************/
	//**��һ������ó���,��ʱ����
	/***************~Warning******************/
	int taskIndex[MAXN];
	bool taskUsed[MAXN];
	set<int> doneSet;
	int Individual::test(int task);
	int n; // count of dominated solution
};