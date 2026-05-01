#include "mapa.h"
#include <stdlib.h>
#include "raylib.h"
#include <string.h>

void inserir_local(Arvore_mapa **local, int chave, char nome[50], Texture2D imagem, Arvore_mapa *pai) {
    if (*local == NULL) {
        *local = (Arvore_mapa *)malloc(sizeof(Arvore_mapa));
        (*local)->chave = chave;
        strcpy((*local)->nome, nome);
        (*local)->imagem = imagem;
        (*local)->esquerda = NULL;
        (*local)->direita = NULL;
        (*local)->pai = pai;
    } else {
        if (chave < (*local)->chave) {
            inserir_local(&(*local)->esquerda, chave, nome, imagem, *local);
        } else if (chave > (*local)->chave) {
            inserir_local(&(*local)->direita, chave, nome, imagem, *local);
        }
    }
}

Arvore_mapa * buscar_local(Arvore_mapa *local, int chave) {
    if (local == NULL) {
        return NULL;
    } else if (local->chave == chave) {
        return local;
    } else if (chave < local->chave) {
        buscar_local(local->esquerda, chave);
    } else if (chave > local->chave) {
        buscar_local(local->direita, chave);
    }
    return NULL;
}

void liberar_arvore(Arvore_mapa **local) {
    if (*local == NULL) {
        return;
    }

    liberar_arvore(&(*local)->esquerda);
    liberar_arvore(&(*local)->direita);
    free(*local);
    *local = NULL;
}