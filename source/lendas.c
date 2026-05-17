#include "raylib.h"
#include <stdlib.h>
#include <string.h>
#include "lendas.h"

void inserir_lenda(Lendas **head, char *nome, bool primeiro_encontro, Texture2D imagem,  Texture2D img_conversa1,
    Texture2D img_conversa2, Rectangle hitbox, Vector2 posicao, Texture2D item, int chave) {
    Lendas *novo = (Lendas*)malloc(sizeof(Lendas));
    if (novo != NULL) {
        novo->nome = malloc(strlen(nome) + 1);
        strcpy(novo->nome, nome);
        novo->primeiro_encontro = primeiro_encontro;
        novo->imagem = imagem;
        novo->img_conversa1 = img_conversa1;
        novo->img_conversa2 = img_conversa2;
        novo->hitbox = hitbox;
        novo->posicao = posicao;
        novo->chave = chave;
        novo->prox = NULL;
        novo->ja_conversou = false;
        novo->dialogo_raiz = NULL;
        novo->dialogo_repetido = NULL;
        novo->quest_completa = false;
        novo->item = item;

        if (*head == NULL) {
            *head  = novo;
        } else {
            Lendas *aux = *head;
            while (aux->prox != NULL) {
                aux = aux->prox;
            } 
            aux->prox = novo;
        }
    }
}

void liberar_lendas(Lendas **head) {
    Lendas *aux = *head;
    while (*head != NULL) {
        aux = *head;
        *head = (*head)->prox;
        free(aux->nome);
        free(aux);
    }
    *head = NULL;
}

Lendas * pegar_lenda_atual(Lendas *head, int chave_atual) {
    while (head != NULL) {
        if (head->chave == chave_atual) {
            return head;
        }
        head = head->prox;
    }
    return NULL;
}

void desenhar_lendas(Lendas *lenda) {
    if (lenda != NULL) {
        DrawTextureEx(lenda->imagem, lenda->posicao, 0.0, 0.4, WHITE);
        //DrawRectangleRec(lenda->hitbox, (Color){100, 100, 100, 100});
    }
}

void desenhar_lendas_conversa(Lendas *lenda) {
    if (lenda != NULL) {
        DrawTextureEx(lenda->img_conversa1, (Vector2){240, 50}, 0.0, 0.7, WHITE);
    }
}

bool interagir_lenda(Lendas *lenda, Vector2 mouse, bool *em_hitbox) {
    if (lenda != NULL) {
        if (CheckCollisionPointRec(mouse, lenda->hitbox)) {
            *em_hitbox = true;
            SetMouseCursor(4);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                *em_hitbox = false;
                return true;
            }
        }
    }

    return false;
}

