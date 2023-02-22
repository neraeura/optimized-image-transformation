
/**************************************************************
 *
 *                     transformations.c
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


#include <assert.h>
#include <string.h>
#include "transformations.h"
#include <stdio.h>
#include <string.h>

typedef A2Methods_UArray2 A2;
typedef A2Methods_mapfun Mapfun;

struct rotatecl {
        unsigned width;
        unsigned height;
        unsigned size;
        unsigned blocksize;       
        A2 new_image;        
        A2Methods_Object *(*at)(A2 array2, int i, int j); 
        // change to just methods? 
};

 /********** transform_image() ********
 * 
 *  Purpose: 
 *  Parameters: 
 *  Returns: 
 *  Effects: 
 * 
 **************************/
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
        A2 new_image = method_suite->new_with_blocksize(height, width, 
                                                           size, blocksize);


        /* obtain original image data */
        struct rotatecl original_data = {width, height, size, blocksize, 
                                                new_image, method_suite->at};


        /* map through original image and apply rotation */
        map(original_image, apply_rotation, &original_data);
        return new_image;
}


 /********** apply90() ********
 * 
 *  Purpose: 
 *  Parameters: 
 *  Returns: 
 *  Effects: 
 * 
 **************************/
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


 /********** apply180() ********
 * 
 *  Purpose: 
 *  Parameters: 
 *  Returns: 
 *  Effects: 
 * 
 **************************/
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


 /********** rotate90() ********
 * 
 *  Purpose: 
 *  Parameters: 
 *  Returns: 
 *  Effects: 
 * 
 **************************/
A2 rotate90(A2Methods_T method_suite, Mapfun map, A2 orig_image)
{
        return transform_image(orig_image, apply90, method_suite, map);
}


 /********** rotate180() ********
 * 
 *  Purpose: 
 *  Parameters: 
 *  Returns: 
 *  Effects: 
 * 
 **************************/
A2 rotate180(A2Methods_T method_suite, Mapfun map, A2 orig_image)
{
        return transform_image(orig_image, apply180, method_suite, map);
}

































// A2 rotate270(A2Methods_T method_suite, A2 apply_rotation, Mapfun map)
// {
//         return transform(method_suite, apply270, map, apply_rotation);
// }
// static void apply270(int col, int row, A2 original_image, void *elem, 
//                                                         void *rotation_data)
// {
//         (void) original_image; 
//         struct rotatecl *r = rotation_data;
//         A2 rotated_image = r->new_image;
//         unsigned new_size = r->size;
        
//         memcpy(r->at(r->new_image, r->width - col - 1, r->height - row - 1),
//                                                              elem, new_size);
                
// }
