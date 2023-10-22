#ifndef IMAGE_H
#define IMAGE_H

typedef struct Image
{
    int rows;
    int cols;
    char type[3]; // "P2" for grayscale, "P3" for color
    unsigned char **pixels;
} Image;

Image *create(int rows, int cols, char type[]);
Image *load_from_ppm(const char *filename);
void write_to_ppm(Image *image, const char *filename);
void rgb_to_gray(Image *image_rgb, Image *image_gray);
void free_image(Image *image);

#endif
