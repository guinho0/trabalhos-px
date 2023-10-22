#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"

// P3 = formato em PPM texto
// p6 = formato em PPM binário

Image *create(int rows, int cols, char type[])
{
    Image *image = (Image *)malloc(sizeof(Image));
    if (image == NULL)
    {
        fprintf(stderr, "Falha ao alocar memoria para a imagem.\n");
        exit(1);
    }
    image->rows = rows;
    image->cols = cols;
    strcpy(image->type, type);

    image->pixels = (unsigned char **)malloc(rows * sizeof(unsigned char *));
    if (image->pixels == NULL)
    {
        fprintf(stderr, "Falha ao alocar memoria para pixels.\n");
        free(image);
        exit(1);
    }

    for (int i = 0; i < rows; i++)
    {
        image->pixels[i] = (unsigned char *)malloc(cols * sizeof(unsigned char));
        if (image->pixels[i] == NULL)
        {
            fprintf(stderr, "Falha ao alocar memoria para pixels.\n");
            for (int j = 0; j < i; j++)
            {
                free(image->pixels[j]);
            }
            free(image->pixels);
            free(image);
            exit(1);
        }
    }

    return image;
}

Image *load_from_ppm(const char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        fprintf(stderr, "Falha ao abrir o arquivo: %s\n", filename);
        return NULL;
    }

    char type[3];
    int rows, cols, max_intensity;
    fscanf(file, "%2s\n", type);
    fscanf(file, "%d %d\n", &cols, &rows);
    fscanf(file, "%d\n", &max_intensity);

    if (strcmp(type, "P3") != 0 && strcmp(type, "P6") != 0)
    {
        fprintf(stderr, "Formato de imagem invalido: %s\n", type);
        fclose(file);
        return NULL;
    }

    Image *image = create(rows, cols, type);
    unsigned char **pixels = image->pixels;

    if (strcmp(type, "P3") == 0)
    {
        // Leitura do formato texto P3
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                fscanf(file, "%hhu %hhu %hhu", &pixels[i][3 * j], &pixels[i][3 * j + 1], &pixels[i][3 * j + 2]);
            }
        }
    }
    else if (strcmp(type, "P6") == 0)
    {
        // Leitura do formato binário P6
        for (int i = 0; i < rows; i++)
        {
            fread(pixels[i], 3, cols, file);
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
        fprintf(stderr, "Falha ao abrir o arquivo PPM de saída.\n");
        return;
    }

    fprintf(file, "%s\n", image->type);
    fprintf(file, "%d %d\n", image->cols, image->rows);
    fprintf(file, "255\n");

    for (int i = 0; i < image->rows; i++)
    {
        for (int j = 0; j < 3 * image->cols; j++)
        {
            fprintf(file, "%hhu ", image->pixels[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

void rgb_to_gray(Image *image_rgb, Image *image_gray)
{
    if (image_rgb == NULL || image_gray == NULL)
    {
        fprintf(stderr, "Imagem de entrada ou saída invalida.\n");
        return;
    }

    if (strcmp(image_rgb->type, "P3") != 0 && strcmp(image_rgb->type, "P6") != 0)
    {
        fprintf(stderr, "Conversao de tipo de imagem invalida.\n");
        return;
    }

    for (int i = 0; i < image_rgb->rows; i++)
    {
        for (int j = 0; j < image_rgb->cols; j++)
        {
            if (strcmp(image_rgb->type, "P3") == 0)
            {
                unsigned char r = image_rgb->pixels[i][3 * j];
                unsigned char g = image_rgb->pixels[i][3 * j + 1];
                unsigned char b = image_rgb->pixels[i][3 * j + 2];
                unsigned char gray_value = (unsigned char)(0.299 * r + 0.587 * g + 0.114 * b);
                image_gray->pixels[i][j] = gray_value;
            }
            else if (strcmp(image_rgb->type, "P6") == 0)
            {
                unsigned char r = image_rgb->pixels[i][j * 3];
                unsigned char g = image_rgb->pixels[i][j * 3 + 1];
                unsigned char b = image_rgb->pixels[i][j * 3 + 2];
                unsigned char gray_value = (unsigned char)(0.299 * r + 0.587 * g + 0.114 * b);
                image_gray->pixels[i][j] = gray_value;
            }
        }
    }
}
void free_image(Image *image)
{
    if (image == NULL)
    {
        return;
    }

    for (int i = 0; i < image->rows; i++)
    {
        free(image->pixels[i]);
    }

    free(image->pixels);
    free(image);
}
