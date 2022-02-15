#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include "jordan.h"

using namespace std;

int main(int argn, char **args)
{
	if (argn < 5)
	{
		cout << "Malo argumentov" << endl;
		return 0;
	}

	clock_t start, end;
	int prov, i,j;
	int n;
	int m;
	double ex;
	int k;
	
	if (sscanf(args[1], "%d", &n) != 1 || sscanf(args[2], "%d", &m) != 1 || sscanf(args[3], "%lf", &ex) != 1 || sscanf(args[4], "%d", &k) != 1)
	{
		cout << "Invalid format" << endl;
		return -1;
	}
	if (k == 0)
		{   
		    if(args[4] == nullptr)
		    {
		        cout << "Invalid format" << endl;
		        return -1;
		    }
		}
		
	
		
	try
	{

		double *A = new double[n*n];
		double *b = new double[n];
		double *N = new double[n*n];

		prov = vvod(args[5], n, A, k);
		if (prov != 0)
		{
			printf("Error \n");
			delete[] A;
			delete[] b;
			delete[] N;
			return -1;
		}
		
		vivod(n, m, m, A);
		
		for (i = 0; i < n; ++i)
		{
			for (j = 0; j < n; ++j) { N[i*n + j] = A[i*n + j];}
		}
		
		start = clock();
		prov = solve(n, A, b, ex);
		end = clock();
		
		if (prov == 0) 
		{
			cout << " \n Eigenvalues: \n";
			vivod(n, m, 1, b);
			printf ("Norma 1: %10.5e \n", norma(n, N, b));
			printf ("Norma 2: %10.5e \n", norma2(n, N, b));
		}
		if (prov == -1) {cout << "Asymmetric Matrix" << endl;}
		
		
		printf("Time is %10.3e second(s) \n", ((double) (end - start)) / ((double) CLOCKS_PER_SEC)); // время работы программы 
		delete[] A;
		delete[] b;
		delete[] N;
	
	}        
	catch(const std::exception& e)
	{
		std::cerr << e.what() << " caught and handled." << endl;
		return -1;
	}
	return 0;
}
