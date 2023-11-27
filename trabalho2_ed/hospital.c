#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hospital.h"

struct hospital{
  int raioX[5][3]; 
  int laudo[3][3]; 
  float **reg;
};
struct pessoa {
  char nome[50];
  char cpf[15];
  int idade;
  int id;
  int doença[2];
  int entrada, E_raiox, S_raiox, E_laudo, S_laudo;
};
struct node {
  void *data;
  Node *Next;
  Node *Prev;
};
struct list {
  Node *First;
  Node *Last;
  int size;
};

struct fila {
  Node *Front;
  Node *Rear;
  int size;
};

List *cria_lista(){
    List *list = (List *)malloc(sizeof(List));
    list->First = NULL;
    list->Last = NULL;
    list->size = 0;
    return list;
}
void inserir_lista(List *list, void *data) {
    Node *novo = (Node*)malloc(sizeof(Node));
    novo->data = data;
    novo->Next = list->First;
    novo->Prev = NULL;
    if(list->size != 0) {
      list->First->Prev = novo;
    }
    else{
      list->Last = novo;
    }
    list->First = novo;
    list->size++;
}
void remove_lista(List *l, void *val) {
  Node *temp = l->First;
  Node *Prev = NULL;
  Node *aux;
  while (temp != NULL) {
    if (temp->data == val) {
      aux = temp;
      if (Prev != NULL) {
        Prev->Next = temp->Next;
        if (temp->Next == NULL) {
          l->Last = Prev;
        }
      } else {
        l->First = temp->Next;
        if (temp->Next == NULL) {
          l->Last = NULL;
        }
      }
      temp = temp->Next;
      free(aux);
    } 
    else {
      Prev = temp;
      temp = temp->Next;
    }
  }
  l->size--;
}
void libera_lista(List *list) {
    Node *First = list->First;
    Node *Next;
    while (First != NULL) {
        Next = First->Next;
        free(First);
        First = Next;
    }
    free(list);
}

