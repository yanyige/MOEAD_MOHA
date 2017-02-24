#include "global.h"
#include "ScheduleProblem.h"
#include "MOEAD.h"

void main() {
	int MaxNumberOfRuns = 1;

	ifstream indata;

	/****************************************
	input: fileName rand machineNumber taskNumber cycleNumber generation population
	****************************************/
	indata.open("TestInstance.txt");
	if (!indata) {
		cerr << "Error: file can not be opened" << endl;
		exit(1);
	}

	char temp[1024];

	while (!indata.eof()) {
		indata.getline(temp, 100);
		//sscanf(temp, "%s %d %d %d %d %d %d", FileName, seed, NumberOfMachine, NumberOfTasks, MyCycle, Generation, Population);
		//cout << FileName << seed << NumberOfMachine << NumberOfTasks << MyCycle << Generation << Population << endl;
		sscanf_s(temp, "%s %d %d %d %d %d %d", FileName, 100, &seed, &NumberOfMachine, &NumberOfTasks, &MyCycle, &Generation, &Population);
		 
		ScheduleProblem schedule;
		schedule.LoadInstance(FileName);

		for (int run = 1; run <= MaxNumberOfRuns; run++) {
			run_id = run;

			MOEAD moead;
			moead.Run(500);
		}


	}
}