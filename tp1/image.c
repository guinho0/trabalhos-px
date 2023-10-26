#include "image.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct image
{
    int rows;
    int cols;
    char type[3];
    int max_pixel;
    unsigned char **data; // imagem em formato matricial
};

Image *create(int rows, int cols, char type[])
{
    Image *img = (Image *)malloc(sizeof(Image));
    if (img == NULL)
    {
        printf("Erro: falha ao alocar memória.\n");
        exit(EXIT_FAILURE);
        img->cols = cols;
        img->rows = rows;
        img->max_pixel = 255;

        strncpy(img->type, type, sizeof(img->type));

        if (strcmp(type, "P2") == 0)
        {
            // Aloca memória para matriz de matriz_pixel do tipo P2
            img->data = (unsigned char **)malloc(cols * sizeof(unsigned char *));

            for (int i = 0; i < cols; i++)
            {
                img->data[i] = (unsigned char *)malloc(rows * sizeof(unsigned char));
            }
        }
        // Aloca memória para matriz de matriz_pixel do tipo P3
        else if (strcmp(type, "P3") == 0)
        {
            img->data = (unsigned char **)malloc(cols * sizeof(unsigned char *));

            for (int i = 0; i < cols; i++)
            {
                img->data[i] = (unsigned char *)malloc(cols * 3 * sizeof(unsigned char));
            }
        }
        else
        {
            printf("Erro: tipo de imagem não suportado.\n");
            exit(EXIT_FAILURE);
        }
        return img;
    }
}
Image *load_from_ppm(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Arquivo não foi aberto...");
        exit(EXIT_FAILURE);
    }

    // Lê o cabeçalho do arquivo

    char type[3];
    int cols, rows, max_pixel, num;
    fscanf(file, "%s\n", type);

    fscanf(file, "%s", type);

    if (strcmp(type, "P3") == 0)
    {

        fscanf(file, "%d %d", &cols, &rows);
        fscanf(file, "%d", &max_pixel);

        Image *img = create(cols, rows, type);
        for (int i = 0; i < img->cols; i++)
        {
            for (int j = 0; j < img->rows * 3; j++)
            {
                fscanf(file, "%d", &num);
                img->data[i][j] = (unsigned char)num;
            }
        }
        return img;
    }

    else
    {
        printf("Erro: O arquivo %s não é do tipo P3.\n", filename);
        exit(EXIT_FAILURE);
    }
    fclose(file);
}

void write_to_ppm(Image *image, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        return;
    }

    // Escreve o cabeçalho do arquivo

    fprintf(file, "%s\n", image->type);
    fprintf(file, "%d %d\n", image->rows, image->cols);
    fprintf(file, "%d\n", image->max_pixel);

    // Escreve os pixels da imagem

    unsigned char *data = image->data;
    for (int i = 0; i < image->rows; i++)
    {
        for (int j = 0; j < image->cols; j++)
        {
            if (strcmp(image->type, "P2") == 0)
            {
                fprintf(file, "%d ", data[i * image->cols + j]);
            }
            else if (strcmp(image->type, "P3") == 0)
            {
                fprintf(file, "%d %d %d ", data[i * image->cols * 3 + j * 3],
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
