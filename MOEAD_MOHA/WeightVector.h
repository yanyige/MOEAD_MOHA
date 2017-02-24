#pragma once
#include "Global.h"

class WeightVector {
public:
	WeightVector();
	~WeightVector();

public:
	vector<double> lambda;

public:
	double DistanceTo(WeightVector &weight);
	void Show();

private:

};

