/*
 *                     
 *                       useuarray2b.c
 *
 *       
 */
 

#include <stdio.h> 
#include <stdlib.h> 
#include <stdbool.h> 
#include <assert.h>
#include "uarray2b.h"
#include "uarray2.h" 
#include <uarray.h>


typedef long number;

const int DIM1 = 5;
const int DIM2 = 5;
const int ELEMENT_SIZE = 4;
const int BLOCK_SIZE = 3;
const int MARKER = 99;

void
check_and_print(int i, int j, UArray2b_T a, void *p1, void *p2) 
{
        number *entry_p = p1;

        *((bool *)p2) &= UArray2b_at(a, i, j) == entry_p;

        if ( (i == (DIM1 - 1) ) && (j == (DIM2 - 1) ) ) {
                /* we got the corner */
                *((bool *)p2) &= (*entry_p == MARKER);
        }

        printf("in block: [%d,%d]\n", i, j);
}
int
main(int argc, char *argv[])
{
        (void)argc;
        (void)argv;

        //UArray2b_T test_array;
        bool OK = true;

//         test_array = UArray2b_new(DIM1, DIM2, ELEMENT_SIZE, BLOCK_SIZE);

//         OK = (UArray2b_width(test_array) == DIM1) &&
//          (UArray2b_height(test_array) == DIM2) &&
//          (UArray2b_size(test_array) == ELEMENT_SIZE) &&
//          (UArray2b_blocksize(test_array) == BLOCK_SIZE);


//         /* Note: we are only setting a value on the corner of the array */
//         // void *val = UArray2b_at(test_array, 3, 0);
//         // (void) val;

//        printf("----MAPPING NORMAL -----\n");
//        UArray2b_map(test_array, check_and_print, &OK);

       UArray2b_T test_64_array = UArray2b_new_64K_block(DIM1, DIM2, 4);
       
        OK = (UArray2b_width(test_64_array) == DIM1) &&
             (UArray2b_height(test_64_array) == DIM2) &&
             (UArray2b_size(test_64_array) == ELEMENT_SIZE) &&
             (UArray2b_blocksize(test_64_array) == BLOCK_SIZE);

          printf("----MAPPING 64 K -----\n");
//        UArray2b_map(test_64_array, check_and_print, &OK);

       //UArray2b_free(&test_array);
       UArray2b_free(&test_64_array);
       printf("The array is %sOK!\n", (OK ? "" : "NOT "));

}
