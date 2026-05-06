#include "lenda_local.h"
#include "lenda_conversa.h"
#include "raylib.h"
#include <stdlib.h>
#include <string.h>

void inserir_lenda_local(Lendas_local **head, char *nome, bool primeiro_encontro, Texture2D imagem, Rectangle hitbox, 
    Vector2 posicao, int chave) {
    Lendas_local *novo = (Lendas_local*)malloc(sizeof(Lendas_local));
    if (novo != NULL) {
        novo->nome = malloc(strlen(nome) + 1);
        strcpy(novo->nome, nome);
        novo->primeiro_encontro = primeiro_encontro;
        novo->imagem = imagem;
        novo->hitbox = hitbox;
        novo->posicao = posicao;
        novo->chave = chave;
        novo->prox = NULL;

        if (*head == NULL) {
            *head  = novo;
        } else {
            Lendas_local *aux = *head;
            while (aux->prox != NULL) {
                aux = aux->prox;
            } 
            aux->prox = novo;
        }
    }
}

void liberar_lendas_local(Lendas_local **head) {
    Lendas_local *aux = *head;
    while (*head != NULL) {
        aux = *head;
        *head = (*head)->prox;
        free(aux->nome);
        free(aux);
    }
}

Lendas_local * pegar_lenda_atual(Lendas_local *head, int chave_atual) {
    while (head != NULL) {
        if (head->chave == chave_atual) {
            return head;
        }
        head = head->prox;
    }
    return NULL;
}

void desenhar_lendas_local(Lendas_local *lenda) {
    if (lenda != NULL) {
        DrawTextureV(lenda->imagem, lenda->posicao, WHITE);
        DrawRectangleRec(lenda->hitbox, (Color){100, 100, 100, 100});
    }
}

void interagir_lenda_local(Lendas_local *lenda, Lendas_conversa *head, Vector2 mouse, Lendas_conversa **conversa_atual) {
    if (lenda != NULL) {
        if (CheckCollisionPointRec(mouse, lenda->hitbox)) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                *conversa_atual = pegar_conversa_atual(head, lenda->nome);
            }
            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                *conversa_atual = NULL;
            }
        }
    }
}