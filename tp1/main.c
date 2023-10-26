#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"

int main()
{

  int op;        // operação
  char path[100]; /* Armazenando o nome do arquivo */
  int option;
  Image *img = (Image *)malloc(sizeof(Image *));// alocar imagem rgb
  Image *image_gray = (Image *)malloc(sizeof(Image *));//alocar imagem em tons de cinza

  while (op != 4)
  {

    printf("# Escolha uma opção: \n");
    printf("1-Carregar imagem.\n");
    printf("2-Converter para níveis de cinza.\n");
    printf("3-Gravar imagem no disco.\n");
    printf("4-Encerrar programa.\n");

    scanf("\n%d", &op);

    switch (op)
    {
    case 1:
      printf(" \nCARREGAR IMAGEM");

      printf("\nDeseja utilizar o nome padrão 'image.ppm' para o arquivo?\n");
      printf("(1) SIM\n");
      printf("(2) NÃO\n");
      scanf("%d", &option);

      if (option == 1)
      {
        strcpy(path, "image.ppm");
      }
      else if (option == 2)
      {
        printf("\nInforme o nome de origem do arquivo: \n");
        scanf("%s", path);
      }

      img = load_from_ppm(path);

      printf("\n\nImagem carregada com sucesso.\n\n");

      
      break;

      case 2:
        // Converte a imagem para níveis de cinza
        if (img == NULL)
        {
          printf("Eh preciso carregar uma imagem antes de converte-la para niveis "
                 "de cinza.\n");
          break;
        }

        
        if (image_gray == NULL)
        {
          printf("Erro ao criar a imagem em tons de cinza.\n");
          break;
        }

        rgb_to_gray(img, image_gray);

        // Libera a memória da imagem original
        free_image(img);
        free_image(image_gray);

        break;

      case 3:
        // Grava a imagem no disco
        if (img == NULL)
        {
          printf("Eh preciso carregar uma imagem antes de grava-la.\n");
          break;
        }

        char filename[100];
        printf("Digite o caminho para salvar a imagem: ");
        scanf("%s", filename);

        write_to_ppm(img, filename);

        break;

      case 4:
        // Sai do programa
        free_image(img);
        return 0;
      }
    }

      return 0;
    }
  

