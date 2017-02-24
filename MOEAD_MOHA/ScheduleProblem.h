#pragma once
#ifndef __SCHEDULEPROBLEM_H_
#define __SCHEDULEPROBLEML_H_

#include "global.h"

class ScheduleProblem {
public: 
	ScheduleProblem();
	~ScheduleProblem();
public:
	/*double t[MAXM][MAXN];
	double c[MAXN][MAXN];*/
	
	/*int taskIndex[MAXN];
	bool taskUsed[MAXN];*/
	


public:
	bool LoadInstance(char *Filename);

	
};

#endif