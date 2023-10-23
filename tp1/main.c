#include <stdio.h>
#include <stdlib.h>
#include "image.h"

int main()
{
    Image *image = NULL;
    Image *gray_image = NULL;

    int option;
    char filename[100]; // Tamanho do caminho do arquivo

    while (1)
    {
        printf("Menu:\n");
        printf("1. Carregar imagem\n");
        printf("2. Converter para niveis de cinza\n");
        printf("3. Gravar imagem\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            printf("Informe o caminho para a imagem: ");
            scanf("%s", filename);
            printf("erro aki1");
            image = load_from_ppm(filename);
            printf("erro aki");
            if (image == NULL)
            {
                printf("Falha ao carregar a imagem.\n");
            }
            break;
        case 2:
            if (image == NULL)
            {
                printf("Nenhuma imagem carregada.\n");
            }
            else
            {
                gray_image = create(image->rows, image->cols, "P2");
                rgb_to_gray(image, gray_image);
                printf("Imagem convertida para tons de cinza.\n");
            }
            break;
        case 3:
            if (gray_image == NULL)
            {
                printf("Nenhuma imagem em tons de cinza para gravar.\n");
            }
            else
            {
                printf("Informe o caminho de gravação da imagem em tons de cinza: ");
                scanf("%s", filename);
                write_to_ppm(gray_image, filename);
                printf("Imagem gravada com sucesso.\n");
            }
            break;
        case 4:
            if (image != NULL)
            {
                free_image(image);
            }

            if (gray_image != NULL)
            {
                free_image(gray_image);
            }
            printf("Encerrando o programa.\n");
            return 0;
        default:
            printf("Opcao invalida. Tente novamente.\n");
        }
    }

    return 0;
}
