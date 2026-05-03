#include "mapa.h"
#include <stdlib.h>
#include "raylib.h"
#include <string.h>

void inserir_local(Arvore_mapa **local, int chave, char *nome, Texture2D imagem, Arvore_mapa *pai, Rectangle *hitbox_esq,
Rectangle *hitbox_dir, Rectangle *hitbox_pai) {
    if (*local == NULL) {
        *local = (Arvore_mapa *)malloc(sizeof(Arvore_mapa));
        (*local)->chave = chave;
        (*local)->nome = malloc(strlen(nome) + 1);
        strcpy((*local)->nome, nome);
        (*local)->imagem = imagem;
        (*local)->esquerda = NULL;
        (*local)->direita = NULL;
        (*local)->pai = pai;
        (*local)->hitbox_esq = hitbox_esq;
        (*local)->hitbox_dir = hitbox_dir;
        (*local)->hitbox_pai = hitbox_pai;
    } else {
        if (chave < (*local)->chave) {
            inserir_local(&(*local)->esquerda, chave, nome, imagem, *local, hitbox_esq, hitbox_dir, hitbox_pai);
        } else if (chave > (*local)->chave) {
            inserir_local(&(*local)->direita, chave, nome, imagem, *local, hitbox_esq, hitbox_dir, hitbox_pai);
        }
    }
}

Arvore_mapa * buscar_local(Arvore_mapa *local, int chave) {
    if (local == NULL) {
        return NULL;
    } else if (local->chave == chave) {
        return local;
    } else if (chave < local->chave) {
        return buscar_local(local->esquerda, chave);
    } else if (chave > local->chave) {
        return buscar_local(local->direita, chave);
    }
    return NULL;
}

void liberar_arvore(Arvore_mapa **local) {
    if (*local == NULL) {
        return;
    }

    liberar_arvore(&(*local)->esquerda);
    liberar_arvore(&(*local)->direita);
    free((*local)->nome);
    free(*local);
    *local = NULL;
}

void desenhar_local(Arvore_mapa *local) {
    DrawText(local->nome, 770 - MeasureText(local->nome, 25) / 2, 15, 25, WHITE);
    DrawTextureEx(local->imagem, (Vector2){200, 50}, 0.0, 0.7, WHITE);
}

void mudar_local(Arvore_mapa *local, int *chave_atual) {
    if (local->hitbox_esq != NULL) {
        if (CheckCollisionPointRec(GetMousePosition(), *(local->hitbox_esq))) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                if (local->esquerda != NULL) {
                    *chave_atual = local->esquerda->chave;
                }
            }
        }
    }
    if (local->hitbox_dir != NULL) {
        if (CheckCollisionPointRec(GetMousePosition(), *(local->hitbox_dir))) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                if (local->direita != NULL) {
                    *chave_atual = local->direita->chave;
                }
            }
        }
    }
    if (local->hitbox_pai != NULL) {
        if (CheckCollisionPointRec(GetMousePosition(), *(local->hitbox_pai))) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                if (local->pai != NULL) {
                    *chave_atual = local->pai->chave;
                }
            }
        }
    }
}

void desenhar_hitbox(Arvore_mapa *local) {
    if (local->hitbox_esq != NULL) {
        DrawRectangleRec(*(local->hitbox_esq), (Color){255, 255, 255, 80});
    }
    if (local->hitbox_dir != NULL) {
        DrawRectangleRec(*(local->hitbox_dir), (Color){255, 255, 255, 80});
    }
    if (local->hitbox_pai != NULL) {
        DrawRectangleRec(*(local->hitbox_pai), (Color){255, 255, 255, 80});
    }
}
