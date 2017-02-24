#ifndef __GLOBAL_H_
#define __GLOBAL_H_

#include<cstdlib>
#include<cmath>
#include<fstream>
#include<iostream>
#include<vector>
#include<ctime>
#include<string>
#include<set>
#include<stack>

using namespace std;

extern int seed;
const int MAXN = 200;
const int MAXM = 200;
const int CYCLE = 3;

extern int NumberOfMachine;
extern int NumberOfTasks;
extern int MyCycle;
extern int Generation;
extern int Population;
extern int run_id;

extern char FileName[100];

extern vector<double> ReferencePoint;
extern int NumberOfObj;

extern double t[MAXM][MAXN];
extern double c[MAXN][MAXN];
extern int isdep[CYCLE][MAXN];
extern int todep[CYCLE][MAXN];

const int inf = 0x3f3f3f3f;

extern int  seed;
extern long rnd_uni_init;

#endif