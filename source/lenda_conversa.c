#include "lenda_conversa.h"
#include <stdlib.h>
#include <string.h>
#include "raylib.h"

void inserir_lenda_conversa(Lendas_conversa **head, char *nome, bool primeiro_encontro, Texture2D imagem1, Texture2D imagem2, char **falas) {
    Lendas_conversa *novo = (Lendas_conversa *)malloc(sizeof(Lendas_conversa));
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
            Lendas_conversa *aux = *head;
            while (aux->prox != NULL) {
                aux = aux->prox;
            } 
            aux->prox = novo;
        }
    }
}

void liberar_lenda_conversa(Lendas_conversa **head) {
    Lendas_conversa *aux = *head;
    while (*head != NULL) {
        aux = *head;
        *head = (*head)->prox;
        free(aux->nome);
        for (int i = 0; i < 6; i++) {
            free(aux->falas[i]);
        }
        free(aux->falas);
        free(aux);
    }
}

Lendas_conversa * pegar_conversa_atual(Lendas_conversa *head, char *nome) {
    while (head != NULL) {
        if (strcmp(head->nome, nome) == 0) {
            return head;
        }
        head = head->prox;
    }
    return NULL;
}

void desenhar_lenda_conversa(Lendas_conversa *lenda) {
    if (lenda != NULL) {
        if (lenda->primeiro_encontro == true) {
            lenda->primeiro_encontro = false;
        }
        DrawTextureEx(lenda->imagem1, (Vector2){240, 50}, 0.0, 0.7, WHITE);
        DrawRectangle(260, 530, 1080, 270, (Color){100, 100, 0, 255});
    }
}