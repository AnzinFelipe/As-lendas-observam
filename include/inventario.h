#ifndef INVENTARIO
#define INVENTARIO

#include "raylib.h"
#include <stdlib.h>

typedef struct Inventario {
    char *nome;
    char *descricao;
    Texture2D imagem;
    Vector2 localMapa;
    Rectangle hitbox;
    bool pego;
    struct Inventario *prox;
} Inventario;

void inserir_inventario(Inventario **head, char *nome, char *descricao, Texture2D imagem);

void liberar_inventario(Inventario **head);

void desenhar_inventario(Inventario *head, int x, int y, int espacamento, Inventario *itemSelecionado);

void LiberarItens_j(Inventario**head);

void atualizar_drag_inventario(Inventario *head, Vector2 mouse, Inventario **itemSelecionado, bool *arrastandoItem);

void desenhar_item_arrastando(Vector2 mouse, Inventario *itemSelecionado, bool arrastandoItem);

#endif