/*****************************************************************
 *                      
 *                      uarray2b.c
 * 
 *      Assignment: CS40 Project 3 - locality
 *      Authors: Nora A-Rahim and Daniel Opara 
 *      CS Logins: narahi01, dopara01
 *      Date:   2/16/2023
 *  
 *      Implementation for uarray2b.h. 
 * 
*****************************************************************/


#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h>
#include "uarray2b.h"
#include "uarray2.h" 
#include <uarray.h>
#define T UArray2b_T

const int MAX_BYTES = 65536;
struct T {
        int height, width;
        unsigned size;
        unsigned blocksize;
        UArray2_T blocks;
};

T UArray2b_new(int width, int height, int size, int blocksize)
{
        T array2b = malloc(sizeof(struct T));
        assert(array2b != NULL);
        assert(blocksize >= 1);
        
        int block_cols = (width  + blocksize - 1) / blocksize;
        int block_rows = (height + blocksize - 1) / blocksize;

        array2b->width = width;
        array2b->height = height;
        array2b->size = size;
        array2b->blocksize = blocksize;
        array2b->blocks = UArray2_new(block_cols, block_rows, sizeof(UArray_T));

        assert(array2b->blocks != NULL);

        for (int col = 0; col < block_cols; col++) {
                for (int row = 0; row < block_rows; row++) {
                        printf("in loop: at [%d, %d]\n", row, col);
                        UArray_T *block = UArray2_at(array2b->blocks, col, row);
                        assert(block != NULL);
                        *block = UArray_new(blocksize * blocksize, size);
                }
        }

        return array2b;
}


// T UArray2b_new_64K_block(int width, int height, int size)
// {
//         T array2b = malloc(sizeof(struct T));
//         assert(array2b != NULL);
        

//         array2b->width = width;
//         array2b->height = height;
//         array2b->size = size;
//         array2b->blocksize = blocksize;
//         array2b->blocks = UArray2_new(block_cols, block_rows, sizeof(UArray_T));

//         int block_cols = (width  + array2b->blocksize - 1) / blocksize;
//         int block_rows = (height + array2b->blocksize - 1) / blocksize;

//         for (int col = 0; col < block_cols; col++) {
//                 for (int row = 0; row < block_rows; row++) {
//                         UArray_T *block_cells = UArray2_at(array2b->blocks, row, col);
//                         *block_cells = UArray_new(blocksize * blocksize, size);
//                 }
//         }
//         return array2b;
// }

void UArray2b_free(T *array2b)
{
        int block_cols = 
        ((*array2b)->width + (*array2b)->blocksize - 1) / (*array2b)->blocksize;
        int block_rows = 
        ((*array2b)->height + (*array2b)->blocksize - 1) / (*array2b)->blocksize;

        /* free the UArray in each block */
        for (int col = 0; col < block_cols; col++) {
                for (int row = 0; row < block_rows; row++) {
                        UArray_T *free_me = UArray2_at((*array2b)->blocks, row, col);
                        assert(*free_me != NULL && free_me != NULL);
                        UArray_free(free_me);
                }
        }
        
        /* free the UArray2 and the struct itself, respectively */
        UArray2_free(&((*array2b)->blocks));
        free(*array2b);
        
}

void *UArray2b_at(T array2b, int column, int row)
{
        assert(array2b != NULL);
        assert(column >= 0 && row >= 0);
        assert(column < array2b->width && row < array2b->height);

        /* Finds the block at index block_col, block_row */
        int block_col = (column / array2b->blocksize);
        int block_row = (row / array2b->blocksize);
        printf("block_col: %d\n", block_col);
        printf("block_row: %d\n", block_row);

        /* Finds the UArray at that block */
        UArray_T *block_cells =  UArray2_at(array2b->blocks, block_col, block_row);
        assert(block_cells != NULL);


        int cell_idx = (array2b->blocksize * (row % array2b->blocksize) +
                                              (column % array2b->blocksize));

        /* Finds the element in that UArray */
        printf("cell index: %d\n", cell_idx);
        void *data = UArray_at(*block_cells, cell_idx);
   
        return data; 
}

int UArray2b_width(T array2b)
{
        return array2b->width;
}

int UArray2b_height(T array2b)
{
        return array2b->height;
}
int UArray2b_size(T array2b)
{
        return array2b->size;
}
int UArray2b_blocksize(T array2b)
{
        return array2b->blocksize;
}
