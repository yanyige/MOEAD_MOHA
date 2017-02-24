
#include "Individual.h"


Individual::Individual() {

	vector<int> temp;
	vector< vector<int> > temp1(NumberOfMachine, temp);

	machine = temp1;
}

Individual::~Individual() {

}

void insertMachine(Individual *ind, int a, int b, int c) { // a = taskIndex[nowPoint], b = nowPoint, c = temp
	vector<int>::iterator iter;
	int j = 0;
	int k = 0;
	// delete temp
	for (j = 0; j < NumberOfMachine; j++) {
		for (iter = ind->machine[j].begin(); iter != ind->machine[j].end(); iter++) {
			if ((*iter) == c) {
				ind->machine[j].erase(iter);
				iter = ind->machine[b].begin();
				while (k < a) {
					k++;
					iter++;
				}
				ind->machine[b].insert(iter, c);
				return;
			}
		}
	}

	return;
}

void Individual::Randomize() {

	set<int> flag_machine;
	stack<int> segment;
	set<int> interval;
	int kk, kkk, tempkk;
	vector<int>::iterator iter;
	set<int>::iterator iiter;

	flag_machine.clear();
	while (!segment.empty()) {
		segment.pop();
	}

	for (int j = 0; j < NumberOfTasks * 2; j++) {
		int temp = rand() % NumberOfTasks;
		if (flag_machine.insert(temp).second) {
			segment.push(temp);
		}
	}
	for (int k = 0; k < NumberOfTasks; k++) {
		if (flag_machine.insert(k).second) {
			segment.push(k);
		}
	}

	interval.clear();
	kk = NumberOfMachine - 1;
	while (kk) {
		int temp = rand() % (NumberOfTasks);
		if (temp == 0) temp = 1;
		while (!interval.insert(temp).second) {
			temp = rand() % (NumberOfTasks);
			if (temp == 0) temp = 1;
		}
		kk--;
	}
	kkk = 0;
	for (iiter = interval.begin(); iiter != interval.end(); iiter++) {
		if (iiter == interval.begin()) {
			kk = (*iiter);
		}
		else {
			kk = (*iiter) - kk;
		}
		tempkk = kk;
		while (tempkk--) {
			this->machine[kkk].push_back(segment.top());
			segment.pop();
		}
		kkk++;
		kk = (*iiter);
	}

	kk = NumberOfTasks - kk;
	tempkk = kk;
	while (tempkk--) {
		this->machine[kkk].push_back(segment.top());
		segment.pop();
	}
	//repair_segment(&Collection[i]);
	//printf("��ʼ���ɹ�!\n");
}

