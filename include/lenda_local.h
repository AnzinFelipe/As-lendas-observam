#ifndef LENDA_LOCAL_H
#define LENDA_LOCAL_H

#include "raylib.h"
#include <stdlib.h>
#include "lenda_conversa.h"

typedef struct Lendas_local {
    char *nome;
    bool primeiro_encontro;
    Texture2D imagem;
    Rectangle hitbox;
    Vector2 posicao;
    int chave;
    struct Lendas_local *prox;
} Lendas_local;

void inserir_lenda_local(Lendas_local **head, char *nome, bool primeiro_encontro, Texture2D imagem, Rectangle hitbox,
    Vector2 posicao, int chave);

void liberar_lendas_local(Lendas_local **head);

Lendas_local * pegar_lenda_atual(Lendas_local *head, int chave_atual);

void desenhar_lendas_local(Lendas_local *lenda);

void interagir_lenda_local(Lendas_local *lenda, Lendas_conversa *head, Vector2 mouse, Lendas_conversa **conversa_atual);

#endif