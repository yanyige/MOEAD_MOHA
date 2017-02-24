#include "ScheduleProblem.h"

ScheduleProblem::ScheduleProblem() {

}

ScheduleProblem::~ScheduleProblem() {

}

bool ScheduleProblem::LoadInstance(char *fileName) {

	//printf("begin!");
	fstream Stream(fileName, ios::in);

	cout << "***************************************************" << endl;
	cout << " 开始读取: " << fileName << endl;

	for (int i = 0; i < NumberOfTasks; i++) {
		Stream >> t[0][i];
	}

	for (int i = 1; i < NumberOfMachine; i++) {
		for (int j = 0; j < NumberOfTasks; j++) {
			t[i][j] = t[0][j];
		}
	}

	for (int i = 0; i < NumberOfTasks; i++) {
		for (int j = 0; j < NumberOfTasks; j++) {
			Stream >> c[i][j];
		}
	}

	for (int i = 0; i < NumberOfTasks; i++) {
		for (int j = 0; j < CYCLE; j++) {
			isdep[j][i] = 0;
			todep[j][i] = 0;
		}
	}

	for (int i = 0; i < NumberOfTasks; i++) {
		for (int j = 0; j < NumberOfTasks; j++) {
			if (c[i][j]>0) {
				todep[0][i]++;
				isdep[0][j]++;
			}
		}
	}

	for (int i = 1; i<CYCLE; i++) {
		for (int j = 0; j<NumberOfTasks; j++) {
			todep[i][j] = todep[0][j];
			isdep[i][j] = isdep[0][j];
		}
	}


	printf(" 读取 Schedule Problem [ %s ] OK ! \n", fileName);

	/***************initialize******************/
	//检查初始化结果
	//for (int i = 0; i < NumberOfTasks; i++) {
	//	cout << t[0][i] << "*";
	//}

	//for (int i = 0; i < NumberOfTasks; i++) {
	//	for (int j = 0; j < NumberOfTasks; j++) {
	//		cout << c[i][j] << " ";
	//	}
	//	cout << endl;
	//}
	/***************~initialize******************/

	return true;
}