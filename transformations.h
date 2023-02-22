/**************************************************************
 *
 *                     transformations.h
 * 
 *     Assignment: transformations
 *     Authors:  Nora A-Rahim and Daniel Opara
 *     CS Logins: narahi01 and dopara01
 *     Date:     February 21, 2023
 *
 *   
 *     
 *
 **************************************************************/
#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include <assert.h>
#include <string.h>
#include "a2methods.h"


#define A2 A2Methods_UArray2
#define Mapfun A2Methods_mapfun

A2 rotate90(A2Methods_T method_suite, Mapfun map, A2 orig_image);

A2 rotate180(A2Methods_T method_suite, Mapfun map, A2 orig_image);

#undef A2 
#undef Mapfun

#endif