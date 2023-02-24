
/*****************************************************************************
 *
 *                     transformations.c
 * 
 *     Assignment: locality
 *     Authors:  Nora A-Rahim and Daniel Opara
 *     CS Logins: narahi01 and dopara01
 *     Date: February 21, 2023
 *
 *     This file contains the implementation for a program that performs 
 *     simple image transformations on pixmaps. 
 *     
 *
 *****************************************************************************/


#include <assert.h>
#include <string.h>
#include "transformations.h"
#include <stdio.h>
#include <string.h>

typedef A2Methods_UArray2 A2;
typedef A2Methods_mapfun Mapfun;

 /*************************** rotatecl{} ************************************
 * 
 *  Purpose: Stores relevant data relating to rotating an image, including the 
 *           dimensions of the original image, the size of image blocks, and 
 *           a 2D array object pointer.
 *           
 *  Members: 
 *              unsigned width = the number of columns in the two dimensional 
 *                               matrix representing the original pixmap prior 
 *                               to rotation 
 *              unsigned height = the number of rows in the two dimensional 
 *                               matrix representing the original pixmap prior 
 *                               to rotation 
 *              unsigned size = the number of bytes in one element of the two
 *                              dimensional array representing the original 
 *                              pixmap prior to rotation 
 *              unsigned blocksize = the number of cells one one side of a 
 *                                   single block in the two dimensional matrix 
 *                                   representing the original pixmap prior
 *                                   to rotation 
 *              A2 new_image = the two dimensional matrix representing the 
 *                             pixmap after being rotated 
 *              A2Methods_Object *(*at) = a function pointer to a method 
 *                                        that retrives an element in a two 
 *                                        dimensional array representing a 
 *                                        pixmap 
 *             
 *  Effects: Gives transformation function relevant information ahout original 
 *           image in order to perform rotations 
 * 
 **************************************************************************/

struct rotatecl {
        unsigned width;
        unsigned height;
        unsigned size;
        unsigned blocksize;       
        A2 new_image;        
        A2Methods_Object *(*at)(A2 array2, int i, int j); 
};

 /****************************** apply90() ************************************
 * 
 *  Purpose: Applies a 90-degree rotation to a single image pixel whose data is 
 *           represented as an element in a two dimensional matrix
 *  Parameters: 
 *              int col = the column of the two dimensional matrix where the 
 *                        pixel resides 
 *              int row = the row of the two dimensional matrix where the pixel 
 *                        resides 
 *              A2 original_image = the two dimensional matrix representing the 
 *                                  pixmap prior to being rotated 
 *              void *source_image = pointer to element of the two dimensional 
 *                                   matrix representing the pixmap prior to 
 *                                   being rotated 
 *              void *original_data = pointer to the struct rotatecl which 
 *                                    contains relevant data regarding the 
 *                                    matrix representing the pixmap prior 
 *                                    to being rotated
 *  Returns: None 
 *  Effects: used as a callback function in higher-level image processing 
 *           functions that apply a rotation to an entire image; called 
 *           repeatedly for each pixel in the original_image,
 *           effectively rotating the entire image by 90 degrees.
 * 
 **************************************************************************/
