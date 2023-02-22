#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <except.h>

#include "assert.h"
#include "a2methods.h"
#include "a2plain.h"
#include "a2blocked.h"
#include "pnm.h"
#include "transformations.h"

void performRotation(A2Methods_UArray2 rotated_image, A2Methods_UArray2 orig_image, A2Methods_T methods, A2Methods_mapfun *map, int rotation);

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
        int   i;    
        
        
        /* default to UArray2 methods */
        A2Methods_T methods = uarray2_methods_plain; 
        assert(methods);

        /* default to best map */
        /* sets mapping function pointer to be whats in the default so that 
        if you call map it will use row-major mapping (or whatever you set to 
        in the default field)*/
        A2Methods_mapfun *map = methods->map_default; 
        assert(map); // assert that map is not null 


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
        FILE *outfp;
        outfp = fopen("rotflow.ppm", "w"); 
        if(i < argc){
                fp = fopen(argv[i], "r"); 
                assert(fp != NULL);
                ppm = Pnm_ppmread(fp, methods);
                fclose(fp);   
        } else {
                ppm = Pnm_ppmread(stdin, methods);
        }
        A2Methods_UArray2 orig_image = ppm->pixels; 
        A2Methods_UArray2 rotated_image = NULL;
        performRotation(rotated_image, orig_image, methods, map, rotation);

        Pnm_ppmwrite(outfp, ppm);

        (void) orig_image;
        
        Pnm_ppmfree(&ppm);
      //  assert(false);    // the rest of this function is not yet implemented
}

void performRotation(A2Methods_UArray2 rotated_image, A2Methods_UArray2 orig_image, A2Methods_T methods, A2Methods_mapfun *map, int rotation)
{
        if(rotation == 90) {
                rotated_image = rotate90(methods, map, orig_image);
        }       
        (void) rotated_image;
}
