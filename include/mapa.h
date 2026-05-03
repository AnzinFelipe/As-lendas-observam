#ifndef MAPA
#define MAPA

#include "raylib.h"
#include <stdlib.h>

typedef struct Arvore_mapa {
    int chave;
    char *nome;
    Texture2D imagem;
    struct Arvore_mapa *esquerda;
    Rectangle *hitbox_esq;
    struct Arvore_mapa *direita;
    Rectangle *hitbox_dir;
    struct Arvore_mapa *pai;
    Rectangle *hitbox_pai;
} Arvore_mapa;

void inserir_local(Arvore_mapa **local, int chave, char *nome, Texture2D imagem, Arvore_mapa *pai, Rectangle *hitbox_esq,
Rectangle *hitbox_dir, Rectangle *hitbox_pai);

Arvore_mapa * buscar_local(Arvore_mapa *local, int chave);

void liberar_arvore(Arvore_mapa **local);

void desenhar_local(Arvore_mapa *local);

void mudar_local(Arvore_mapa *local, int *chave_atual);

void desenhar_hitbox(Arvore_mapa *local);

#endif