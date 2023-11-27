#ifndef HOSPITAL_H
#define HOSPITAL_H

typedef struct node Node;
typedef struct list List;
typedef struct fila Fila;
typedef struct pessoa Pessoa;
typedef struct hospital Hospital;

List *cria_lista();
void inserir_lista(List *list, void *data);
void remove_lista(List *l, void *val);
void libera_lista(List *list);
Fila *cria_fila();
void remove_fila(Fila *fila);
void libera_fila(Fila *fila);
Hospital *cria_hospital();
int gera_pessoa();
int *gera__doença();
int gera__raiox();
int gera_laudo();
char* gera_nome();
Pessoa *gera_paciente(int id);
void ordenado(Fila *fila, Pessoa *novo_paciente);
void raiox(Fila *fila_sala_de_entrada, Fila *raiox, Hospital *hospital, int UT);
void laudo(Fila *fila_raiox, Fila *laudo, Hospital *hospital, int UT);
void tempo_raiox(Hospital *hospital);
void tempo_laudo(Hospital *hospital);
void atualiza_raiox(Hospital *hospital, Fila *fila_raiox, int UT);
void atualiza_laudo(Hospital *h, Fila *Laudo, int UT);
int verifica_raiox(Hospital *h);
int verifica_laudo(Hospital *h);
void atualiza_tempo(Fila *Laudo, List *tempo);
void atualizacao_geral(Hospital *H, Fila *Raiox, Fila *Laudo, int UT);
float media_laudo(List *geral);
void media_doenças(List *geral, Hospital *h);
int pos_tempo(List *geral);
void printa_metrica(List *geral, Hospital *h);
void libera_hospital(Hospital *h);
#endif