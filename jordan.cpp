#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include "jordan.h"
#include <thread>
#include <pthread.h>
#include <stdexcept>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <sys/resource.h>

using namespace std;

/*int main1(int argn, char **args);

int main(int argn, char **args)
{
	while(1)
	main1(argn,args);
} */

struct _kak_nibud_now_pridumayu;
typedef _kak_nibud_now_pridumayu work;
struct _kak_nibud_now_pridumayu
{
    double *A;
    double *b;
    double *x;
    int n;
    int num;
    int count;
    int* prov;
    long double thread_time;
    
};

void *do_stuff(void *d)
{
	work *data = (work*)d;
	
	sync(data->count);
	data->thread_time = get_full_time();
	
	solve(data->n, data->A, data->b, data->x, data->num,
                 data->count, data->prov);
	
	data->thread_time = get_full_time() - data->thread_time;
	sync(data->count); 
	//if (data->num == 0) {printf("Working time 0 thread: %Lf sec.\n", total_time);}

    return NULL;
    
}

int main(int argn, char **args)
{
	long double total_time, total_time_norm;
	int i, j, n, m, k, count;
	int prov = 1;
	
	if (argn < 5)
	{
		cout << "Malo argumentov" << endl;
		return -1;
	}
	if (sscanf(args[1], "%d", &n) != 1 || sscanf(args[2], "%d", &count) != 1 || sscanf(args[3], "%d", &m) != 1 || sscanf(args[4],"%d", &k) != 1 )
	{cout << "Invalid format \n" << endl; return -1;}
	if (count < 1) 
	{cout << "Threads must be greater than 0 \n" << endl; return -1;}
	if (m > n||m <= 0){cout<<"Incorrect input data"; return -1;}
	if (k == 0)
	{   
	    if(args[5] == nullptr)
	    {cout << "Invalid format" << endl; return -1;}
	}

	try
	{

		double *A = new double[n*n];
		double *b = new double[n];
		double *x = new double[n];
		double *N = new double[n*n];
		double *N1 = new double[n];
		
		work *w = new work[count];
		pthread_t *threads = new pthread_t[count];
		
		int pr = vvod(args[5], n, A, k);
		if (pr != 0)
		{
			cout << "Error \n" << endl; 
			return -1;
		}
		vivod(n, m, m, A);
		
		cout << " \n b: " << endl;
		nashb(n, A, b);
		vivod(n, m, 1, b);
		cout << "\n";

		
		for (i = 0; i < n; ++i)
		{
			for (j = 0; j < n; ++j) { N[i*n + j] = A[i*n + j];}
			N1[i] = b[i];
		}
		
		for (i = 0; i < count; ++i)
		{
			w[i].A = A;
			w[i].b = b;
			w[i].x = x;
			w[i].n = n;
			w[i].num = i;
			w[i].count = count;
			w[i].prov = &prov;
		}

		for (i = 0; i < count; ++i)
		{
			if (pthread_create(threads + i, 0, do_stuff, w + i))
			{
				printf("Not created \n");
				delete []A;
				delete []b;
				delete []N;
				delete []x;
				delete []N1;
				delete []w;
				delete []threads;
				return -1;
			}
		}

		total_time = get_full_time();

		for (i = 0; i < count; ++i)
		{
			if (pthread_join(threads[i], 0))
			{
				delete []A;
				delete []b;
				delete []N;
				delete []N1;
				delete []w;
				delete []threads;
				delete []x;
				return -1;
			}
		}
		
		total_time = get_full_time() - total_time;
		
		if(!prov)
		{
			cout << "Degenerate matrix" << endl;
			delete []A;
			delete []b;
			delete []N;
			delete []N1;
			delete []w;
			delete []x;
			delete []threads;
			return -1;
		}
		
		cout << " \n x: \n";
		vivod(n, m, 1, x);
		
		total_time_norm = get_full_time();
		
		// vivod(n, m, n, A);
		
		double norm = norma(n, N , x, N1);
		
		total_time_norm = get_full_time() - total_time_norm;
		
		printf("Norm time: %Lf sec.\n", total_time_norm);
		
		printf("%s : residual = %e elapsed = %.2Lf s = %d n = %d m = %d p = %d \n",args[0], norm, total_time , k, n, m, count);
		
		delete []A;
		delete []b;
		delete []N;
		delete []N1;
		delete []w;
		delete []x;
		delete []threads;
	
	} 
	      
	catch(const exception& e)
	{
		std::cerr << e.what() << " caught and handled (million ne prokatit kstati :))" << endl;
		return -1;
	}
	return 0;
}
