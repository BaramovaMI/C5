#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include "jordan.h"
#include <math.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <pthread.h>
#include <stdexcept>
#include <thread>

using namespace std;

long double get_full_time()
{
    struct timeval buf;
    gettimeofday(&buf, 0);
    return (double)buf.tv_sec + (double)buf.tv_usec/1000000.0;
}

void sync(int count)
{
    static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    static pthread_cond_t condvar_in = PTHREAD_COND_INITIALIZER;
    static pthread_cond_t condvar_out = PTHREAD_COND_INITIALIZER;
    static int threads_in = 0;
    static int threads_out = 0;
    
    pthread_mutex_lock(&mutex); //blocking for waiting
    
    threads_in++;
    if (threads_in >= count)
    {
        threads_out = 0;
        pthread_cond_broadcast(&condvar_in); // unblocked the rest
    }
    else
    {
        while (threads_in < count)
            pthread_cond_wait(&condvar_in, &mutex); //unblocked mutex (the folllowing can)
    }
    
    threads_out++;
    if (threads_out >= count) // so that there is no use in the loop (for exited)
    {
        threads_in = 0;
        pthread_cond_broadcast(&condvar_out);
    }
    else
    {
        while (threads_out < count)
            pthread_cond_wait(&condvar_out, &mutex);
    }
    
    pthread_mutex_unlock(&mutex);  // everyone is coming out
}


void solve(int n, double* A, double* b, double* x, int num, int count, int* prov)
{
	int i,j, k, argmax, start, end;
	double max, mnozh = 0;
	for (int i = 0; i < n*n; i++)
	{
		mnozh += A[i]*A[i];
	}
	double check = sqrt(mnozh) * 1e-15;
	for (i = 0; i < n; ++i) 
	{
		if(num==0)
		{
			max = A[i*n+i];
			argmax = i;
			for (j = i+1; j < n; ++j)
			{
				if (abs(A[j*n+i]) > abs(max))
				{
					max = A[j*n+i];
					argmax = j;
				}
			}
			if (abs(max) < check) {*prov = 0;} 
			else
			{
				if (argmax != i)
				{
					for (j = 0; j < n; ++j)
					{swap(A[i*n + j], A[argmax*n + j]);}
					swap(b[i], b[argmax]);
				}
				for (j = i + 1; j < n; ++j) {A[i*n + j] /= A[i*n + i];}
				b[i] /= A[i*n + i];
				A[i*n + i] /= A[i*n + i];
			}
		}
		sync(count);

		if(prov == 0) {return;}
		
		start = n * num / count;
		end = n * (num + 1) / count;
		
		for (j =  start; j < end; ++j)
		{
			if (j != i)
			{
				mnozh = A[j*n + i];
				for (k = i; k < n; ++k)
				{A[j*n + k] -= A[i*n+k]* mnozh;}
				b[j] -= b[i]* mnozh;
			}
		}
		
		
	    
		sync(count);
	}

	for (int i=0; i < n;i++) 
		{
			x[i] = b[i];
		}
	return;	
}
