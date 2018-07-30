#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define size 10000000

int main(int argc, char ** argv) {
    int n = 10000000;
	//maximum static array alocation is size of an int
    //static double x[size];
    //double x[size];
    double *x = (double *)malloc(sizeof(double)*n);
    double *y = (double *)malloc(sizeof(double)*n);
    double *z = (double *)malloc(sizeof(double)*n);
    double *z2 = (double *)malloc(sizeof(double)*n);
    double min=0.0;
    double max = 10.0;
    double step = (min-max)/(double)(n-1);
    int i,iter;
    int itmax = 100;
    clock_t start, stop;
    double elapsed_time;
    
//took the "static" variable outside of the loop
//moved invariant calculation out of the loop
    double pi = acos(-1.0);
//combied the operations on ,y and z into a single loop as there is no need for 3 if you can do these sequentially 
    start = clock();
    for(i=0;i<n;i++) 
	{
        x[i] = min+(double)i*step;
        //took out the pow function call, reduced to x[i]*x[i] to exclude the unneeded library call to square using pow()
        y[i] = exp(-((x[i]-5.0)*(x[i]-5.0) ));
		z[i] = y[i]*sin((x[i]-min)/(max-min)*2.0*pi);
    }  
    

    
//included the operation on z into the first for loop and modified the indeces used in the line
    for(iter=0;iter<itmax;iter++) 
	{
        z2[0] = 0.5*(z[0]+z[1]);
        z2[n-1] = 0.5*(z[n-1]+z[n-2]);
        for(i=1;i<n-1;i++) 
		{
            z2[i] = (1.0/3.0)*(z[i-1]+z[i]+z[i+1]);
            z[i-1] = z2[i-1]*y[i-1];
        }
//included the last two operations that need to be done on the z array
//done this way to ensure the array is accessed in a sequential manner

        z[n-2] = z2[n-2]*y[n-2];
		z[n-1] = z2[n-1]*y[n-1];
    }
    stop = clock();
    elapsed_time = (stop-start)/(double)CLOCKS_PER_SEC;

    printf("ELAPSED TIME = %f\n",elapsed_time);

    //free(x);
    free(y);
    free(z);
    free(z2);
}
