// RandomNumber.h: interface for the CRandomNumber class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RANDOMNUMBER_H__3E74075C_CF04_4B65_95F0_F724E8D74CF3__INCLUDED_)
#define AFX_RANDOMNUMBER_H__3E74075C_CF04_4B65_95F0_F724E8D74CF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define IM1 2147483563
#define IM2 2147483399
#define AM (1.0/IM1)
#define IMM1 (IM1-1)
#define IA1 40014
#define IA2 40692
#define IQ1 53668
#define IQ2 52774
#define IR1 12211
#define IR2 3791
#define NTAB 32
#define NDIV (1+IMM1/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)
double rnd_uni(long *idum);

#include "Global.h"

class CRandomNumber {
public:
	CRandomNumber();
	virtual ~CRandomNumber();

public:
	double GetNumber();
	double rnd_uni(long *idum);
};

#endif // !defined(AFX_RANDOMNUMBER_H__3E74075C_CF04_4B65_95F0_F724E8D74CF3__INCLUDED_)