void Individual::Repair() {

	

	vector<int>::iterator iter;
	/***************initialize******************/
	    //printf("repairǰ�Ľ��\n");
	    //for(int j = 0 ; j < NumberOfMachine ; j ++){
	    //    printf("��%d������: ", j);
	    //    for(iter = this->machine[j].begin(); iter != this->machine[j].end() ; iter ++){
	    //        printf("%d ", (*iter));
	    //    }
	    //    printf("\n");
	    //}
	/***************~initialize******************/
	memset(taskIndex, 0, sizeof(taskIndex));
	int acTask = 0;
	int nowPoint = 0;
	int depentTask[MAXM];
	bool dependent = false;
	memset(taskUsed, 0, sizeof(taskUsed));
	doneSet.clear();
	/*******************done********************/
	while (acTask < NumberOfTasks) {
		        //printf("actask = %d\n", acTask);
		dependent = false;
		for (nowPoint = 0; nowPoint < NumberOfMachine; nowPoint++) { // �����е�ָ�����ѭ��
													   //            printf("size = %d\n", i->machine[nowPoint].size());
													   //            printf("taskindex = %d\n", taskIndex[nowPoint]);
			if (this->machine[nowPoint].size() == taskIndex[nowPoint]) {
				//                    dependent = true;
				depentTask[nowPoint] = -1; // ���ָ��ָ�����һ������ĺ��棬˵����������Ѿ���ɣ�����������-1.
				continue; // ���ָ��ָ�����һ��Ԫ�أ�����
			}
			int nowTask = this->machine[nowPoint].at(taskIndex[nowPoint]);
			            //printf("nowPoint = %d\n", nowPoint);
			            //printf("nowTask = %d\n", nowTask);
			depentTask[nowPoint] = test(nowTask);
			//            printf("depentTask[nowPoint] = %d\n", depentTask[nowPoint]);
			if (depentTask[nowPoint] == -1) { // ����ܷ���������ָ����Ʋ��ҿ�����Ļ�����+1.
				taskIndex[nowPoint] ++;
				acTask++;
				taskUsed[nowTask] = true;
				doneSet.insert(nowTask);
				dependent = true;
				break;
			}
		}

		if (dependent == false) {
			            //printf("����������\n");
			int machine = rand() % NumberOfMachine;

			int temp = rand() % NumberOfMachine;
			//            printf("ѡ��Ļ�����%d\n", temp);
			while (depentTask[temp] == -1) temp = rand() % NumberOfMachine;
			//            int number = rand() % m;
			//            while(depentTask[number] == -1) number = rand() % m;
			insertMachine(this, taskIndex[machine], machine, depentTask[temp]);
			//            printf("�����Ľ��\n");
			//            for(int j = 0 ; j < m ; j ++){
			//                printf("��%d������: ", j);
			//                for(iter = i->machine[j].begin(); iter != i->machine[j].end() ; iter ++){
			//                    printf("%d ", (*iter));
			//                }
			//                printf("\n");
			//            }
		}
	}

	//printf("repair�ɹ�!\n");

}



int Individual::test(int task) {
	int i;
	int tot = 0;
	int arr[MAXN];
	memset(arr, 0, sizeof(arr));
	for (i = 0; i < NumberOfTasks; i++) {
		if (c[i][task] > 0) {
			if (doneSet.find(i) == doneSet.end() && taskUsed[i] == false) { //���û���ҵ�
				arr[tot++] = i;
			}
		}
	}
	if (tot == 0)return -1;
	else {
		int random = rand() % tot;
		return arr[random];
	}
}

void Individual::Evaluate() {

	//printf(" Evaluating!\n");
	vector<int>::iterator iter;
	vector<int>::iterator jter;

	this->n = inf;
	this->makespan = 0;
	this->workload = 0;
	double depcopy[CYCLE][MAXN][MAXN];
	int isdepcopy[CYCLE][MAXN], todepcopy[CYCLE][MAXN];
	for (int k = 0; k<MyCycle; k++) {
		for (int ii = 0; ii<NumberOfTasks; ii++) {
			isdepcopy[k][ii] = isdep[k][ii];
			todepcopy[k][ii] = todep[k][ii];
			for (int j = 0; j<NumberOfTasks; j++) {
				depcopy[k][ii][j] = c[ii][j];
			}
		}
	}

	double load[MAXM];
	memset(load, 0, sizeof(load));
	int jud_index[MAXM], flag_end[MAXM], position;
	memset(jud_index, 0, sizeof(jud_index));
	memset(flag_end, 0, sizeof(flag_end));
	double E[MAXM];
	memset(E, 0, sizeof(E));
	double tao[CYCLE][MAXN];
	double taoend[CYCLE][MAXN];
	double Lstart, ltemp;
	int it = 1, task_in_machine[MAXN];
	double avg = 0, workload = 0;
	for (int j = 0; j < NumberOfTasks; j++) {
		avg += t[0][j];
	}
	avg /= NumberOfMachine;
	for (int j = 0; j < NumberOfMachine; j++) {
		for (iter = this->machine[j].begin(); iter != this->machine[j].end(); ++iter) {
			task_in_machine[*iter] = j;
			load[j] = load[j] + t[j][(*iter)];

		}
		workload += abs(load[j] - avg);

	}
	this->workload = workload;
	while (it <= NumberOfTasks*MyCycle) {
		for (int ii = 0; ii<NumberOfMachine; ii++) {
			if (flag_end[ii] == MyCycle || this->machine[ii].empty()) {
				continue;
			}
			position = this->machine[ii].at(jud_index[ii]);


			if (isdepcopy[flag_end[ii]][position] == 0) {

				Lstart = E[ii];
				for (int kk = 0; kk<NumberOfTasks; kk++) {
					if ((c[kk][position]>0) && (task_in_machine[kk] != task_in_machine[position])) {
						ltemp = taoend[flag_end[ii]][kk] + c[kk][position] + 2;
						if (ltemp>Lstart) {
							Lstart = ltemp;
						}
					}
				}

				tao[flag_end[ii]][position] = Lstart;
				E[ii] = tao[flag_end[ii]][position] + t[ii][position];
				taoend[flag_end[ii]][position] = E[ii];
				for (int kk = 0; kk<NumberOfTasks; kk++) {
					if (c[position][kk]>0 && (task_in_machine[kk] != task_in_machine[position])) {
						E[ii] += 2;
						break;
					}
				}
				it++;
				for (int jj = 0; jj<NumberOfTasks; jj++) {
					if (depcopy[flag_end[ii]][position][jj]>0 && position != jj) {

						depcopy[flag_end[ii]][position][jj] = 0.0;
						isdepcopy[flag_end[ii]][jj]--;
						todepcopy[flag_end[ii]][position]--;
					}
				}
				if (position == (*(this->machine[ii].rbegin()))) //
				{
					flag_end[ii]++;
					jud_index[ii] = 0;
				}
				else {
					jud_index[ii]++;
				}

			}
		}
	}

	for (int jj = 0; jj<NumberOfMachine; jj++) {
		if (E[jj]>this->makespan) {
			this->makespan = E[jj];
		}
	}

	//printf(" Evaluate done! \n");
}

