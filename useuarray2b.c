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

// void
// check_and_print(int i, int j, UArray2_T a, void *p1, void *p2) 
// {
//         number *entry_p = p1;

//         *((bool *)p2) &= UArray2_at(a, i, j) == entry_p;

//         if ( (i == (DIM1 - 1) ) && (j == (DIM2 - 1) ) ) {
//                 /* we got the corner */
//                 *((bool *)p2) &= (*entry_p == MARKER);
//         }

//         printf("ar[%d,%d]\n", i, j);
// }
int
main(int argc, char *argv[])
{
        (void)argc;
        (void)argv;

        UArray2b_T test_array;
        bool OK = true;

        test_array = UArray2b_new(DIM1, DIM2, ELEMENT_SIZE, BLOCK_SIZE);

        OK = (UArray2b_width(test_array) == DIM1) &&
             (UArray2b_height(test_array) == DIM2) &&
             (UArray2b_size(test_array) == ELEMENT_SIZE);


        /* Note: we are only setting a value on the corner of the array */
        void *val = UArray2b_at(test_array, 3, 0);
        (void) val;




        // printf("Trying column major\n");
        // UArray2_map_col_major(test_array, check_and_print, &OK);

        // printf("Trying row major\n");
        // UArray2_map_row_major(test_array, check_and_print, &OK);


        UArray2b_free(&test_array);
        printf("The array is %sOK!\n", (OK ? "" : "NOT "));

}
