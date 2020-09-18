/*-----------------------------------------------------------------------------
 * File:    main.c
 *
 * Author: Dennis Kovarik
 * Date: 9/19/2020
 * Class Assignment: CSC 510 Program 1
 * 
 * Purpose: Parallel version of the Monte Carlo algorithm to estimate quarter 
 *          pi.
 *
 * Compile: gcc -g -Wall -fopenmp -o pi_redox util.c main.c -lm
 *   
 * Run:     ./pi
 *          ./pi <number of thows>
 *          ./pi <number of thows> <number of threads>
 *              number of thows:   number of simulated throws
 *              number of threads: number of threads to run in parallel
 *
 *
 * Input:   none
 * Output:  quarter pi estimation using omp parallel reduction clause
 *          runtime for the Monte Carlo Algorithm using reduction clause
 *          quarter pi estimation using omp parallel critical clause
 *          runtime for the Monte Carlo Algorithm using critical clause
 *          quarter pi actual
 *
 * Notes:
 * 1.  This program can be run with 0, 1 or 2 command line arguments
 * 2.  The first command line argument specifies the number of throws
 * 3.  The second command line argument specifies the number of threads
 *
 *---------------------------------------------------------------------------*/
#include "util.h"

int numThreads;


/**************************************************************************//**
* @author Dennis Kovarik
*
* @par Description:
* This function runs the monte carlo algorthim in parallel to estimate the 
* value of quarter pi. This function reteives random values for the x and y 
* positions of the thrown dart. The dart is determined to be inside the 
* quarter circle segment by calculating its distance from the upper left 
* corner of the board (0,0). If this distance is greater than 1, than the dart
* is outside the quarter circle. Otherwise it is considered to be inside.The 
* parallel algorithm is run using a critical clause.
*
* @param[in] numThrows - The number of simulated throws made at the board.
*
* @returns the estimation of quarter pi as a double.
******************************************************************************/
double monteCarloCritical(long long int numThrows)
{
    long long int totInsideSeg = 0;
    double x, y, dist;

#   pragma omp parallel num_threads(numThreads) default(none) \
        shared(numThrows, totInsideSeg) private(x,y,dist)
    {
        long long int insideSegment = 0;
        unsigned int mySeedCrit = (unsigned int)omp_get_thread_num();
        srand(mySeedCrit);
#       pragma omp for schedule(static)
        for(long long int i = 0; i < numThrows; i++)
        {
            x = (double)rand_r(&mySeedCrit) / RAND_MAX;
            y = (double)rand_r(&mySeedCrit) / RAND_MAX;
            dist = calcDist(x, y);

            if(dist < 1.0)
            {
                insideSegment += 1;
            }
        }
#       pragma omp critical
        totInsideSeg += insideSegment;
    }

    return (double)totInsideSeg / numThrows;
}


/**************************************************************************//**
* @author Dennis Kovarik
*
* @par Description:
* This function runs the monte carlo algorthim in parallel to estimage the 
* value of quarter pi. This function reteives random values for the x and y 
* positions of the thrown dart. The dart is determined to be inside the 
* quarter circle segment by calculating its distance from the upper left 
* corner of the board (0,0). If this distance is greater than 1, than the dart
* is outside the quarter circle. Otherwise it is considered to be inside.The 
* parallel algorithm is run using a reduction clause.
*
* @param[in] numThrows - The number of simulated throws made at the board.
*
* @returns the estimation of quarter pi as a double.
******************************************************************************/
double monteCarloReduction(long long int numThrows)
{
    long long int insideSegment = 0;
    double x, y, dist;
    unsigned int mySeed;

#   pragma omp parallel num_threads(numThreads) default(none) \
        shared(insideSegment, numThrows) private(x,y,dist, mySeed)
    {
        mySeed = (unsigned int)omp_get_thread_num();
        srand(mySeed);

#       pragma omp for schedule(static) reduction(+: insideSegment)
        for(long long int i = 0; i < numThrows; i++)
        {
            x = (double)rand_r(&mySeed) / RAND_MAX;
            y = (double)rand_r(&mySeed) / RAND_MAX;
            dist = calcDist(x, y);

            if(dist < 1.0)
            {
                insideSegment += 1;
            }
        }
    }

    return (double)insideSegment / numThrows;
}

    
/**************************************************************************//**
* @author Dennis Kovarik
*
* @par Description:
* This is the main function which is the start of the program. It will run the
* monte carlo program to estimate quarter pi and display this value to the
* screen. It will also display the actual value of quarter pi. In addition, it
* will measure and display to the screen the runtime for the monte carlo 
* algorithm.
*
* This program can be run with 0, 1, or 2 additional command line arguments.  
* If no arguments are passed in, then the program will default to simulating
* 10000000 on 4 threads. The 1st argument passed in specifies the number of 
* simulated throws, while the second argument specifies the number of threads
* to run. 
*
* @param[in] numThrows - The number of simulated throws made at the board.
* @param[in] threads   - The number of threads to run in parallel.
*
* @returns 0 if the program executed correctly.
******************************************************************************/
int main(int argc, char **argv)
{
    long long int numThrows = 10000000;
    double quartPiEstimateRedox,quartPiEstimateCritical, tot_time_redox, 
           tot_time_critical, t0, t1;
    double quartPi = M_PI / 4.0;
    numThreads = 4;
    
    // Read in command line arguments
    if(argc > 1)
        numThrows = strtoll(argv[1], NULL, 10);

    if(argc > 2)
        numThreads = atoi(argv[2]);
    
    // Run Monte Carlo Alogrithm using reduction clause
    t0 = omp_get_wtime();
    quartPiEstimateRedox = monteCarloReduction(numThrows);
    t1 = omp_get_wtime();
    tot_time_redox = t1 - t0;

    // Run Monte Carlo Alogrithm using critcal section
    t0 = omp_get_wtime();
    quartPiEstimateCritical = monteCarloCritical(numThrows);
    t1 = omp_get_wtime();
    tot_time_critical = t1 - t0;

    printf("quarter pi estimation using reduction clause\n");
    printf("quart pi estimate: %f\n", quartPiEstimateRedox);    
    printf("quart pi actual:   %f\n", quartPi);    
    printf("elapsed time = %f ms\n", tot_time_redox);
    printf("\n");
    printf("quarter pi estimation using critical section\n");
    printf("quart pi estimate: %f\n", quartPiEstimateCritical);    
    printf("quart pi actual:   %f\n", quartPi);    
    printf("elapsed time = %f ms\n", tot_time_critical);

    return 0;
}