void Individual::Show() {
	vector<int>::iterator iter;
	
	cout << "���Ind�Ļ���������: " << endl;

	for(int j = 0 ; j < NumberOfMachine ; j ++){
	    printf("��%d������: ", j);
	    for(iter = this->machine[j].begin(); iter != this->machine[j].end() ; iter ++){
	        printf("%d ", (*iter));
	    }
	    printf("\n");
	}																
																	
	cout << " ���Ind��makespan�ǣ�" << " " << this->makespan << endl;
	cout << " ���Ind��workload�ǣ�" << " " << this->workload << endl;

}

void Individual::UniformCrossover(Individual &parent1, Individual &parent2) {
	int myMap[MAXN][2];

	int temp = rand() % 10;

	//parent1.Show();
	
	//parent2.Show();

	for (int j = 0; j < NumberOfMachine; ++j) {
		//cout << "j = " << j << endl;
		for (int i = 0; i < parent1.machine[j].size(); i ++) {
			myMap[parent1.machine[j][i]][0] = j;
			//cout << "myMap[" << parent1.machine[j][i] << "][0]=" << j << endl;
		}
		for (int i = 0; i < parent2.machine[j].size(); i++) {
			myMap[parent2.machine[j][i]][1] = j;
			//cout << "myMap2[" << parent2.machine[j][i] << "][1]=" << j << endl;
		}
	}

	for (int i = 0; i < NumberOfTasks; ++i) {
		int temp = rand() % 2;
		this->machine[myMap[i][temp]].push_back(i);//����һ���µĸ���,���浽individual��
		//cout << myMap[i][temp] << endl;
		//cout << this->machine[myMap[i][temp]][0] << endl;
	}
}

bool Individual::operator>(const Individual& indiv) {
	if (indiv.makespan > makespan || indiv.workload>workload) {
		return false;
	}
	return true;
}

bool Individual::operator<(const Individual& indiv) {
	if (indiv.makespan < makespan || indiv.workload < workload) {
		return false;
	}
	return true;
}

bool Individual::operator==(const Individual& ind) {
	if (ind.makespan != makespan || ind.workload != workload) {
		return false;
	}
	return true;
}
