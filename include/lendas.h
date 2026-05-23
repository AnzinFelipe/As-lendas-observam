#ifndef LENDAS_H
#define LENDAS_H

#include "raylib.h"
#include <stdlib.h>
#include "raydial.h"
#include "inventario.h"

typedef struct Vars_structs_inicio_jogo Vars_structs_inicio_jogo;

typedef struct Lendas {
    char *nome;
    bool primeiro_encontro;
    Texture2D imagem;
    Texture2D img_conversa1;
    Texture2D img_conversa2;
    Rectangle hitbox;
    Vector2 posicao;
    int chave;
    RayDialNode *dialogo_raiz;
    bool ja_conversou;
    RayDialNode *dialogo_repetido;
    char *item_quest;
    bool quest_completa;
    RayDialNode *dialogo_final;
    RayDialNode *dialogo_final_repetido;
    Texture2D item;
    struct Lendas *prox;
} Lendas;

void inserir_lenda(Lendas **head, char *nome, bool primeiro_encontro, Texture2D imagem, Texture2D img_conversa1,
    Texture2D img_conversa2, Rectangle hitbox, Vector2 posicao, Texture2D item, char *item_quest, int chave);

void liberar_lendas(Lendas **head);

Lendas * pegar_lenda_atual(Lendas *head, int chave_atual);

void desenhar_lendas(Lendas *lenda);

void desenhar_lendas_conversa(Lendas *lenda);

bool interagir_lenda(Lendas *lenda, Vector2 mouse, bool *em_hitbox);

void excluir_lenda(Lendas **head, int chave);

void dar_item(Lendas **lenda_local, Lendas *lenda, Inventario **item, Vector2 mouse, Inventario **head, Vars_structs_inicio_jogo *s);

#endif