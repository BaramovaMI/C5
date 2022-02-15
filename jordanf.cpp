#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include "jordan.h"

double jordanf(int, int , int , int);

double jordanf(int k, int n , int i, int j) //f
{
	if (k==1) { return n+1 - fmax(i,j) + 1; }
	if (k==2) { return fmax(i,j); }
	if (k==3) { return abs(i-j); }
	if (k==4) { return 1.0 /(i+j - 1); }
	return 0;
}

double vvod(char* input, int n, double* A, int k)
{
	
	int i,j;
        if (k==0)
        {
		FILE *in;
		in = fopen(input, "rt");
		if(in == NULL){return -1;}
		for (i = 0; i < n*n; ++i)
		{
			if(fscanf(in, "%lf", &A[i]) != 1){return -1;}
		}
		fclose(in);
        }
        else 
	{
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				A[i*n + j] = jordanf(k, n, i+1, j+1);
			}
		}
	}
        return 0;
}
