#include "raylib.h"
#include <stdlib.h>

typedef struct arvore_mapa {
    int num;
    char nome[50];
    Texture2D imagem;
    struct arvore_mapa *esquerda;
    struct arvore_mapa *direita;
    struct arvore_mapa *anterior;
} arvore_mapa;