static void apply90(int col, int row, A2 original_image, void *source_image, 
                                                        void *original_data)
{
        /* not relevant */
        (void) original_image; 

        /* create a new closure that copies over the original image data */
        struct rotatecl *rotation_data = original_data;
       
        /* obtain the new, rotated image and it's size */
        A2 rotated_image = rotation_data->new_image;
        unsigned new_size = rotation_data->size;
        unsigned new_row = rotation_data->height - row - 1;

        /* use this information to get destination_image */
        A2 destination_image = rotation_data->at(rotated_image, new_row, col);
        
        /* copy data from source image into the desintation image */
        memcpy(destination_image, source_image, new_size); 
}       


 /******************************* apply180() *********************************
 * 
 *  Purpose: Applies a 180-degree rotation to a single image pixel whose data 
 *           is represented as an element in a two dimensional matrix 
 * 
 *  Parameters: int col = the column of the two dimensional matrix where the 
 *                        pixel resides 
 *              int row = the row of the two dimensional matrix where the pixel 
 *                        resides 
 *              A2 original_image = the two dimensional matrix representing the 
 *                                  pixmap prior to being rotated 
 *              void *source_image = pointer to element of the two dimensional 
 *                                   matrix representing the pixmap prior to 
 *                                   being rotated 
 *              void *original_data = pointer to the struct rotatecl which 
 *                                    contains relevant data regarding the 
 *                                    matrix representing the pixmap prior 
 *                                    to being rotated
 *  Returns: None
 *  Effects: used as a callback function in higher-level image processing 
 *           functions that apply a rotation to an entire image; called 
 *           repeatedly for each pixel in the original_image,
 *           effectively rotating the entire image by 180 degrees.
 * 
 **************************************************************************/
static void apply180(int col, int row, A2 original_image, void *source_image, 
                                                        void *original_data)
{
        (void) original_image; 

        /* create a new closure that copies over the original image data */
        struct rotatecl *rotation_data = original_data;
        
        /* obtain the new, rotated image and it's size */
        A2 rotated_image = rotation_data->new_image;
        unsigned new_size = rotation_data->size;
        unsigned new_col = rotation_data->width - col - 1;
        unsigned new_row = rotation_data->height - row - 1;
        
        /* use this information to get destination_image */
        A2 destination_image = rotation_data->at(rotated_image, new_col, 
                                                                new_row);
        
         /* copy data from source image into the desintation image */
        memcpy(destination_image, source_image, new_size);            
}


 /****************************** apply270() **********************************
 * 
 *  Purpose: Applies a 270-degree rotation to a single image pixel whose data is 
 *           represented as an element in a two dimensional matrix 
 *  Parameters: int col = the column of the two dimensional matrix where the 
 *                        pixel resides 
 *              int row = the row of the two dimensional matrix where the pixel 
 *                        resides 
 *              A2 original_image = the two dimensional matrix representing the 
 *                                  pixmap prior to being rotated 
 *              void *source_image = pointer to element of the two dimensional 
 *                                   matrix representing the pixmap prior to 
 *                                   being rotated 
 *              void *original_data = pointer to the struct rotatecl which 
 *                                    contains relevant data regarding the 
 *                                    matrix representing the pixmap prior 
 *                                    to being rotated
 *  Returns: None
 *  Effects: used as a callback function in higher-level image processing 
 *           functions that apply a rotation to an entire image; called 
 *           repeatedly for each pixel in the original_image,
 *           effectively rotating the entire image by 270 degrees.
 * 
 **************************************************************************/
static void apply270(int col, int row, A2 original_image, void *source_image, 
                                                        void *original_data)
{
        (void) original_image; 
        
        /* create a new closure that copies over the original image data */
        struct rotatecl *rotation_data = original_data;
       
        /* obtain the new, rotated image and it's size */
        A2 rotated_image = rotation_data->new_image;
        unsigned new_size = rotation_data->size;
        unsigned new_col = rotation_data->width - col - 1;

        /* use this information to get destination_image */
        A2 destination_image = rotation_data->at(rotated_image, row, new_col);

        /* copy data from source image into the desintation image */
        memcpy(destination_image, source_image, new_size);
}



 /************************** mirrorVertical() ********************************
 * 
 *  Purpose: Applies a vertical flip to a single image pixel whose data is 
 *           represented as an element in a two dimensional matrix 
 *  Parameters: int col = the column of the two dimensional matrix where the 
 *                        pixel resides 
 *              int row = the row of the two dimensional matrix where the pixel 
 *                        resides 
 *              A2 original_image = the two dimensional matrix representing the 
 *                                  pixmap prior to being mirrored 
 *              void *source_image = pointer to element of the two dimensional 
 *                                   matrix representing the pixmap prior to 
 *                                   being mirrored 
 *              void *original_data = pointer to the struct rotatecl which 
 *                                    contains relevant data regarding the 
 *                                    matrix representing the pixmap prior 
 *                                    to being mirrored
 *  Returns: None
 *  Effects: used as a callback function in higher-level image processing 
 *           functions that mirrors an entire image; called 
 *           repeatedly for each pixel in the original_image,
 *           effectively mirroring the image vertically
 * 
 **************************************************************************/
