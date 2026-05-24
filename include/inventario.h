#ifndef INVENTARIO
#define INVENTARIO

#include "raylib.h"
#include <stdlib.h>
typedef struct Vars_structs_inicio_jogo Vars_structs_inicio_jogo;

typedef struct Inventario {
    char *nome;
    char *descricao;
    Texture2D imagem;
    Vector2 localMapa;
    Rectangle hitbox;
    int relevancia;
    bool pego;
    struct Inventario *prox;
} Inventario;

void inserir_inventario(Inventario **head, char *nome, char *descricao, Texture2D imagem, int relevancia);

void liberar_inventario(Inventario **head);

void desenhar_inventario(Inventario *head, int x, int y, int espacamento, Inventario *itemSelecionado);

void LiberarItens_j(Inventario**head);

void atualizar_drag_inventario(Inventario *head, Vector2 mouse, Inventario **itemSelecionado, bool *arrastandoItem);

void desenhar_item_arrastando(Vector2 mouse, Inventario *itemSelecionado, bool arrastandoItem);

void insertion_sort_iventario(Inventario **head);

void excluir_item(Inventario **head, Inventario *item);

void juntar_item(Inventario **head, Inventario **item, Vector2 mouse, Vars_structs_inicio_jogo *s);

#endif