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
        novo->dialogo_final = NULL;
        novo->dialogo_final_repetido = NULL;
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
            FreeDialogueNode(aux->dialogo_final);
            FreeDialogueNode(aux->dialogo_final_repetido);
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
                    FreeDialogueNode(temp->dialogo_final);
                    FreeDialogueNode(temp->dialogo_final_repetido);
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
            if (strcmp(lenda->nome, "Papa-figo") == 0 && strcmp((*item)->nome, "Saco de pano") == 0) {
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                    excluir_item(head, *item);
                    insertion_sort_iventario(head);
                    *item = NULL;
                    //gameover
                    return;
                }
            }
            if (strcmp(lenda->item_quest, (*item)->nome) == 0) {
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                    if (strcmp(lenda->nome, "Rachadura") == 0) {
                        excluir_lenda(lenda_local, 104);
                        inserir_lenda(lenda_local, "Emparedada da Rua Nova", true, s->rachadura2, s->emparedada1, s->emparedada2, (Rectangle){580, 150, 320, 420}, (Vector2){200, 20}, s->mingau, "Cara de La Ursa", 104);
                        Lendas *emparedada = pegar_lenda_atual(*lenda_local, 104);

                        RayDialNode *emparedada_fala1 = CreateDialogueNode("fala1", "");
                        RayDialNode *emparedada_fala2 = CreateDialogueNode("fala2", "");
                        RayDialNode *emparedada_fala3 = CreateDialogueNode("fala3", "");
                        RayDialNode *emparedada_fala4 = CreateDialogueNode("fala4", "");
                        RayDialNode *emparedada_fala5 = CreateDialogueNode("fala5", "");
                        RayDialNode *emparedada_fala6 = CreateDialogueNode("fala6", "");
                        RayDialNode *emparedada_fala7 = CreateDialogueNode("fala7", "");
                        RayDialNode *emparedada_fala8 = CreateDialogueNode("fala8", "");
                        RayDialNode *emparedada_fala9 = CreateDialogueNode("fala9", "");
                        RayDialNode *emparedada_fala10 = CreateDialogueNode("fala10", "");
                        RayDialNode *emparedada_fala11 = CreateDialogueNode("fala11", "");
                        RayDialNode *emparedada_fala12 = CreateDialogueNode("fala12", "");

                        emparedada_fala1->components = criarComp(emparedada->nome, "OBRIGADA POR ME TIRAR DA PAREDE! Mas eu estou com uma aparência péssima...");
                        emparedada_fala2->components = criarComp(emparedada->nome, "Por favor, me ajude mais uma vez... não quero que me veja meio morta-viva meio espectro...");
                        emparedada_fala3->components = criarComp(emparedada->nome, "O processo para se tornar um espectro é meio demorado... queria ter uma máscara legal por enquanto...");
                        emparedada_fala4->components = criarComp("Subconsciente", "--Você precisa ajudá-la mais uma vez, será que tem algum tipo de máscara largada por aí?--");
                        emparedada_fala5->components = criarComp(emparedada->nome, "Vamos conversar quando eu tiver uma máscara por favor...");
                        emparedada_fala6->components = criarComp(emparedada->nome, "OBRIGADA! QUE CABEÇA LEGAL, ACHEI UM BARATO!");
                        emparedada_fala7->components = criarComp(emparedada->nome, "Agora sim podemos conversar. Oi, tudo bem? Por acaso tu tá perdido? Eu também, acredita? Eu estava presa numa parede há tanto tempo... mas não era nessa não.");
                        emparedada_fala8->components = criarComp(emparedada->nome, "Vim até aqui andando entre as paredes, não sei muito bem o por quê.");
                        emparedada_fala9->components = criarComp(emparedada->nome, "Acho que a única coisa que posso fazer por você é te dar um mingau que eu tinha acabado de fazer, gosta? Meu passatempo dentro da parede era fazer umas comidinhas gostosas.");
                        emparedada_fala10->components = criarComp(emparedada->nome, "Mais uma vez obrigada por me ajudar, o mundo precisa de mais gente como você.");
                        emparedada_fala11->components = criarComp("Subconsciente", "--Um mingau? Parece gostoso, mas você não parece com fome, talvez possa oferecê-lo para outra pessoa.--");
                        emparedada_fala12->components = criarComp(emparedada->nome, "Oi de novo! É muito bom poder estar aqui fora.");

                        AddChoice(emparedada_fala1, emparedada_fala2);
                        AddChoice(emparedada_fala2, emparedada_fala3);
                        AddChoice(emparedada_fala3, emparedada_fala4);
                        AddChoice(emparedada_fala6, emparedada_fala7);
                        AddChoice(emparedada_fala7, emparedada_fala8);
                        AddChoice(emparedada_fala8, emparedada_fala9);
                        AddChoice(emparedada_fala9, emparedada_fala10);
                        AddChoice(emparedada_fala10, emparedada_fala11);

                        emparedada->dialogo_raiz = emparedada_fala1;
                        emparedada->dialogo_repetido = emparedada_fala5;
                        emparedada->dialogo_final = emparedada_fala6;
                        emparedada->dialogo_final_repetido = emparedada_fala12;
                    } else {
                        lenda->quest_completa = true;
                        lenda->ja_conversou = false;
                    }
                    excluir_item(head, *item);
                    insertion_sort_iventario(head);
                    *item = NULL;
                }
            }
        }
    }
}