static void mirrorVertical(int col, int row, A2 original_image, 
                          void *source_image, void *original_data)
{
    (void) original_image;

    /* create a new closure that copies over the original image data */
    struct rotatecl *flip_data = original_data;

    /* obtain the new, flipped image and its size */
    A2 flipped_image = flip_data->new_image;
    unsigned new_size = flip_data->size;

    /* use the row index as the new row index, and flip the column index */
    unsigned new_row = flip_data->height - row - 1;
    unsigned new_col = col;

    /* use this information to get the destination image */
    A2 destination_image = flip_data->at(flipped_image, new_row, new_col);

    /* copy data from source image into the destination image */
    memcpy(destination_image, source_image, new_size);
}



/************************** mirrorHorizontal() ********************************
 * 
 *  Purpose: Applies a horizontal flip to a single image pixel whose data is 
 *           represented as an element in a two dimensional matrix 
 *  Parameters: int col = the column of the two dimensional matrix where the 
 *                        pixel resides 
 *              int row = the row of the two dimensional matrix where the pixel 
 *                        resides 
 *              A2 original_image = the two dimensional matrix representing the 
 *                                  pixmap prior to being mirrored 
 *              void *source_image = pointer to element of the two dimensional 
 *                                   matrix representing the pixmap prior to 
 *                                   being mirrored 
 *              void *original_data = pointer to the struct rotatecl which 
 *                                    contains relevant data regarding the 
 *                                    matrix representing the pixmap prior 
 *                                    to being mirrored
 *  Returns: None
 *  Effects: used as a callback function in higher-level image processing 
 *           functions that mirrors an entire image; called 
 *           repeatedly for each pixel in the original_image,
 *           effectively mirroring the image horizontally
 * 
 **************************************************************************/
static void mirrorHorizontal(int col, int row, A2 original_image, 
                              void *source_image, void *original_data)
{
    (void) original_image;

    /* create a new closure that copies over the original image data */
    struct rotatecl *mirror_data = original_data;

    /* obtain the new, horizontally mirrored image and its size */
    A2 mirrored_image = mirror_data->new_image;
    unsigned new_size = mirror_data->size;
    unsigned new_col = mirror_data->width - col - 1;

    /* use this information to get the destination image */
    A2 destination_image = mirror_data->at(mirrored_image, row, new_col);

    /* copy data from source image into the destination image  */
    memcpy(destination_image, source_image, new_size);
}



/************************** transpose() ***********************************
 * 
 *  Purpose: Applies a transpose transformation flip to a single image pixel 
 *              (swaps its row and column coordinates) whose data is 
 *              represented as an element in a two dimensional matrix 
 *  Parameters: int col = the column of the two dimensional matrix where the 
 *                        pixel resides 
 *              int row = the row of the two dimensional matrix where the pixel 
 *                        resides 
 *              A2 original_image = the two dimensional matrix representing the 
 *                                  pixmap prior to being mirrored 
 *              void *source_image = pointer to element of the two dimensional 
 *                                   matrix representing the pixmap prior to 
 *                                   being mirrored 
 *              void *original_data = pointer to the struct rotatecl which 
 *                                    contains relevant data regarding the 
 *                                    matrix representing the pixmap prior 
 *                                    to being mirrored
 *  Returns: None
 *  Effects: used as a callback function in higher-level image processing 
 *           functions that mirrors an entire image across the row-column 
 *           axis; called repeatedly for each pixel in the 
 *           original_image, effectively mirroring the image across what can
 *           be considered an x-y axis
 * 
 **************************************************************************/
