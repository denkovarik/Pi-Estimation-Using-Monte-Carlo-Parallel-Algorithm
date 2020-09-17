#include "utilities.h"

int numThreads;

double monteCarloQuartPiEstimate(long long int numThrows)
{
    long long int insideSegment = 0;
    double x, y, dist;
    unsigned int mySeed;

#   pragma omp parallel num_threads(numThreads) default(none) \
        shared(insideSegment, numThrows) private(x,y,dist, mySeed)
    {
        mySeed = (unsigned int)omp_get_thread_num();
        srand(mySeed);
#       pragma omp for reduction(+: insideSegment) schedule(dynamic)
        for(long long int i = 0; i < numThrows; i++)
        {
            x = (double)rand_r(&mySeed) / RAND_MAX;
            y = (double)rand_r(&mySeed) / RAND_MAX;
            dist = calcDist(x, y);

            if(dist < 1.0)
                insideSegment += 1;
        }
    }

    return (double)insideSegment / numThrows;
}

    
int main(int argc, char **argv)
{
    long long int numThrows = 10000000;
    double quartPiEstimate, tot_time, t0, t1;
    double quartPi = M_PI / 4.0;
    
    // Read in command line arguments
    if(argc > 1)
        numThrows = strtoll(argv[1], NULL, 10);

    if(argc > 2)
        numThreads = atoi(argv[2]);

    t0 = omp_get_wtime();
    quartPiEstimate = monteCarloQuartPiEstimate(numThrows);
    t1 = omp_get_wtime();
    tot_time = t1 - t0;

    printf("Quart Pi Estimate: %f\n", quartPiEstimate);    
    printf("Quart Pi Actual:   %f\n", quartPi);    
    
    printf("Elapsed time = %f ms\n", tot_time);

    return 0;
}
