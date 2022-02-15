#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include "jordan.h"

int nashb(int n, double *A, double *b)
{
	int i,k;
	for (i = 0; i < n; ++i)
	{
		b[i] = 0;
		for (k = 0; k < n; k+=2)
		{
			b[i] += A[ i*n  + k];
		}
	}
	return 0;
}
