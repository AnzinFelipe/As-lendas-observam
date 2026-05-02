#include "inventario.h"
#include "raylib.h"
#include <stdlib.h>
#include <string.h>

void inserir_inventario(Inventario **head, char *nome, Texture2D imagem) {
    Inventario *novo = (Inventario *)malloc(sizeof(Inventario));
    if (novo != NULL) {
        novo->nome = malloc(strlen(nome) + 1);
        strcpy(novo->nome, nome);
        novo->imagem = imagem;
        novo->prox = NULL;
        if (*head == NULL) {
            *head = novo;
        } else {
            Inventario *aux = *head;
            while (aux->prox != NULL) {
                aux = aux->prox;
            } 
            aux->prox = novo;
        }
    }
}

void liberar_inventario(Inventario **head) {
    if (*head != NULL) {
        Inventario *aux = *head;
        while (*head != NULL) {
            aux = *head;
            *head = (*head)->prox;
            free(aux->nome);
            free(aux);
        }
    }
}

void desenhar_inventario(Inventario *head) {
    for (int i = 1; i < 6; i++) {
        DrawCircle(100, i * 140, 50.0, DARKGRAY);
    }
    int pos = 100;
    if (head != NULL) {
        while (head != NULL) {
            DrawTextureEx(head->imagem, (Vector2){60, pos}, 0.0, 0.4, WHITE);
            pos += 140;
            head = head->prox;
        }
    }
}
