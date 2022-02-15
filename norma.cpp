#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "jordan.h"

using namespace std;

double norma(int n, double* A, double* x, double* b)
{
	double Ax;
	double Axb = 0;
	double b2 = 0;
	for (int i = 0; i<n; ++i)
	{
		Ax=0;
		for (int j=0; j<n; ++j) {Ax += A[i*n+j]*x[j];}
		Axb += pow(Ax-b[i], 2);
		b2 +=pow(b[i], 2);
	}
	return sqrt(Axb)/sqrt(b2);
} 
