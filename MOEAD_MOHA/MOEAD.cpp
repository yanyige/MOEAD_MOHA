#include "MOEAD.h"


MOEAD::MOEAD() {
	ReferencePoint = vector<double>(NumberOfObj, 0);
	NeighborhoodSize = 10;

	NumberOfFuncEvals = 0;

	seed = (seed + 3111) % 77559; //(unsigned)time(NULL);
	rnd_uni_init = -(long)seed;
	
}

MOEAD::~MOEAD() {
}

void MOEAD::MinFastSort(vector<double> &dist, vector<int> &indx, int n, int m) {
	for (int i = 0; i < m; i++) {
		for (int j = i + 1; j < n; j++) {
			if (dist[i] > dist[j]) {
				double temp = dist[i];
				dist[i] = dist[j];
				dist[j] = temp;
				int id = indx[i];
				indx[i] = indx[j];
				indx[j] = id;
			}
		}
	}
}

void MOEAD::InitializeReferencePoint() {
	Individual ind;
	ind.Randomize();
	ind.Repair();
	ind.Evaluate();
	//ind.Show();
	this->UpdateReferencePoint(ind);
}

void MOEAD::UpdateReferencePoint(Individual &ind) {

	/*if (ind.profit[iObj] > ReferencePoint[iObj]) {
		ReferencePoint[iObj] = ind.profit[iObj];
	}*/
	if (ind.makespan < ReferencePoint[0]) {
		ReferencePoint[0] = ind.makespan;
	}
	if (ind.workload < ReferencePoint[1]) {
		ReferencePoint[1] = ind.workload;
	}
}

void MOEAD::InitializeWeightVector() {
	char filename[1024];
	//sprintf(filename, "weights/wks%d%d.dat", NumberOfItems, NumberOfKnapsacks);
	sprintf_s(filename, "weights/wks5002.dat");

	ifstream indata;
	indata.open(filename); // opens the file
	if (!indata) { // file couldn't be opened
		cerr << "Error: file could not be opened" << endl;
		exit(1);
	}

	indata >> PopulationSize;

	SubProblem  subp;
	for (int i = 1; i <= PopulationSize; i++) {
		for (int ii = 0; ii < NumberOfObj; ii++) {
			indata >> subp.WeightVector.lambda[ii];
		}
		subp.WeightVector.Show();
		CurrentPopulation.push_back(subp);
	}

	indata.close();

	cout << "权重向量初始化完毕" << endl;
}

void MOEAD::InitializeNeighborhood() {
	for (int iPop = 0; iPop < PopulationSize; iPop++) {
		vector<int>     indx; //对应向量的下标
		vector<double>  dist; //相邻向量的距离
		for (int iPop2 = 0; iPop2 < PopulationSize; iPop2++) {
			indx.push_back(iPop2);
			double tp = CurrentPopulation[iPop].WeightVector.DistanceTo(CurrentPopulation[iPop2].WeightVector);
			dist.push_back(tp);
		}
		this->MinFastSort(dist, indx, PopulationSize, NeighborhoodSize + 1);

		for (int i = 0; i < NeighborhoodSize + 1; i++) {
			CurrentPopulation[iPop].IndexOfNeighbor.push_back(indx[i]);
		}
		indx.clear();
		dist.clear();
	}
}

void MOEAD::InitializePopulation() {
	for (int iPop = 0; iPop < CurrentPopulation.size(); iPop++) {
		CurrentPopulation[iPop].CurrentSolution.Randomize();
		CurrentPopulation[iPop].CurrentSolution.Repair();

		UpdateReferencePoint(CurrentPopulation[iPop].CurrentSolution);
		NumberOfFuncEvals++;
	}
}

