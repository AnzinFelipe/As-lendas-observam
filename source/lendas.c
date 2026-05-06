#include "lendas.h"
#include <stdlib.h>
#include <string.h>
#include "raylib.h"

void inserir_lenda(Lendas **head, char *nome, bool primeiro_encontro, Texture2D imagem1, Texture2D imagem2, char **falas) {
    Lendas *novo = (Lendas *)malloc(sizeof(Lendas));
    if (novo != NULL) {
        novo->nome = malloc(strlen(nome) + 1);
        strcpy(novo->nome, nome);
        novo->primeiro_encontro = primeiro_encontro;
        novo->imagem1 = imagem1;
        novo->imagem2 = imagem2;
        novo->falas = (char **)malloc(6 * sizeof(char *));
        for (int i = 0; i < 6; i++) {
            novo->falas[i] = malloc(strlen(falas[i]) + 1);
            strcpy(novo->falas[i], falas[i]);
        }
        novo->prox = NULL;
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

void excluir_lenda(Lendas **head) {
    if (*head != NULL) {
        free((*head)->nome);
        for (int i = 0; i < 6; i++) {
            free((*head)->falas[i]);
        }
        free((*head)->falas);
        free(*head);
        *head = NULL;
    }
}

void desenhar_lenda(Lendas **lenda) {
    if (*lenda != NULL) {
        if ((*lenda)->primeiro_encontro == true) {
            (*lenda)->primeiro_encontro = false;
        }
        DrawTextureEx((*lenda)->imagem1, (Vector2){240, 50}, 0.0, 0.7, WHITE);
    }
}