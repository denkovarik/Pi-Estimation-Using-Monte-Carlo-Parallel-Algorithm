#include "utilities.h"


/**************************************************************************//**
* @author Dennis Kovarik
*
* @par Description:
* This function checks that the function calcDist is correctly calculating the 
* euclidean distance between a point and the origin.
*
* @returns 1 if the test passed
* @returns 0 otherwise
******************************************************************************/
int checkCalcDis()
{
    double x, y;
    double expectedAnswer = 0.0;
    double theAnswer = 0.0;

    // Origin is considered to be point (0,0)
    // Case 1: point (0,0) from origin expect calcDis = 0.0
    x = 0.0;
    y = 0.0;
    expectedAnswer = 0.0;
    theAnswer = calcDist(x,y);

    if(fabs(theAnswer - expectedAnswer) > 0.000001)
    {
        printf("Distance from (0,0) to (%f, %f) should be %f but is instead %f\n",
            x, y, expectedAnswer, theAnswer);
   
        return 0;
    }

    // Case 2: point (1,0) from origin expect calcDis = 1.0
    x = 1.0;
    y = 0.0;
    expectedAnswer = 1.0;
    theAnswer = calcDist(x,y);

    if(fabs(theAnswer - expectedAnswer) > 0.000001)
    {
        printf("Distance from (0,0) to (%f, %f) should be %f but is instead %f\n",
            x, y, expectedAnswer, theAnswer);
   
        return 0;
    }

    // Case 3:point (0,1) from origin expect calcDis = 1.0
    x = 0.0;
    y = 1.0;
    expectedAnswer = 1.0;
    theAnswer = calcDist(x,y);

    if(fabs(theAnswer - expectedAnswer) > 0.000001)
    {
        printf("Distance from (0,0) to (%f, %f) should be %f but is instead %f\n",
            x, y, expectedAnswer, theAnswer);
   
        return 0;
    }

    // Case 4: point (1,1) from origin expect calcDis = 0.0
    x = 1.0;
    y = 1.0;
    expectedAnswer = 1.414214;
    theAnswer = calcDist(x,y);

    if(fabs(theAnswer - expectedAnswer) > 0.000001)
    {
        printf("Distance from (0,0) to (%f, %f) should be %f but is instead %f\n",
            x, y, expectedAnswer, theAnswer);
   
        return 0;
    }

    // Case 5: point (0.54,0.335) from origin expect calcDis = 0.0
    x = 0.54;
    y = 0.335;
    expectedAnswer = 0.635472;
    theAnswer = calcDist(x,y);

    if(fabs(theAnswer - expectedAnswer) > 0.000001)
    {
        printf("Distance from (0,0) to (%f, %f) should be %f but is instead %f\n",
            x, y, expectedAnswer, theAnswer);
   
        return 0;
    }

    return 1;
}


int main()
{
    int allTestsPassed = 1;
    srandom(omp_get_thread_num());

    if(checkCalcDis() == 0)
    {
        allTestsPassed = 0;
        printf("Problem with function calcDist\n");
    }

    if(allTestsPassed == 1)
    {
        printf("All Tests Passed :)\n");
    }
    
    return 0;
}
