/**************************************************************
 *
 *                     transformations.h
 * 
 *     Assignment: locality
 *     Authors:  Nora A-Rahim and Daniel Opara
 *     CS Logins: narahi01 and dopara01
 *     Date: February 21, 2023
 *
 *     This file contains the interface for a program that performs 
 *     simple image transformations on pixmaps. 
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

A2 rotate270(A2Methods_T method_suite, Mapfun map, A2 orig_image);

A2 flipVertical(A2Methods_T method_suite, Mapfun map, A2 original_image);

A2 flipHorizontal(A2Methods_T method_suite, Mapfun map, A2 original_image);

A2 transposeMatrix(A2Methods_T method_suite, Mapfun map, A2 original_image);


#undef A2 
#undef Mapfun

#endif