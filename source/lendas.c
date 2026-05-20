#include "raylib.h"
#include <stdlib.h>
#include <string.h>
#include "lendas.h"
#include "inventario.h"
#include "iniciar_liberar_jogo.h"

void inserir_lenda(Lendas **head, char *nome, bool primeiro_encontro, Texture2D imagem,  Texture2D img_conversa1,
    Texture2D img_conversa2, Rectangle hitbox, Vector2 posicao, Texture2D item, char *item_quest, int chave) {
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
        novo->item_quest = malloc(strlen(item_quest) + 1);
        strcpy(novo->item_quest, item_quest);
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
        free(aux->item_quest);
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
        if (lenda->quest_completa) {
            DrawTextureEx(lenda->img_conversa2, (Vector2){240, 50}, 0.0, 0.7, WHITE);
        } else {
            DrawTextureEx(lenda->img_conversa1, (Vector2){240, 50}, 0.0, 0.7, WHITE);
        }
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

void excluir_lenda(Lendas **head, int chave) {
    if (*head != NULL) {  
        if ((*head)->chave == chave) {
            Lendas *aux = *head;
            *head = (*head)->prox;
            FreeDialogueNode(aux->dialogo_raiz);
            FreeDialogueNode(aux->dialogo_repetido);
            free(aux->nome);
            free(aux->item_quest);
            free(aux);
        } else {
            Lendas *aux = *head;
            while (aux->prox != NULL) {
                if (aux->prox->chave == chave) {
                    Lendas *temp = aux->prox;
                    aux->prox = temp->prox;
                    FreeDialogueNode(temp->dialogo_raiz);
                    FreeDialogueNode(temp->dialogo_repetido);
                    free(temp->nome);
                    free(temp->item_quest);
                    free(temp);
                    return;
                }
                aux = aux->prox;
            }
        }
    }
}

void dar_item(Lendas **lenda_local, Lendas *lenda, Inventario **item, Vector2 mouse, Inventario **head, Vars_structs_inicio_jogo *s) {
    if (lenda != NULL && *item != NULL) {
        if (CheckCollisionPointRec(mouse, lenda->hitbox)) {
            if (strcmp(lenda->item_quest, (*item)->nome) == 0) {
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                    if (strcmp(lenda->nome, "Rachadura") == 0) {
                        excluir_lenda(lenda_local, 104);
                        inserir_lenda(lenda_local, "Emparedada da Rua Nova", true, s->rachadura2, s->emparedada1, s->emparedada2, (Rectangle){580, 150, 320, 420}, (Vector2){200, 20}, s->mingau, "Cara de La Ursa", 104);
                        Lendas *emparedada = pegar_lenda_atual(*lenda_local, 104);

                        RayDialNode *emparedada_fala1 = CreateDialogueNode("fala1", "");
                        RayDialNode *emparedada_fala2 = CreateDialogueNode("fala2", "");

                        emparedada_fala1->components = criarComp(emparedada->nome, "OBRIGADA!!!");
                        emparedada_fala2->components = criarComp(emparedada->nome, "...");

                        emparedada->dialogo_raiz = emparedada_fala1;
                        emparedada->dialogo_repetido = emparedada_fala2;
                    } else {
                        lenda->quest_completa = true;
                    }
                    excluir_item(head, *item);
                    insertion_sort_iventario(head);
                    *item = NULL;
                }
            }
        }
    }
}
