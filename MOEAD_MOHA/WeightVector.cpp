
#include "WeightVector.h"

WeightVector::WeightVector() {
	vector<double> w_vec(vector<double>(NumberOfObj, 0));

	lambda = w_vec;
}

WeightVector::~WeightVector() {

}

double WeightVector::DistanceTo(WeightVector &weight) {
	double dist = 0;
	for (int iObj = 0; iObj<NumberOfObj; iObj++) {
		double diff = this->lambda[iObj] - weight.lambda[iObj];
		dist += diff*diff;
	}
	return sqrt(dist);
}

void WeightVector::Show() {
	for (int iObj = 0; iObj<NumberOfObj; iObj++) {
		printf(" %f ", lambda[iObj]);
	}
	printf("\n");
}