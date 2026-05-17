#include "raylib.h"
#include <stdlib.h>
#include <string.h>
#include "item.h"
#include "inventario.h"

void ColocarItemNoMapa(Item **Head, Texture2D imagem, char *nome, Vector2 localSpawn, char *descricao, int chave) {
    Item *novo = (Item*)malloc(sizeof(Item));
    novo->nome       = nome;
    novo->descricao  = descricao;
    novo->imagem     = imagem;
    novo->LocalSpawn = localSpawn;
    novo->hitbox     = (Rectangle){ localSpawn.x, localSpawn.y, imagem.width, imagem.height };
    novo->pego       = false;
    novo->prox       = NULL;
    novo->chave=chave;

    if (*Head == NULL) {
        *Head = novo;
    } else {
        Item *atual = *Head;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo;
    }
}

void PegarItemEEntrarInventário(Item **head, int chave_atual, Vector2 mouse_novo,Inventario **inventario, bool *em_hitbox){
    Item *aux=*head;
    while (aux != NULL) {
        if (!aux->pego && aux->chave == chave_atual) {
            if (CheckCollisionPointRec(mouse_novo, aux->hitbox)) {
                *em_hitbox = true;
                SetMouseCursor(4);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    aux->pego = true;
                    inserir_inventario(inventario, aux->nome, aux->descricao, aux->imagem);
                }
            }
        }
        aux = aux->prox;
    }  
}

void ItemAparecerNoCenario(Item **head, int chave_atual){
    Item *aux = *head;
    while (aux != NULL) {
        if (!aux->pego && aux->chave == chave_atual) {
            DrawTextureV(aux->imagem, aux->LocalSpawn, WHITE);
        }
        aux = aux->prox;
    }
}

void LiberarItens_i(Item **head) {
    Item *aux = *head;
    while (aux != NULL) {
        Item *prox = aux->prox;
        free(aux);
        aux = prox;
    }
    *head = NULL;
}