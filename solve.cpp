#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include "jordan.h"

using namespace std;

int solve(int n, double* A, double* b, double* x)
{
	int i,j, k, argmax;
	double max, mnozh = 0;
	for (int i = 0; i < n*n; i++)
	{
		mnozh += pow(A[i],2);
	}
	double check = sqrt(mnozh) * 1e-15;
	for (i = 0; i < n; ++i) 
	{
		max = A[i*n+i];
		argmax = i;
		for (j = i+1; j < n; ++j) // looking for the maximum in the column
		{
			if (abs(A[j*n+i]) > abs(max))
			{
				max = A[j*n+i];
				argmax = j;
			}
		}
		
		if (abs(max) < check) {return -1;} 

		if (argmax != i)
		{
		
			for (j = 0; j < n; ++j) // swap lines
			{
				swap(A[i*n + j], A[argmax*n + j]);
			}
			swap(b[i], b[argmax]);
		}
		for (j = i + 1; j < n; ++j) // normalize
		{
			A[i*n + j] /= A[i*n + i];
		}
		b[i] = b[i]/A[i*n + i];
		A[i*n + i] /= A[i*n + i];

		for (j = 0; j < n; ++j) //subtrack, it turns out
		{
			if (j != i)
			{
				mnozh = A[j*n + i];
				for (k = i; k < n; ++k)
				{
					A[j*n + k] -= A[i*n+k]* mnozh;
				}
				b[j] -= b[i]* mnozh;
			}
		}
	}
	for (int i=0; i < n;i++) 
		{
			x[i] = b[i];
		}
	return 0;	
}
