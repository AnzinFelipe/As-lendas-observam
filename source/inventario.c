#include "inventario.h"
#include "raylib.h"
#include <stdlib.h>
#include <string.h>

void inserir_inventario(Inventario **head, char *nome, char *descricao, Texture2D imagem) {
    Inventario *novo = (Inventario *)malloc(sizeof(Inventario));
    if (novo != NULL) {
        novo->nome = malloc(strlen(nome) + 1);
        strcpy(novo->nome, nome);
        novo->descricao = malloc(strlen(descricao) + 1);
        strcpy(novo->descricao, descricao);
        novo->imagem = imagem;
        novo->pego = false;
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
            free(aux->descricao);
            free(aux);
        }
    }
}

void desenhar_inventario(Inventario *head) {
    for (int i = 1; i < 6; i++) {
        DrawCircle(100, i * 140, 50.0, DARKGRAY);
    }
    Vector2 padrao;
    int pos = 100;
    Vector2 posicao;
    if (head != NULL) {
        while (head != NULL) {
            posicao = (Vector2){60, pos};
            padrao = posicao;
            head->hitbox = (Rectangle){posicao.x, posicao.y, 80, 80};
            pegar_item(head, &posicao, padrao);
            head->hitbox = (Rectangle){posicao.x, posicao.y, 80, 80};
            //DrawRectangleRec(head->hitbox, BLUE);
            DrawTextureEx(head->imagem, posicao, 0.0, 0.4, WHITE);
            pos += 140;
            head = head->prox;
        }
    }
}

void pegar_item(Inventario *item, Vector2 *posicao, Vector2 padrao) {
    if (CheckCollisionPointRec(GetMousePosition(), item->hitbox)) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            item->pego = true;
        }
    }
    if (item->pego == true) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            *posicao = (Vector2){GetMousePosition().x - (item->imagem.width  * 0.4f) / 2,
            GetMousePosition().y - (item->imagem.height * 0.4f) / 2};
        } else {
            item->pego = false;
            *posicao = padrao;
        }
    }
}
