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

void desenhar_inventario(Inventario *head, int x, int y, int espacamento) {
    for (int i = 1; i < 6; i++) {
        DrawCircle(100, i * 140, 50.0, DARKGRAY);
    }
    int i=0;
    Vector2 posicao;
    if (head != NULL) {
        while (head != NULL && i<5) {
            float tamanho = 70;
            posicao = (Vector2){x - tamanho / 2, y + i * espacamento - tamanho / 2};
            Rectangle original  = { 0, 0, head->imagem.width, head->imagem.height };
            Rectangle final = { posicao.x, posicao.y, tamanho, tamanho };
            head->hitbox = final;
            DrawTexturePro(head->imagem, original, final, (Vector2){0, 0}, 0.0, WHITE);
            i++;
            head = head->prox;
        }
    }
}

void LiberarItens_j(Inventario **head) {
    Inventario *aux = *head;
    while (aux != NULL) {
        Inventario *prox = aux->prox;
        free(aux);
        aux = prox;
    }
    *head = NULL;
}






