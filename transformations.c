
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
 *  Purpose: Applies a 180-degree rotation to a single image pixel whose data is 
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
 *  Returns: 
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



