#ifndef INVENTARIO
#define INVENTARIO

#include "raylib.h"
#include <stdlib.h>

typedef struct Inventario {
    char *nome;
    Texture2D imagem;
    struct Inventario *prox;
} Inventario;

void inserir_inventario(Inventario **head, char *nome, Texture2D imagem);

void liberar_inventario(Inventario **head);

void desenhar_inventario(Inventario *head);

#endif