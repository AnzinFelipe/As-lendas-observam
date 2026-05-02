#ifndef INVENTARIO
#define INVENTARIO

#include "raylib.h"
#include <stdlib.h>

typedef struct Inventario {
    char *nome;
    char *descricao;
    Texture2D imagem;
    Rectangle hitbox;
    bool pego;
    struct Inventario *prox;
} Inventario;

void inserir_inventario(Inventario **head, char *nome, char *descricao, Texture2D imagem);

void liberar_inventario(Inventario **head);

void desenhar_inventario(Inventario *head);

void pegar_item(Inventario *item, Vector2 *posicao, Vector2 padrao);

#endif