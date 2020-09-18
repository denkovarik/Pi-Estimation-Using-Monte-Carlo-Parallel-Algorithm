/**************************************************************************//**
* @file util.c
*
* @brief Source file for utility functions
*
******************************************************************************/
#include "util.h"


/**************************************************************************//**
* @author Dennis Kovarik
*
* @par Description:
* This function calculate the euclidean distance between a 2D point from the 
* origin. 
*
* @param[in] x - Double of the x value for the point.
* @param[in] y - Double of the y value for the point.
*
* @returns the distance between the point and the origin as a double.
******************************************************************************/
double calcDist(double x, double y)
{
    return sqrt(x*x + y*y);
}
