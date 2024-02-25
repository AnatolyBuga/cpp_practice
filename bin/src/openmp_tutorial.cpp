#include <cstdio>
#include "omp.h"
#include <chrono>
#include <iostream>

void pi1_SPMD();
void pi2();
auto pi_reduction() -> void;
auto locks() -> void;

void openmp_tut() {
    pi1_SPMD();
    pi2();
    pi_reduction();
    locks();
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
//pragma omp master{}    - only master thread will do work inside that region, good to add barrier after
//pragma omp single{}    - only one thread will do the work. Whichever grabs work first. Implied barrier. If don't want to wait - see nowait
//pragma omp sections{}  - split sections between threads
//pragma omp section
// omp_init_lock()
// omp_set_lock()
// omp_unset_lock()
// omp_destroy_lock()
// omp_set_schedule()
// omp_get_max_threads()
// omp_in_parallel() - am I in parallel region?
// omp_set_dynamic() - set dynamic mode each par region might give you a different number of threads. set to 0 to stop changing number of threads
// omp_get_dynamic() - am I in dynamic mode?
// omp_num_procs()
// omp_set_num_threads()
// omp_get_num_threads() - if not in par region - will return 1

// env vars
// OMP_NUM_THREADS
// OMP_STACKSIZE - this is how much stack size I want you to put aside
// OMP_WAIT_POLICY - what thread is doing while waiting (ACTIVE(spin lock)/PASSIVE(park thread))
// OMP_PROC_BIND - bind thread to a processor/core. Use when data is precached in the processor's stack

 void pi2()
{
    float step;
    int i, nthreads;
    double x, pi, sum=0.0;
    step = 1/static_cast< float >(num_steps);
    omp_set_num_threads(NUM_THREADS);

    auto begin = std::chrono::high_resolution_clock::now();

    //schedule(static[,CHUNK]) eg 100 iterations. CHUNK=10. then 10x10(CHUNK) blocks to works on in parallel
    //schedule(dynamic[,CHUNK]) deciding AT run time, by each thread grabbing a CHUNK, completing, then next
    //schedule(guided[,CHUNK]) starts with a large CHUNK and reduces it to the CHUNK as proceeds
    //schedule(runtime) through OMP_SCHEDULE env variable or runtime lib
    //schedule(auto) leave it up to the runtime
    

    //reduction(op:list)
    //each thread gets its local copy of sum
    //each thread does local summation of the average
    //then combines using the op
    #pragma omp parallel for //private(x) reduction(+:sum)
    for (i=0; i<num_steps; i++)
    { 
        x = (i + .5)*step;
        #pragma omp atomic
        sum = sum + 4.0/(1.+ x*x);  
    }

    pi = sum/num_steps;
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - begin;

    printf("My pi: %.10f, time taken: %.6f seconds\n", pi, duration.count());
}

 auto pi_reduction() -> void
{
    float step;
    int i, nthreads;
    double x, pi, sum=0.0;
    step = 1/static_cast< float >(num_steps);
    omp_set_num_threads(NUM_THREADS);

    auto begin = std::chrono::high_resolution_clock::now();

    //reduction(op:list)
    //each thread gets its local copy of sum
    //each thread does local summation of the average
    //then combines using the op
    //private variable created uninitialised
    //private goes out of scope when finished
    //firstprivate - same as private, but initialised to the global value
    //lastprivate - last iteration (whatever thread) - copy that value to the global scope
    // https://stackoverflow.com/questions/6358375/openmp-are-local-variables-automatically-private
    // There is an implied BARRIER at the end of each loop (importnat when omp for is inside omp parallel) 
    // if don't want to wait for the barrier add nowait
    #pragma omp parallel for private(x) reduction(+:sum) 
    for (i=0; i<num_steps; i++)
    { 
        x = (i + .5)*step;
        sum += 4.0/(1.+ x*x);  
    }

    pi = sum/num_steps;
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - begin;

    printf("My pi: %.10f, time taken: %.6f seconds\n", pi, duration.count());
}

auto locks() -> void {
    const int NITEMS=20;
    int array[NITEMS];
    omp_lock_t lock[NITEMS];

    for (int i=0; i<NITEMS; i++)
        omp_init_lock(&(lock[i]));

    // default(none) - I require to spell out shared/private state of each variable
    #pragma omp parallel for shared(array, lock) default(none)
     for (int i=0; i<NITEMS; i++) {
        int tid = omp_get_thread_num();
        int item = (i * 7) % NITEMS;

        omp_set_lock(&(lock[item]));
        array[item] = tid;    // only one thread in here at a time; others block at set_lock()
        omp_unset_lock(&(lock[item]));
    }

    for (int i=0; i<NITEMS; i++)
        printf("%3d ", array[i]);
    printf("\n");

    for (int i=0; i<NITEMS; i++)
        omp_destroy_lock(&(lock[i]));
}

// Task - independent unit of work
// Task - code, data, internal control variables (like omp_num_threads)
//pragma omp task - each thread will create the task, eg task will be called foo() 
//if inside single , then only one thread
//pragma omp taskwait - wait for tasks
// https://stackoverflow.com/questions/13788638/difference-between-section-and-task-openmp