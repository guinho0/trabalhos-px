# Trabalho 1 Estrutura de Dados - TAD Image - Processador de Imagens PPM
# Alunos: Thiago Augusto de Carvalho e Ian Gandine
# Professor: Thiago Paixão

## Introdução

Este arquivo README.md é a documentação para o projeto "TAD Image - Processador de Imagens PPM". O objetivo deste projeto é demonstrar o uso de um Tipo Abstrato de Dados (TAD) para leitura, processamento e gravação de imagens no formato PPM em linguagem de programação C. O projeto é composto por três arquivos principais: image.c, image.h e main.c.

## Funções Implementadas

O projeto implementa as seguintes funções relacionadas ao TAD Image:

- `Image* create(int rows, int cols, char type[])`: Esta função cria uma nova imagem com o número especificado de linhas e colunas, além de indicar o tipo de imagem (P2 para tons de cinza ou P3 para colorida).

- `Image* load_from_ppm(const char* filename)`: Esta função carrega uma imagem a partir de um arquivo PPM especificado pelo nome do arquivo.

- `void write_to_ppm(Image* image, const char* filename)`: Esta função grava uma imagem em um arquivo PPM com o nome especificado.

- `void rgb_to_gray(Image* image_rgb, Image* image_gray)`: Esta função converte uma imagem colorida em uma imagem em tons de cinza, seguindo a fórmula matemática dada.
-`void free_image(Image *image)`: Esta função libera a memória que alocada para a imagem.

## Compilação e Execução
Nesse projeto, usamos o arquivo Makefile que facilita a execução do projeto.
Para compilar o projeto, execute o seguinte comando no terminal: make all.

obs: talvez no windows seja necessário usar o mingw32-make all ou o mingw64-make all.

obs2: voce pode tambem usar o comando: gcc main.c image.c -o tp1




## Uso

O programa oferece um menu de opções que permite carregar uma imagem, convertê-la em tons de cinza e gravá-la em um novo arquivo PPM. Certifique-se de seguir as instruções no menu ao executar o programa.

## Formato de Imagem Suportado

O programa suporta imagens PPM nos formatos "P2" (tons de cinza) e "P3" ( colorido e codificado em ASCII). Certifique-se de que suas imagens estejam em um desses formatos.



## Licença

Este projeto é licenciado sob a Licença MIT. Consulte o arquivo LICENSE para obter detalhes.

---

## Erros (apenas para a correção do professor)

erro 1: erro ao compilar pelo make all.(tive que usar o mingw32-make all).
erro 2: o código não está carregando a imagem, não sei se o erro é na imagem ou no código, ao abrir a imagem em editores aparentemente está tudo certo com ela. Assim, acredito que o está em create, pois o type não está retornando P3 ou P2, se isso estiver aqui, provavelmente é porque não deu tempo de resolver.
erro 3: se a imagem não carrega eu não consigo saber se as outras funções estão funcionando #tristeza.

