#ifndef LENDA_CONVERSA_H
#define LENDA_CONVERSA_H

#include "raylib.h"
#include <stdlib.h>

typedef struct Lendas_conversa {
    char *nome;
    bool primeiro_encontro;
    Texture2D imagem1;
    Texture2D imagem2;
    char **falas;
    struct Lendas_conversa *prox;
} Lendas_conversa;

void inserir_lenda_conversa(Lendas_conversa **head, char *nome, bool primeiro_encontro, Texture2D imagem1, Texture2D imagem2, char **falas);

void liberar_lenda_conversa(Lendas_conversa **head);

Lendas_conversa * pegar_conversa_atual(Lendas_conversa *head, char *nome);

void desenhar_lenda_conversa(Lendas_conversa *lenda);

#endif