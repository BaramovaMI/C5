#include <iostream>
#include <cmath>
#include <fstream>
#include <string>

#include "jordan.h"

using namespace std;
int sgn(double );

int sgn(double m, double norm)
{
	if (m > norm) {return 1;}
	//if (m < -norm) {return -1;}
	return -1;
}

int solve(int n, double* A, double* b, double ex)
{
	int i,j, k, l;
	double x,y, sin_, cos_, check = 0, norm;
	
	// for accuracy
	for (i = 0; i < n; ++i)
	{
		for (j = i+1; j < n; ++j){check += A[i*n + j] * A[i*n + j];}
	}
	check *= 2;
	norm = check;
	for (i = 0; i < n; ++i)
	{
		norm += A[i*n + i] * A[i*n + i];
	}
	norm = sqrt(norm);
	ex *= norm;
	norm *=  1e-15;
	
	for ( i = 0; i < n; ++i ) // symmetry check
	{
		for ( j = i + 1; j < n; ++j )
		{
			if ( abs(A[i*n + j] - A[j*n + i]) > norm){return -1;}
				
		}
        }
        
	while (check > ex) 
	{
		for ( i = 0; i < n-1; ++i )
		{
			for ( j = i+1; j < n; ++j )
			{
				if (abs(A[i*n + j]) > norm) 
				{
					x = -2*A[i*n + j]; y = A[i*n + i] - A[j*n + j];
					if (abs(y) < norm) 
					{
						sin_ = 1.0 / sqrt( 2.0 );
						cos_ = 1.0 / sqrt( 2.0 );
					}
					else
					{
						cos_ = sqrt((1+(abs(y)/sqrt(x*x+y*y)))/2);
						sin_ = sgn(x*y,norm)*abs(x)/(2*cos_*sqrt(x*x+y*y));
						//cout << sgn(x*y, norm) << "\n";
					}
				
					for (k = 0; k < n; ++k) 
					{
						if (k != i && k != j)
						{
							x = A[i * n + k];
							A[i * n + k] = x * cos_ - A[j * n + k] * sin_;
							A[j * n + k] = x * sin_ + A[j * n + k] * cos_;
						}
					}
					for (k = 0; k < n; ++k)
					{
						if (k != i && k != j)
						{
							A[k * n + i] = A[i * n + k];
							A[k * n + j] = A[j * n + k];
						}
					}
					x = A[i*n + i]; y = A[j*n +j];
					A[i * n + i] = x*cos_*cos_ - 2*cos_*sin_*A[i *n + j] + sin_*sin_*y;
					A[j * n + j] = 2*A[i*n + j]*sin_*cos_ + y*cos_*cos_ + sin_*sin_*x;
					A[i * n + j] = 0.0; 
					A[j * n + i] = 0.0;
				}
			}
		}
			
		check = 0;
		for (k = 0; k < n; ++k)
		{
			for (l = k+1; l < n; ++l){check += A[k*n + l] * A[k*n + l];}
		}
		check *= 2;
	}
	
	for (i = 0; i < n; ++i){b[i] = A[i*n + i];}
	
	return 0;	
}
