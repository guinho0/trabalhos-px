#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"

int main()
{
  Image *image = NULL;
  Image *image_gray = NULL;
  FILE *file;

  while (1)
  {
    int option;

    printf("Menu:\n");
    printf("1. Carregar imagem\n");
    printf("2. Converter para níveis de cinza\n");
    printf("3. Gravar imagem\n");
    printf("4. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &option);

    switch (option)
    {
    case 1:

      // Verifica se a imagem pode ser carregada
      file = fopen("C:/Users/thiag/Desktop/Trabalho_1/trabalhos-px/tp1/imagemp3peq.ppm", "r");
      if (file == NULL)
      {
        printf("Imagem não encontrada.\n");
        break;
      }
      fclose(file);
      printf("imagem encontrada\n"); // só pra verificar

      // Carrega a imagem para a memória
      image = load_from_ppm("C:/Users/thiag/Desktop/Trabalho_1/trabalhos-px/tp1/imagemp3peq.ppm");
      if (image == NULL)
      {
        printf("Erro ao carregar a imagem.\n");
        break;
      }
      else
      {
        printf("Imagem carregada com sucesso.\n");
      }
      break;

    case 2:
      // Converte a imagem para níveis de cinza
      if (image == NULL)
      {
        printf("É preciso carregar uma imagem antes de convertê-la para níveis "
               "de cinza.\n");
        break;
      }

      // Image *image_gray = create(image->rows, image->cols, "P2");
      if (image_gray == NULL)
      {
        printf("Erro ao criar a imagem em tons de cinza.\n");
        break;
      }

      rgb_to_gray(image, image_gray);

      // Libera a memória da imagem original
      free_image(image);
      free_image(image_gray);

      break;

    case 3:
      // Grava a imagem no disco
      if (image == NULL)
      {
        printf("É preciso carregar uma imagem antes de gravá-la.\n");
        break;
      }

      char filename[100];
      printf("Digite o caminho para salvar a imagem: ");
      scanf("%s", filename);

      write_to_ppm(image, filename);

      break;

    case 4:
      // Sai do programa
      free_image(image);
      return 0;
    }
  }

  return 0;
}
