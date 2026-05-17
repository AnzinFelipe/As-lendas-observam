#include "mapa.h"
#include <stdlib.h>
#include "raylib.h"
#include <string.h>

void inserir_local(Arvore_mapa **local, int chave, char *nome, Texture2D imagem, Rectangle hitbox_esq,
Rectangle hitbox_dir, Rectangle hitbox_pai) {
    if (*local == NULL) {
        *local = (Arvore_mapa *)malloc(sizeof(Arvore_mapa));
        (*local)->chave = chave;
        (*local)->nome = malloc(strlen(nome) + 1);
        strcpy((*local)->nome, nome);
        (*local)->imagem = imagem;
        (*local)->esquerda = NULL;
        (*local)->direita = NULL;
        (*local)->hitbox_esq = hitbox_esq;
        (*local)->tem_hitbox_esq = (hitbox_esq.width != 0 || hitbox_esq.height != 0 || hitbox_esq.x != 0 || hitbox_esq.y != 0);
        (*local)->hitbox_dir = hitbox_dir;
        (*local)->tem_hitbox_dir = (hitbox_dir.width != 0 || hitbox_dir.height != 0 || hitbox_dir.x != 0 || hitbox_dir.y != 0);
        (*local)->hitbox_pai = hitbox_pai;
        (*local)->tem_hitbox_pai = (hitbox_pai.width != 0 || hitbox_pai.height != 0 || hitbox_pai.x != 0 || hitbox_pai.y != 0);
    } else {
        if (chave < (*local)->chave) {
            inserir_local(&(*local)->esquerda, chave, nome, imagem, hitbox_esq, hitbox_dir, hitbox_pai);
        } else if (chave > (*local)->chave) {
            inserir_local(&(*local)->direita, chave, nome, imagem, hitbox_esq, hitbox_dir, hitbox_pai);
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

Arvore_mapa * buscar_pai(Arvore_mapa *local, int chave) {
    if (local == NULL) {
        return NULL;
    } else if (local->esquerda != NULL && local->esquerda->chave == chave) {
        return local;
    } else if (local->direita != NULL && local->direita->chave == chave) {
        return local;
    } else if (chave < local->chave) {
        return buscar_pai(local->esquerda, chave);
    } else if (chave > local->chave) {
        return buscar_pai(local->direita, chave);
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
    DrawText(local->nome, 800 - MeasureText(local->nome, 25) / 2, 15, 25, WHITE);
    DrawTextureEx(local->imagem, (Vector2){240, 50}, 0.0, 0.7, WHITE);
}

void mudar_local(Arvore_mapa *local, Arvore_mapa *mapa, int *chave_atual, Vector2 mouse) {
    if (local->tem_hitbox_esq) {
        if (CheckCollisionPointRec(mouse, local->hitbox_esq)) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                if (local->esquerda != NULL) {
                    *chave_atual = local->esquerda->chave;
                }
            }
        }
    }
    if (local->tem_hitbox_dir) {
        if (CheckCollisionPointRec(mouse, local->hitbox_dir)) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                if (local->direita != NULL) {
                    *chave_atual = local->direita->chave;
                }
            }
        }
    }
    if (local->tem_hitbox_pai) {
        if (CheckCollisionPointRec(mouse, local->hitbox_pai)) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                Arvore_mapa *pai = buscar_pai(mapa, *chave_atual);
                if (pai != NULL) {
                    *chave_atual = pai->chave;
                }
            }
        }
    }
}

void desenhar_hitbox(Arvore_mapa *local) {
    if (local->tem_hitbox_esq) {
        DrawRectangleRec(local->hitbox_esq, (Color){255, 255, 255, 80});
    }
    if (local->tem_hitbox_dir) {
        DrawRectangleRec(local->hitbox_dir, (Color){255, 255, 255, 80});
    }
    if (local->tem_hitbox_pai) {
        DrawRectangleRec(local->hitbox_pai, (Color){255, 255, 255, 80});
    }
}

void mudar_mouse_mapa(Arvore_mapa *local, Vector2 mouse, bool *em_hitbox) {
    if (local->tem_hitbox_dir && local->tem_hitbox_esq) {
        if (CheckCollisionPointRec(mouse, local->hitbox_esq)) {
            *em_hitbox = true;
            SetMouseCursor(7);
        } else if (CheckCollisionPointRec(mouse, local->hitbox_dir)) {
            *em_hitbox = true;
            SetMouseCursor(8);
        }
    } else if (local->tem_hitbox_dir){
        if (CheckCollisionPointRec(mouse, local->hitbox_dir)) {
            *em_hitbox = true;
            SetMouseCursor(6);
        }
    } else if (local->tem_hitbox_esq) {
        if (CheckCollisionPointRec(mouse, local->hitbox_esq)) {
            *em_hitbox = true;
            SetMouseCursor(6);
        }
    }
    if (local->tem_hitbox_pai) {
        if (CheckCollisionPointRec(mouse, local->hitbox_pai)) {
            *em_hitbox = true;
            SetMouseCursor(9);
        }
    }
}
