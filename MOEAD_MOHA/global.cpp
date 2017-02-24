#include "global.h"


int NumberOfMachine;
int NumberOfTasks;
int MyCycle;
int Generation;
int Population;

//const int MAXN = 270;
//const int MAXM = 270;
//const int CYCLE = 3;
//int CYCLE = 3;
//const int MAXN = 200;
//const int MAXM = 200;

int run_id;
int NumberOfObj = 2;

double t[MAXM][MAXN];
double c[MAXN][MAXN];
int isdep[CYCLE][MAXN];
int todep[CYCLE][MAXN];

vector<double> ReferencePoint;

int  seed = 3133;
long rnd_uni_init = -long(seed);

char FileName[100];