static void transpose(int col, int row, A2 original_image, 
                      void *source_image, void *original_data)
{
    (void) original_image;

    /* create a new closure that copies over the original image data */
    struct rotatecl *transpose_data = original_data;

    /* obtain the new, transposed image and its size */
    A2 transposed_image = transpose_data->new_image;
    unsigned new_size = transpose_data->size;

    /* use the row index as the new column index, and vice versa */
    unsigned new_row = col;
    unsigned new_col = row;

    /* use this information to get the destination image */
    A2 destination_image = transpose_data->at(transposed_image, new_col, 
                                                                new_row);

    /* copy data from source image into the destination image */
    memcpy(destination_image, source_image, new_size);
}

 /************************** transform_image() ******************************
 * 
 *  Purpose: Transforms an image according to a specfied rotation function 
 *  Parameters: 
 *              A2 original_image = An A2 object containing a two dimensional 
 *                                  matrix representing a pixmap prior to 
 *                                  being rotated 
 *              A2Methods_applyfun apply_rotation = A function pointer that 
 *                                                 specifies the rotation 
 *                                                 function to be applied to 
 *                                                 each pixel in the image
 *              A2Methods_T method_suite = a pointer to the method suite 
 *                                         containing a record of function 
 *                                         pointers for two implementations
 *                                         of 2D arrays  
 *              Mapfun map = A pointer to a default mapping function 
 *              A2 original_image = An A2 object containing a two dimensional 
 *                                  matrix representing a pixmap prior to 
 *                                  being rotated 
 *  Returns: The new A2 object that contains the transformed image data. 
 *  Effects: 
 * 
 **************************************************************************/
static A2 transform_image(A2 original_image, A2Methods_applyfun apply_rotation,
                                        A2Methods_T method_suite,  Mapfun map)
{
        /* store relevant information about the original image */
        int width = method_suite->width(original_image);
        int height = method_suite->height(original_image);
        int size = method_suite->size(original_image);
        int blocksize = method_suite->blocksize(original_image);


        /* make a new_image A2 object */
        /* this only works for 90 degree rotations as of now */
        A2 new_image;
        if (apply_rotation != apply180) {
                new_image = method_suite->new_with_blocksize(height, width,
                                                        size, blocksize);
        } else {
                new_image = method_suite->new_with_blocksize(width, height,
                                                        size, blocksize);
        }

        /* obtain original image data */
        struct rotatecl original_data = {width, height, size, blocksize, 
                                                new_image, method_suite->at};


        /* map through original image and apply rotation */
        map(original_image, apply_rotation, &original_data);
        
        return new_image;
}

 /******************************** rotate90() ********************************
 * 
 *  Purpose: Applies a uniform 90 degree rotation to every element in a two 
 *           dimensional array representing a pixmap 
 *  Parameters: 
 *              A2Methods_T method_suite = a pointer to the method suite 
 *                                         containing a record of function 
 *                                         pointers for two implementations
 *                                         of 2D arrays  
 *              Mapfun map = A pointer to a default mapping function 
 *              A2 original_image = An A2 object containing a two dimensional 
 *                                  matrix representing a pixmap prior to 
 *                                  being rotated 
 *  Returns: An A2 object representing a pixmap succesfully rotated by 
 *           90 degrees
 *  Effects: Makes use of a callback functions to perform image rotation 
 * 
 **************************************************************************/
A2 rotate90(A2Methods_T method_suite, Mapfun map, A2 original_image)
{
        return transform_image(original_image, apply90, method_suite, map);
}


 /****************************** rotate180() ********************************
 * 
 *  Purpose: Applies a uniform 180 degree rotation to every element in a two 
 *           dimensional array representing a pixmap 
 *  Parameters: A2Methods_T method_suite = a pointer to the method suite 
 *                                         containing a record of function 
 *                                         pointers for two implementations
 *                                         of 2D arrays  
 *              Mapfun map = A pointer to a default mapping function 
 *              A2 original_image = An A2 object containing a two dimensional 
 *                                  matrix representing a pixmap prior to 
 *                                  being rotated 
 *  Returns: An A2 object representing an image succesfully rotated by 
 *           180 degrees
 *  Effects: Makes use of a callback functions to perform image rotation 
 * 
 **************************************************************************/
