


static void mirrorVertical(int col, int row, A2 original_image, 
                          void *source_image, void *original_data)
{
    /* not relevant */
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

    /* copy data from source image into the destination image in reverse order */
    memcpy(destination_image, source_image, new_size);
}


static void mirrorHorizontal(int col, int row, A2 original_image, 
                              void *source_image, void *original_data)
{
    /* not relevant */
    (void) original_image;

    /* create a new closure that copies over the original image data */
    struct rotatecl *mirror_data = original_data;

    /* obtain the new, horizontally mirrored image and its size */
    A2 mirrored_image = mirror_data->new_image;
    unsigned new_size = mirror_data->size;
    unsigned new_col = mirror_data->width - col - 1;

    /* use this information to get the destination image */
    A2 destination_image = mirror_data->at(mirrored_image, row, new_col);

    /* copy data from source image into the destination image in reverse order */
    memcpy(destination_image, source_image, new_size);
}

static void transpose(int col, int row, A2 original_image, 
                       void *source_image, void *original_data)
{
    /* not relevant */
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
    A2 destination_image = transpose_data->at(transposed_image, new_row, new_col);

    /* copy data from source image into the destination image */
    memcpy(destination_image, source_image, new_size);
}