Fila *cria_fila(){
  Fila *fila = (Fila *)malloc(sizeof(Fila));
    fila->Rear = NULL;
    fila->Front = NULL;
    fila->size = 0;
    return fila;
}
void remove_fila(Fila *fila) {
    if (fila->Front == NULL) {
        fprintf(stderr, "Erro: Fila vazia\n");
        return;
    }
    Node *temp = fila->Front;
    fila->Front = fila->Front->Next;
    if (fila->Front == NULL) {
        fila->Rear = NULL;
    } 
    else {
        fila->Front->Prev = NULL;
    }
    free(temp);           
    fila->size--;
}
void libera_fila(Fila *fila) {
    Node *Front = fila->Front;
    Node *Next;
    while (Front != NULL) {
        Next = Front->Next;
        free(Front);
        Front = Next;
    }
    free(fila);
}
Hospital *cria_hospital() {
  Hospital *hospital = (Hospital *)malloc(sizeof(Hospital));
  hospital->reg = (float**)malloc(5 * sizeof(int*));
  for (int i = 0; i < 5; i++) {
    hospital->reg[i] = (float *)malloc(sizeof(float) * 2);
    hospital->reg[i][0] = i+1;
    hospital->reg[i][1] = 0;
  }
  return hospital;
}
int gera_pessoa(){
  int gera_pessoa = rand() % 100;
  if(gera_pessoa < 20){
    return 1;
  }
  return 0;
}
int *gera__doença(){
  int gera__doença = rand() % 100;
  int *doença = (int*)malloc(sizeof(int)*2);
  int sn = 1;
  int b = 2;
  int p = 3;
  int ff = 4;
  int a = 4;

  if(gera__doença < 30 ){
    doença[0] = 1;
    doença[1] = sn;
  }
  else if (gera__doença >= 30 && gera__doença < 50){
    doença[0] = 2;
    doença[1] = b;
  }
  else if (gera__doença >= 50 && gera__doença < 70){
    doença[0] = 3;
    doença[1] = p;
  }
  else if (gera__doença >= 70 && gera__doença < 85){
    doença[0] = 4;
    doença[1] = ff;
  }
  else if (gera__doença >= 85){
    doença[0] = 5;
    doença[1] = a;
  }
  return doença;
}
int gera__raiox(){
  int gera__raiox = 5 + (rand() % 6);
  return gera__raiox;
}
int gera_laudo(){
  int gera_laudo = 10 + rand() % 21;
  return gera_laudo;
}
char* gera_nome() {
    char* nomes[] = {"thiago", "hiago", "samila", "camila", "jessica", "amanda", "jubileu", "pedro", "joão", "izaque", "Jesus"};
    int indice = rand() % (sizeof(nomes) / sizeof(nomes[0]));
    char* nome = strdup(nomes[indice]);
    return nome;
}
char* gera_cpf() {
    char cpf[15];
    sprintf(cpf, "%03d.%03d.%03d-%02d", rand() % 1000, rand() % 1000, rand() % 1000, rand() % 100);
    char* resultado = strdup(cpf);
    return resultado;
}
int gera_idade() {
  return rand() % 100;
}
Pessoa *gera_paciente(int id){
  Pessoa *paciente = (Pessoa*)malloc(sizeof(Pessoa));
  int *doença = (int*)malloc(sizeof(int)*2);
  doença = gera__doença();
  // Gera aleatoriamente o nome, CPF e idade
  strcpy(paciente->nome, gera_nome());
  strcpy(paciente->cpf, gera_cpf());
  paciente->idade = gera_idade();
  paciente->id = id;
  paciente->doença[0] = doença[0];
  paciente->doença[1] = doença[1];
  paciente->entrada = id;
  free(doença);
  return paciente;
}
void ordenado(Fila *fila, Pessoa *pessoa) {
    Node *novo = (Node*)malloc(sizeof(Node));
    novo->data = pessoa;
    novo->Prev = NULL;
    novo->Next = NULL;
    // Caso especial: fila vazia
    if (fila->Front == NULL) {
        fila->Front = novo;
        fila->Rear = novo;
        fila->size++;
        return;
    }
    Node *atual = fila->Front;
    while (atual != NULL && pessoa->doença[1] <= ((Pessoa *)atual->data)->doença[1]) {
        atual = atual->Next;
    }
    // Insere o novo na posição correta
    if (atual != NULL) {
        Node *Prev = atual->Prev;
        novo->Next = atual;
        novo->Prev = Prev;
        if (Prev != NULL) {
            Prev->Next = novo;
        } 
        else {
            fila->Front = novo;
        }
        atual->Prev = novo;
    } 
    else {
        Node *Last = fila->Rear;
        novo->Prev = Last;
        Last->Next = novo;
        fila->Rear = novo;
    }
    fila->size++;
}
void raiox(Fila *fila_sala_de_entrada, Fila *raiox, Hospital *hospital, int UT){
  if(fila_sala_de_entrada->Front == NULL){
    return;
  }
  Pessoa *aux = (Pessoa*)fila_sala_de_entrada->Front->data;
  for (int i = 0;i<5;i++){
    if(hospital->raioX[i][0] == 0){
      hospital->raioX[i][0] = 1;
      hospital->raioX[i][1] = gera__raiox();
      hospital->raioX[i][2] = aux->id;
      aux->E_raiox = UT;
      remove_fila(fila_sala_de_entrada);
      ordenado(raiox, aux);
      return;
    }
  }
}
void laudo(Fila *fila_raiox, Fila *laudo, Hospital *hospital, int UT){
  if (fila_raiox->Front == NULL) {
    return;
  }

  Pessoa *aux = (Pessoa *)fila_raiox->Front->data;
  if (aux->S_raiox == 0) {
    return;
  }

  for (int i = 0; i < 3; i++) {
    if (hospital->laudo[i][0] == 0) {
      hospital->laudo[i][0] = 1;
      hospital->laudo[i][1] = gera_laudo();
      hospital->laudo[i][2] = aux->id;
      aux->E_laudo = UT;
      remove_fila(fila_raiox);
      ordenado(laudo, aux);
      return;
    }
  }
}
void tempo_raiox(Hospital *hospital){
  for(int i = 0;i<5;i++){
    if(hospital->raioX[i][1] != 0){
      hospital->raioX[i][1]--;
    }
    if(hospital->raioX[i][1] == 0){
      hospital->raioX[i][0] = 0;
    }
  }
}
void tempo_laudo(Hospital *hospital){
  for(int i = 0;i<3;i++){
    if(hospital->laudo[i][1] != 0){
      hospital->laudo[i][1]--;
    }
    if(hospital->laudo[i][1] == 0){
      hospital->laudo[i][0] = 0;
    }
  }
}
void atualiza_raiox(Hospital *hospital, Fila *fila_raiox, int UT){
  for(int i = 0;i<5;i++){
    if(hospital->raioX[i][1] == 0){
      Node *Aux = fila_raiox->Front;
      Pessoa *paciente;
      while (Aux != NULL) {
        paciente = (Pessoa *)Aux->data;
        if (paciente->id == hospital->raioX[i][2]) {
          paciente->S_raiox = UT;
          hospital->raioX[i][2] = 0;
          return;
        }
        Aux = Aux->Next;
      }
    }
  }
}
void atualiza_laudo(Hospital *h, Fila *Laudo, int UT){
  for(int i = 0;i<3;i++){
    if(h->laudo[i][1] == 0){
      Node *Aux = Laudo->Front;
      while (Aux != NULL) {
        Pessoa *paciente = (Pessoa *)Aux->data;
        if (paciente->id == h->laudo[i][2]) {
          paciente->S_laudo = UT;
          h->laudo[i][2] = 0;
          return;
        }
        Aux = Aux->Next;
      }
    }
  }
}
int verifica_raiox(Hospital *h){
  for (int i = 0; i < 5; i++) {
    if (h->raioX[i][0] == 0) {
      return 1;
    }
  }
  return 0; 
}
int verifica_laudo(Hospital *h){
  for (int i = 0; i < 3; i++) {
    if (h->laudo[i][0] == 0) {
      return 1; 
    }
  }
  return 0;
}
void atualiza_tempo(Fila *Laudo, List *tempo){
  if(Laudo->Front == NULL || tempo->First == NULL){
    return;
  }
  Node *aux = Laudo->Front;
  if(((Pessoa*)aux->data)->S_laudo == 0) return;
  for(Node *UT = tempo->First;UT != NULL; UT = UT->Next){
    if(((Pessoa*)UT->data)->id == ((Pessoa*)aux->data)->id){
      tempo->First->data = UT->data; 
      remove_fila(Laudo);
      return;
    }
  }
}
void atualizacao_geral(Hospital *H, Fila *Raiox, Fila *Laudo, int UT){
  tempo_raiox(H);
    tempo_laudo(H);
    atualiza_raiox(H, Raiox, UT);
    atualiza_laudo(H, Laudo, UT);
}
float media_laudo(List *geral){
  float Soma = 0.0;
  int k = 0;
  Node *paciente = geral->First;
  for (int i = 0; i < geral->size; i++) {
      if (((Pessoa *)paciente->data)->S_laudo != 0) {
        Soma += ((Pessoa *)paciente->data)->S_laudo - ((Pessoa *)paciente->data)->entrada;
        k++;
      }
      paciente = paciente->Next;
  }
  if (k != 0) {
    return Soma / k;
  } 
  return 0.0;
}
void media_doenças(List *geral, Hospital *h) {
    if (geral->First == NULL) {
        return;
    }
    Node *aux = geral->First;
    for (int i = 0; i < 5; i++) {
        float somas = 0.0;
        int counter = 0;
        while (aux != NULL) {
            Pessoa *paciente = (Pessoa *)aux->data;
            if (paciente->S_laudo != 0 && paciente->doença[0] == h->reg[i][0]) {
                somas += paciente->S_laudo - paciente->entrada;
                counter++;
            }
            aux = aux->Next;
        }
      if(counter!=0){
        h->reg[i][1] = somas/ counter;
      }
      else{
        h->reg[i][1] = 0.0;
      }
      h->reg[i][1] = (counter != 0) ? (somas / counter) : 0.0;
        aux = geral->First;
    }
}
int pos_tempo(List *geral){
  float Soma = 0.0;
  int counter = 0;
  Node *aux = (Node *)malloc(sizeof(Node));
  aux = geral->First;

  for (int i = 0; i < geral->size; i++) {
      if (((Pessoa *)aux->data)->S_laudo != 0) {
        Soma = ((Pessoa *)aux->data)->S_laudo - ((Pessoa *)aux->data)->entrada;
        if(Soma>7200){
          counter++;
        }
      }
      aux = aux->Next;
  }
  return counter;
} 
void printa_metrica(List *geral, Hospital *h){
  media_doenças(geral,  h);
  printf("laudo: %f\ndoencas:\nsn: %f\nb: %f\np: %f\nff: %f\na: %f\nFora do tempo: %d\n\n", media_laudo(geral),  h->reg[0][1], h->reg[1][1], h->reg[2][1], h->reg[3][1], h->reg[4][1], pos_tempo(geral));
}
void libera_hospital(Hospital *h) {
  if (h != NULL) {
    for (int i = 0; i < 5; i++) {
      free(h->reg[i]);
    }
    free(h->reg);
    free(h);
  }
}