void MOEAD::UpdateSecondPopulation(Individual &ind) {
	//*

	ind.Evaluate();
	int iCount = 0;
	for (int n = 0; n<SecondPopulation.size(); n++) {

		if (ind == SecondPopulation[n])
			return;

		if (SecondPopulation[n]<ind)
			return;

		if (ind<SecondPopulation[n]) {
			SecondPopulation[n].dominated = true;
			iCount++;
		}
		else {
			SecondPopulation[n].dominated = false;
		}
	}

	for (int n = 0; n<SecondPopulation.size(); n++) {
		if (SecondPopulation[n].dominated) {
			SecondPopulation.erase(SecondPopulation.begin() + n);
			n--;
		}
	}

	SecondPopulation.push_back(ind);
}

// compare the offspring solution with its neighhoring solutions
void MOEAD::UpdateNeighboringSolution(Individual &offspring, int iPop) {
	for (int n = 0; n<NeighborhoodSize; n++) {
		double f11, f12, f21, f22;
		double id = CurrentPopulation[iPop].IndexOfNeighbor[n];    // the index of neighboring subproblem
		offspring.Evaluate();  // fitness of the offspring
		CurrentPopulation[id].CurrentSolution.Evaluate();  // fitness of neighbors
		f11 = offspring.makespan;
		f12 = offspring.workload;
		f21 = CurrentPopulation[id].CurrentSolution.makespan;
		f22 = CurrentPopulation[id].CurrentSolution.workload;

		cout << "f11:" << f11 << " f21:" << f21 << endl;
		cout << "f12:" << f12 << " f22:" << f22 << endl;
																																	  // if offspring is better, then update the neighbor
		if (f11<=f21 && f12<=f22) {
			CurrentPopulation[id].CurrentSolution = offspring;
		}
	}
}

void MOEAD::SaveSecondPopulation() {
	char saveFilename[1024];
	sprintf_s(saveFilename, "POF/POF_MOEAD_KS%d%d_R%d.dat", NumberOfTasks, NumberOfObj, run_id);
	std::fstream fout;
	fout.open(saveFilename, std::ios::out);
	for (int n = 0; n<SecondPopulation.size(); n++) {
		for (int k = 0; k<NumberOfObj; k++) {
			fout << SecondPopulation[n].workload << " ";
		}
		fout << "\n";
	}
	fout.close();
}

void MOEAD::ShowSecondPopulation() {
	for (int n = 0; n<SecondPopulation.size(); n++) {
		cout << "makespan:" << SecondPopulation[n].makespan << " ";
		cout << "workload:" << SecondPopulation[n].workload << " ";
		cout << "\n";
	}
}

void MOEAD::Run(int fevals) {

	MaxNumOfFuncEvals = fevals;

	this->InitializeReferencePoint();

	this->InitializeWeightVector();

	this->InitializeNeighborhood();

	this->InitializePopulation();

	int gen = 1;

	cout << "main" << NumberOfFuncEvals << " "<< endl;
	while (NumberOfFuncEvals < MaxNumOfFuncEvals) {
		gen++;

		for (int iPop = 0; iPop < PopulationSize; iPop++) {

			// 随机挑选两个邻居
			int id1 = int(Rnd.GetNumber()*NeighborhoodSize);
			int id2 = int(Rnd.GetNumber()*NeighborhoodSize);

			/*cout << id1 << " " << id2 << endl;
			cout << "iPop:" << iPop << endl;*/

			int p1 = CurrentPopulation[iPop].IndexOfNeighbor[id1];
			int p2 = CurrentPopulation[iPop].IndexOfNeighbor[id2];

			Individual offspring;

			//cout << "p1=" << p1 << "p2=" << p2 << endl;

			offspring.UniformCrossover(CurrentPopulation[p1].CurrentSolution, CurrentPopulation[p2].CurrentSolution);
			offspring.Repair();
			//offspring.Evaluate();

			this->UpdateReferencePoint(offspring);

			this->UpdateSecondPopulation(offspring);
			
			this->UpdateNeighboringSolution(offspring, iPop);

			NumberOfFuncEvals++;

			if (NumberOfFuncEvals >= MaxNumOfFuncEvals) break;

		}
	}

	this->ShowSecondPopulation();

}