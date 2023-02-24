
/**************************************************************************
 *
 *                     ppmtrans.c
 * 
 *     Assignment: locality
 *     Authors:  Nora A-Rahim and Daniel Opara
 *     CS Logins: narahi01 and dopara01
 *     Date:     February 21, 2023
 *
 *     This file contains the implementation for a program that performs 
 *     simple image transformations on pixmaps. 
 *     
 *
 **************************************************************************/



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "a2methods.h"
#include "a2plain.h"
#include "a2blocked.h"
#include "cputiming.h"
#include "pnm.h"
#include "transformations.h"

typedef A2Methods_UArray2 A2;

void performRotation(A2Methods_UArray2 original_image, 
                      A2Methods_T methods, 
                      A2Methods_mapfun *map, Pnm_ppm ppm, int rotation, 
                      A2Methods_UArray2 *p_rotated_image);


A2 timeData(A2Methods_UArray2 original_image, A2Methods_T methods, 
                                        A2Methods_mapfun *map, int rotation, 
                                        Pnm_ppm ppm, char *timing_filename);


 /* decides which mapping and methods to use */
#define SET_METHODS(METHODS, MAP, WHAT) do {                    \
        methods = (METHODS);                                    \
        assert(methods != NULL);                                \
        map = methods->MAP;                                     \
        if (map == NULL) {                                      \
                fprintf(stderr, "%s does not support "          \
                                WHAT "mapping\n",               \
                                argv[0]);                       \
                exit(1);                                        \
        }                                                       \
} while (false)

static void
usage(const char *progname)
{
        fprintf(stderr, "Usage: %s [-rotate <angle>] "
                        "[-{row,col,block}-major] [filename]\n",
                        progname);
        exit(1);
}

int main(int argc, char *argv[]) 
{
        char *time_file_name = NULL;
        (void) time_file_name;
        int   rotation       = 0;
        char *transformation;
        char *transposing;
        int   i;   
        
        /* default to UArray2 methods */
        A2Methods_T methods = uarray2_methods_plain; 
        assert(methods);

        /* default to best map */
        A2Methods_mapfun *map = methods->map_default; 
        assert(map);

        for (i = 1; i < argc; i++) {
                if (strcmp(argv[i], "-row-major") == 0) {
                        SET_METHODS(uarray2_methods_plain, map_row_major, 
                                    "row-major");
                } else if (strcmp(argv[i], "-col-major") == 0) {
                        SET_METHODS(uarray2_methods_plain, map_col_major, 
                                    "column-major");
                } else if (strcmp(argv[i], "-block-major") == 0) {
                        SET_METHODS(uarray2_methods_blocked, map_block_major,
                                    "block-major");
                } else if (strcmp(argv[i], "-rotate") == 0) {
                        if (!(i + 1 < argc)) {      /* no rotate value */
                                usage(argv[0]);
                        }
                        char *endptr;
                        rotation = strtol(argv[++i], &endptr, 10);
                        if (!(rotation == 0 || rotation == 90 ||
                            rotation == 180 || rotation == 270)) {
                                fprintf(stderr, 
                                        "Rotation must be 0, 90 180 or 270\n");
                                usage(argv[0]);
                        }
                        if (!(*endptr == '\0')) {    /* Not a number */
                                usage(argv[0]);
                        }
                } else if (strcmp(argv[i], "-flip") == 0) {
                        if (!(i + 1 < argc)) {
                                usage(argv[0]);
                        }
                        transformation = argv[++i];
                        if (!strcmp(transformation, "horizontal")) {
                                rotation = 1;
                        } else if (!strcmp(transformation, "vertical")){
                                rotation = 2;
                        } else { 
                                usage(argv[0]);
                        }
                } else if (strcmp(argv[i], "-transpose") == 0) {
                        if (!(i + 1 < argc)) {
                                usage(argv[0]);
                        }
                        transposing = argv[++i];
                        if (!strcmp(transformation, "transpose")) {
                                rotation = 3;
                        } else { 
                                usage(argv[0]);
                        }
                } else if (strcmp(argv[i], "-time") == 0) {
                        time_file_name = argv[++i];
                } else if (*argv[i] == '-') {
                        fprintf(stderr, "%s: unknown option '%s'\n", argv[0],
                                argv[i]);
                        usage(argv[0]);
                } else if (argc - i > 1) {
                        fprintf(stderr, "Too many arguments\n");
                        usage(argv[0]);
                } else {
                        break;
                }
        }

        Pnm_ppm ppm;
        FILE *fp;

        if (i < argc){
                fp = fopen(argv[i], "r"); 
                assert(fp);
                ppm = Pnm_ppmread(fp, methods);
                fclose(fp);   
        } else {
                ppm = Pnm_ppmread(stdin, methods);
        }

        A2Methods_UArray2 original_image = ppm->pixels; 
        A2Methods_UArray2 rotated_image = NULL;
       
        
        rotated_image = timeData(original_image, methods, map, rotation, ppm, 
                                                        time_file_name);

        assert(rotated_image != NULL);

        /* get new rotated image data */
        ppm->width = methods->width(rotated_image);
        ppm->height = methods->height(rotated_image);
        ppm->pixels = rotated_image;

        Pnm_ppmwrite(stdout, ppm);

        Pnm_ppmfree(&ppm);
        
}


 /**************************** performRotation() ****************************
 * 
 *  Purpose: Calls the proper method of rotation corresponding to the degree
 *              of rotation requested by the user
 *  Parameters: 
 *              A2Methods_UArray2 original_image = an A2Methods_UArray2 object,
 *                                      specifically, the two dimensional array
 *                                      that contains the original image given
 *                                      to the program matrix
 *              A2Methods_T *methods = a pointer to the method suite 
 *                                         containing function pointers 
 *                                         for two implementations
 *                                         of 2D arrays  
 *              A2Methods_mapfun *map = a pointer to a default mapping function
 *              Pnm_ppm ppm = the Pnm_ppm object of the original image
 *              int rotation = the degree to which an image will be rotated
 *            
 *              char *timing_filename = a pointer to the filename that
 *                                      that will contain the timing data
 *  Returns: None
 *  Effects: The Pnm_ppm object is passed soley for freeing its pixels if a
 *           rotation is performed
 * 
 ****************************************************************************/
