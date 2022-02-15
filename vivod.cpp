#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include "jordan.h"

void vivod(int n,int m,int t, double* x)
{
	for (int i=0; i < t;i++) 
	{
		for (int j=0; j < m; j++)
		{
			printf(" %10.3e", x[i*n + j]);
		}
		printf("\n");
	}
}
