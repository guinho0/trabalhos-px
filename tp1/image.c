#include "image.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PPM_MAGIC "P3"
#define PPM_MAX_VALUE 255

typedef struct image
{
    int rows;
    int cols;
    char type[3];
    unsigned char *data;
} Image;

Image *create(int rows, int cols, char type[])
{
    Image *image = malloc(sizeof(Image));
    if (image == NULL)
    {
        return NULL;
    }

    image->rows = rows;
    image->cols = cols;
    strcpy(image->type, type);

    if (strcmp(type, "P2") == 0)
    {
        image->data = malloc(rows * cols * sizeof(unsigned char));
    }
    else if (strcmp(type, "P3") == 0)
    {
        image->data = malloc(rows * cols * 3 * sizeof(unsigned char));
    }
    else
    {
        return NULL;
    }

    return image;
}

Image *load_from_ppm(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        return NULL;
    }

    // Lê o cabeçalho do arquivo

    char magic[3];
    fscanf(file, "%s\n", magic);
    if (strcmp(magic, PPM_MAGIC) != 0)
    {
        fclose(file);
        return NULL;
    }

    int rows, cols;
    fscanf(file, "%d %d\n", &rows, &cols);
    char type[3];
    fscanf(file, "%s\n", type);

    // Aloca memória para a imagem

    Image *image = create(rows, cols, type);
    if (image == NULL)
    {
        fclose(file);
        return NULL;
    }

    // Lê os pixels da imagem

    unsigned char *data = image->data;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (strcmp(type, "P2") == 0)
            {
                fscanf(file, "%c ", &data[i * cols + j]);
            }
            else if (strcmp(type, "P3") == 0)
            {
                fscanf(file, "%c %c %c ", &data[i * cols * 3 + j * 3],
                       &data[i * cols * 3 + j * 3 + 1],
                       &data[i * cols * 3 + j * 3 + 2]);
            }
        }
    }

    fclose(file);

    return image;
}

void write_to_ppm(Image *image, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        return;
    }

    // Escreve o cabeçalho do arquivo

    fprintf(file, "%s\n", PPM_MAGIC); // alterei ppm_magic por image->type
    fprintf(file, "%d %d\n", image->rows, image->cols);
    fprintf(file, "%d\n", PPM_MAX_VALUE);

    // Escreve os pixels da imagem

    unsigned char *data = image->data;
    for (int i = 0; i < image->rows; i++)
    {
        for (int j = 0; j < image->cols; j++)
        {
            if (strcmp(image->type, "P2") == 0)
            {
                fprintf(file, "%c ", data[i * image->cols + j]);
            }
            else if (strcmp(image->type, "P3") == 0)
            {
                fprintf(file, "%c %c %c ", data[i * image->cols * 3 + j * 3],
                        data[i * image->cols * 3 + j * 3 + 1],
                        data[i * image->cols * 3 + j * 3 + 2]);
            }
        }
    }

    fclose(file);
}
void rgb_to_gray(Image *image_rgb, Image *image_gray)
{
    if (image_rgb == NULL || image_gray == NULL)
    {
        return;
    }

    if (strcmp(image_rgb->type, "P3") != 0)
    {
        return;
    }

    int rows = image_rgb->rows;
    int cols = image_gray->cols;

    unsigned char *data_rgb = image_rgb->data;
    unsigned char *data_gray = image_gray->data;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            int r = data_rgb[i * cols * 3 + j * 3];
            int g = data_rgb[i * cols * 3 + j * 3 + 1];
            int b = data_rgb[i * cols * 3 + j * 3 + 2];

            int gray = 0.299 * r + 0.587 * g + 0.114 * b;

            data_gray[i * cols + j] = gray;
        }
    }
}
void free_image(Image *image)
{
    if (image == NULL)
    {
        return;
    }

    free(image->data);
    free(image);
}
