#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "jordan.h"

using namespace std;

double norma(int n, double* A, double* b)
{
	double sled = 0;
	double sob = 0;
	for (int i = 0; i < n; ++i)
	{
		sled += A[i*n + i];
		sob += b[i];
	}
	
	return abs(sled - sob);
} 

double norma2(int n, double* A, double* b)
{
	double sled = 0;
	double sob = 0;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j) {sled += A[i*n + j] * A[i*n + j];}
		sob += b[i] * b[i];
	}
	
	return abs(sqrt(sled) - sqrt(sob));
}
