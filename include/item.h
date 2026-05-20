#ifndef ITEM_H
#define ITEM_H

#include "raylib.h"
#include <stdlib.h>
#include "inventario.h"

typedef struct Item{
    char *nome;
    char *descricao;
    Texture2D imagem;
    Vector2 LocalSpawn;
    bool pego;
    int relevancia;
    Rectangle hitbox;
    int chave;
    struct Item *prox;
} Item;

void ColocarItemNoMapa(Item **Head, Texture2D imagem, char *nome, Vector2 localSpawn, char *descricao, int chave, int relevancia);
void PegarItemEEntrarInventário(Item **head, int chave_atual, Vector2 mouse_novo,Inventario **inventario, bool *em_hitbox);
void ItemAparecerNoCenario(Item **head, int chave_atual);
void LiberarItens_i(Item **head);

#endif