void performRotation(A2Methods_UArray2 original_image, 
                      A2Methods_T methods, 
                      A2Methods_mapfun *map, Pnm_ppm ppm, int rotation, 
                      A2Methods_UArray2 *p_rotated_image)
{
        if (rotation == 90) {
                *p_rotated_image = rotate90(methods, map, original_image);
        } else if (rotation == 180) {
                *p_rotated_image = rotate180(methods, map, original_image);
        } else if (rotation == 270) {
                *p_rotated_image = rotate270(methods, map, original_image);
        } else if (rotation == 0) {
                *p_rotated_image = original_image;
        } else if (rotation == 1) {
                *p_rotated_image = flipHorizontal(methods, map, original_image);
        } else if (rotation == 2) { 
                *p_rotated_image = flipVertical(methods, map, original_image);
        } else if (rotation == 3) { 
                *p_rotated_image = transposeMatrix(methods, map, original_image);
        } else {
                methods->free(&ppm->pixels);
                Pnm_ppmfree(&ppm);
                exit(1);
        }
}

/**************************** timeData() *************************************
 * 
 *  Purpose: Generates timing data for image rotations if given a client's 
 *           request for it 
 * 
 *  Parameters: 
 *              A2Methods_UArray2 original_image = an A2Methods_UArray2 object,
 *                                      specifically, the two dimensional array
 *                                      that contains the original image given
 *                                      to the program matrix
 *              A2Methods_T *methods = a pointer to the method suite 
 *                                         containing function pointers 
 *                                         for two implementations
 *                                         of 2D arrays  
 *              A2Methods_mapfun *map = a pointer to a default mapping function
 *              Pnm_ppm ppm = the Pnm_ppm object of the original image
 *              int rotation = the degree to which an image will be rotated
 *            
 *              char *timing_filename = a pointer to the filename that
 *                                      that will contain the timing data
 *  Returns: An A2 object representing an image succesfully rotated 
 *           by a specified number of degrees
 *  Effects: The Pnm_ppm object is passed soley for freeing its pixels if a
 *           rotation is performed
 * 
 ****************************************************************************/
A2 timeData(A2Methods_UArray2 original_image, A2Methods_T methods, 
                                        A2Methods_mapfun *map, int rotation,
                                        Pnm_ppm ppm, char *timing_filename)
{
        double time_used; 
        FILE *timefp;
        A2Methods_UArray2 rotated_image;
        
        if (timing_filename != NULL) {
                CPUTime_T timer;
                timer = CPUTime_New();
                CPUTime_Start(timer);
                performRotation(original_image, methods, map, ppm, rotation,
                                                        &rotated_image);
                assert(rotated_image != NULL);
                time_used = CPUTime_Stop(timer);

                timefp = fopen(timing_filename, "w");
                fprintf(timefp, "%lf\n", time_used);
                fclose(timefp);
                methods->free(&ppm->pixels);
                CPUTime_Free(&timer);
        } else {
                performRotation(original_image, methods, map, ppm, rotation, 
                                                        &rotated_image);
                methods->free(&ppm->pixels);
        }

        return rotated_image;
}
