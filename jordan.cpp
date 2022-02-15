#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include "jordan.h"

using namespace std;

int main(int argn, char **args)
{
	if (argn < 4)
	{
		cout << "Malo argumentov" << endl;
		return -1;
	}

	clock_t start, end;
	int prov, i,j;
	int n ;
	int m ;
	int k ;

	if (sscanf(args[1], "%d", &n) != 1 || sscanf(args[2], "%d", &m) != 1 || sscanf(args[3],"%d", &k) != 1)
	{
		cout << "Invalid format \n";
		return -1;
	}

	try
	{

		double *A = new double[n*n];
		double *b = new double[n];
		double *x = new double[n];
		double *N = new double[n*(n+1)];
		double *N1 = new double[n];

		if (k == 0)
		{   
		    if(args[4] == nullptr)
		    {
		        cout << "Invalid format" << endl;
		        return -1;
		    }
		}
	
		prov = vvod(args[4], n, A, k);
		if (prov != 0)
		{
			printf("Error \n");
			return -1;
		}
		vivod(n, m, m, A);
		
		cout << " \n b: " << endl;
		nashb(n, A, b);
		vivod(n, m, 1, b);

		
		for (i = 0; i < n; ++i)
		{
			for (j = 0; j < n; ++j) { N[i*n + j] = A[i*n + j];}
			N1[i] = b[i];
		}
		
		start = clock();
		prov = solve(n, A, b, x);
		end = clock();
		
		if (prov == 0) 
		{
			cout << " \n x: \n";
			vivod(n, m, 1, x); 
			printf ("Norm: %10.5e \n", norma(n, N, x, N1));
		}
		if (prov == -1) {cout << "Degenerate matrix" << endl;}
		
		
		printf("Time is %10.3e second(s) \n", ((double) (end - start)) / ((double) CLOCKS_PER_SEC)); // время работы программы 
		delete[] A;
		delete[] b;
		delete[] x;
		delete[] N;
		delete[] N1;
	
	}        
	catch(const std::exception& e)
	{
		std::cerr << e.what() << " caught and handled (million ne prokatit kstati :))" << endl;
		return -1;
	}
	return 0;
}
