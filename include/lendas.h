#ifndef LENDAS_H
#define LENDAS_H

#include "raylib.h"
#include <stdlib.h>
#include "raydial.h"

typedef struct Lendas {
    char *nome;
    bool primeiro_encontro;
    Texture2D imagem;
    Rectangle hitbox;
    Vector2 posicao;
    int chave;
    RayDialNode *dialogo_raiz;
    bool ja_conversou;
    RayDialNode *dialogo_repetido;
    struct Lendas *prox;
} Lendas;

void inserir_lenda(Lendas **head, char *nome, bool primeiro_encontro, Texture2D imagem, Rectangle hitbox,
    Vector2 posicao, int chave);

void liberar_lendas(Lendas **head);

Lendas * pegar_lenda_atual(Lendas *head, int chave_atual);

void desenhar_lendas(Lendas *lenda);

bool interagir_lenda(Lendas *lenda, Vector2 mouse);

#endif