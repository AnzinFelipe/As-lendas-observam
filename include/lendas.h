#ifndef LENDAS_H
#define LENDAS_H

#include "raylib.h"
#include <stdlib.h>

typedef struct Lendas {
    char *nome;
    bool primeiro_encontro;
    Texture2D imagem1;
    Texture2D imagem2;
    char **falas;
    struct Lendas *prox;
} Lendas;

void inserir_lenda(Lendas **head, char *nome, bool primeiro_encontro, Texture2D imagem1, Texture2D imagem2, char **falas);

void excluir_lenda(Lendas **head);

void desenhar_lenda(Lendas **lenda);

#endif