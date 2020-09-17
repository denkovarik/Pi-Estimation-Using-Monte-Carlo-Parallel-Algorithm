# Pi Estimation Using Monte Carlo Parallel Algorithm

## Introduction
This program runs the Monte Carlo Algorithm to estimate a quarter pi. Suppose we toss darts randomly at a square dartboard whose sides are 1 ft in length. Suppose also that there is a quarter circle segment with radius 1 ft inscribed in the square dartboard, from the top left corner, to the lower right corner. If the points that are hit by the darts are uniformly distributed (and always landing in the square), then the number of darts that hit inside the circle segment versus the total number of darts thrown should approximately satisfy a quarter of π: 

                                    π / 4 = darts inside cicle segment / total number of darts tossed

This is a so called Monte Carlo process, as it uses randomness to solve a problem.

## Setup

### Clone the Repo
https: 
* git clone https://gitlab.com/dennis.kovarik/pi-estimation-using-monte-carlo-parallel-algorithm.git
ssh:
* git clone git@gitlab.com:dennis.kovarik/pi-estimation-using-monte-carlo-parallel-algorithm.git

### Compile the program
Run the Following command in the terminal
* make

## Testing
### Compile the Test
* make Test

### Run the Test
* ./runTests

## Usage
This program can be run with 0, 1, or 2 command line arguments passed into the program. The first command line argument specifies the number of simulated throws to use to estimate quarter pi using the Monte Carlo Algorithm. The second command line argument specifies the number of threads to run in parallel.
* ./pi
* ./pi `<number of throws>`
* ./pi `<number of throws>` `<threads>`