A2 rotate180(A2Methods_T method_suite, Mapfun map, A2 original_image)
{
        return transform_image(original_image, apply180, method_suite, map);
}

 /****************************** rotate270() **********************************
 * 
 *  Purpose: Applies a uniform 270 degree rotation to every element in a two 
 *           dimensional array representing a pixmap 
 *  Parameters: A2Methods_T method_suite = a pointer to the method suite 
 *                                         containing a record of function 
 *                                         pointers for two implementations
 *                                         of 2D arrays  
 *              Mapfun map = A pointer to a default mapping function 
 *              A2 original_image = An A2 object containing a two dimensional 
 *                                  matrix representing a pixmap prior to 
 *                                  being rotated 
 *  Returns: An A2 object representing an image succesfully rotated by 
 *           270 degrees
 *  Effects: Makes use of a callback functions to perform image rotation 
 * 
 ****************************************************************************/
A2 rotate270(A2Methods_T method_suite, Mapfun map, A2 original_image)
{
        return transform_image(original_image, apply270, method_suite, map);
}

 /************************** flipVertical() *******************************
 * 
 *  Purpose: Applies a uniform vertical mirroring to every element in a two 
             dimensional array representing a pixmap 
 *  Parameters: A2Methods_T method_suite = a pointer to the method suite 
 *                                         containing a record of function 
 *                                         pointers for two implementations
 *                                         of 2D arrays  
 *              Mapfun map = A pointer to a default mapping function 
 *              A2 original_image = An A2 object containing a two dimensional 
 *                                  matrix representing a pixmap prior to 
 *                                  being mirrored 
 *  Returns: An A2 object representing an image succesfully vertically mirrored
 *  Effects: Makes use of a callback functions to perform image mirroring 
 * 
 ****************************************************************************/
A2 flipVertical(A2Methods_T method_suite, Mapfun map, A2 original_image)
{
        return transform_image(original_image, mirrorVertical, method_suite, 
        map);
}

 /************************** flipHorizontal() *******************************
 * 
 *  Purpose: Applies a uniform horizontal mirroring to every element in a two 
             dimensional array representing a pixmap 
 *  Parameters: A2Methods_T method_suite = a pointer to the method suite 
 *                                         containing a record of function 
 *                                         pointers for two implementations
 *                                         of 2D arrays  
 *              Mapfun map = A pointer to a default mapping function 
 *              A2 original_image = An A2 object containing a two dimensional 
 *                                  matrix representing a pixmap prior to 
 *                                  being mirrored 
 *  Returns: An A2 object representing an image succesfully horizontally 
             mirrored
 *  Effects: Makes use of a callback functions to perform image mirroring 
 * 
 ****************************************************************************/
A2 flipHorizontal(A2Methods_T method_suite, Mapfun map, A2 original_image)
{
        return transform_image(original_image, mirrorHorizontal, method_suite, 
        map);
}


 /************************** transposeMatrix() *******************************
 * 
 *  Purpose: Applies a uniform transpose transformation to every element in a 
             two dimensional array representing a pixmap 
 *  Parameters: A2Methods_T method_suite = a pointer to the method suite 
 *                                         containing a record of function 
 *                                         pointers for two implementations
 *                                         of 2D arrays  
 *              Mapfun map = A pointer to a default mapping function 
 *              A2 original_image = An A2 object containing a two dimensional 
 *                                  matrix representing a pixmap prior to 
 *                                  being mirrored 
 *  Returns: An A2 object representing an image succesfully transposed 
 *  Effects: Makes use of a callback functions to perform image transposing 
 * 
 ****************************************************************************/
A2 transposeMatrix(A2Methods_T method_suite, Mapfun map, A2 original_image)
{
        return transform_image(original_image, transpose, method_suite, map);
}