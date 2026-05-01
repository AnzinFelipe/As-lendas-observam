#ifndef MAPA
#define MAPA

#include "raylib.h"
#include <stdlib.h>

typedef struct Arvore_mapa {
    int chave;
    char nome[50];
    Texture2D imagem;
    struct Arvore_mapa *esquerda;
    struct Arvore_mapa *direita;
    struct Arvore_mapa *pai;
} Arvore_mapa;

void inserir_local(Arvore_mapa **local, int chave, char nome[50], Texture2D imagem, Arvore_mapa *pai);

Arvore_mapa * buscar_local(Arvore_mapa *local, int chave);

void liberar_arvore(Arvore_mapa **local);

#endif