#include <cstdio>
#include "omp.h"
#include <chrono>
#include <iostream>

void pi1_SPMD();
void pi2();

void openmp_tut() {
    pi1_SPMD();
    pi2();
}

static int num_steps = 100'000;

#define PAD 8 // assume 64 byte L1 cache line size
#define NUM_THREADS 2

//SPMD - I have thread id and I do something different based on that id
void pi1_SPMD(){
    float step;
    int i, nthreads;
    float pi, sum[NUM_THREADS][PAD]; // see below false sharing

    omp_set_num_threads(NUM_THREADS);

    step = 1/static_cast< float >(num_steps);

    auto begin = std::chrono::high_resolution_clock::now();

    #pragma omp parallel //spans default number of threads
    {
        int i, id, nthrds;
        double x;

        id = omp_get_thread_num(); //Thread ID
        nthrds = omp_get_num_threads(); // Get number of threads
        if(id==0) nthreads = nthrds; // BS

        for(i=id,sum[id][0]=0.0;i<num_steps;i+=nthrds ) { ///i = 0, 2, 4
            x = (i+0.5)*step; // middle of the step 0.5*step, 2.5*step
            sum[id][0] += 4/(1+x*x); // add f(x) to sum[id] FALSE sharing
            // Size of cache line: sum[0], sum[1] are on the SAME cache line and hence waiting to get sum[i]
        }
        // double omp_get_wtime(); // time in seconds since a fixed point in the past
    }
    for (i=0,pi=0.0;i<nthreads;i++) pi=pi+sum[i][0]/num_steps;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - begin;

    printf("My pi: %.10f, time taken: %.6f seconds\n", pi, duration.count());
    std::cout <<  " " << std::endl;
}

//pragma omp barrier     - waits for all threads to finish (even when inside #pragma) until proceeding 
//pragma omp critical{}  - execute one at time
//pragma omp atomic      - similar to critical, but uses Atomic variables: x binop= expr (eg X += 5), x++(fetch_add), ++x, x--, --x

 void pi2()
{
    float step;
    int i, nthreads;
    double x, pi, sum=0.0;
    step = 1/static_cast< float >(num_steps);
    omp_set_num_threads(NUM_THREADS);

    auto begin = std::chrono::high_resolution_clock::now();

    //schedule(static [,chunk])
    #pragma omp parallel for //private(x) reduction(+:sum)
    for (i=0; i<num_steps; i++)
    { 
        x = (i + .5)*step;
        #pragma omp atomic //this part contains error
        sum = sum + 4.0/(1.+ x*x);  
    }

    pi = sum/num_steps;
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - begin;

    printf("My pi: %.10f, time taken: %.6f seconds\n", pi, duration.count());
}