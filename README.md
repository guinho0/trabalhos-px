# Trabalho 1 Estrutura de Dados - TAD Image - Processador de Imagens PPM
#Alunos: Thiago Augusto de Carvalho e Ian Gandine
#Professor: Thiago Paixão

## Introdução

Este arquivo README.md é a documentação para o projeto "TAD Image - Processador de Imagens PPM". O objetivo deste projeto é demonstrar o uso de um Tipo Abstrato de Dados (TAD) para leitura, processamento e gravação de imagens no formato PPM em linguagem de programação C. O projeto é composto por três arquivos: image.c, image.h e main.c.

## Funções Implementadas

O projeto implementa as seguintes funções relacionadas ao TAD Image:

- `Image* create(int rows, int cols, char type[])`: Esta função cria uma nova imagem com o número especificado de linhas e colunas, além de indicar o tipo de imagem (P2 para tons de cinza ou P3 para colorida).

- `Image* load_from_ppm(const char* filename)`: Esta função carrega uma imagem a partir de um arquivo PPM especificado pelo nome do arquivo.

- `void write_to_ppm(Image* image, const char* filename)`: Esta função grava uma imagem em um arquivo PPM com o nome especificado.

- `void rgb_to_gray(Image* image_rgb, Image* image_gray)`: Esta função converte uma imagem colorida em uma imagem em tons de cinza, seguindo a fórmula matemática dada.

## Compilação e Execução
Nesse projeto, usamos o arquivo Makefile que facilita a execução do projeto.
Para compilar o projeto, execute o seguinte comando no terminal: make(ou mingw32-make).




## Uso

O programa oferece um menu de opções que permite carregar uma imagem, convertê-la em tons de cinza e gravá-la em um novo arquivo PPM. Certifique-se de seguir as instruções no menu ao executar o programa.

## Formato de Imagem Suportado

O programa suporta imagens PPM nos formatos "P3" (texto) e "P6" (binário). Certifique-se de que suas imagens estejam em um desses formatos.

## Contribuições

Contribuições são bem-vindas! Sinta-se à vontade para abrir problemas ou enviar solicitações de pull para melhorar este projeto.

## Licença

Este projeto é licenciado sob a Licença MIT. Consulte o arquivo LICENSE para obter detalhes.

---

**Apreciamos sua participação!** 📸

