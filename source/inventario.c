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

/*aloca a lissta encadeada do inventário
usa como parâmetros os inventário **head, char *nome, char *descricao, texture2d imagem
cria inventario *novo e aloca a memoria para ele (inventario novo = (inventario*)malloc(sizeof(inventario)))
se novo for diferente de null (allocou o espaço)
alocca memoria para o nome de novo(malloc(strlen(nome)+1))
copia o nome para novo->nome(strcpy(novo->nome,nome))
alloca memoria para a descricao de novo(novo->descricao = malloc(strlen(descricao)+1))
copia a descricao para a descricao de novo(strcpy(novo->descricao, descricao))
bota como imagem de novo a imagem(novo -> imagem = imagem)
define o novo como não estando pego(novo->pego = false)
define o proximo do inventario para o novo como null(novo->prox = NULL)
se *head for null(se não tiver nada alem de novo basicamente)
define *head como novo (*head = novo)
caso tenha algo além do novo(else)
inventario *aux = *head 
enquanto o proximo elemento de aux não for o último(while(aux -> prox != NULL))
define o aux como o proximo do aux/anda com o aux(aux = aux->prox)
quando chega ao aux ->prox = NULL, define o aux->prox como novo/último item na insercao
(aux -> prox = novo) 
*/
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

/*libera o inverntário? 
bota como parametro o **head pois altera
se *head for diferente de null (enquanto tiver items)
define inventario *aux como *head para poder deletar o item atual
enquanto *head for diferente de null(tiver items)
aux é igualado a *head, 
*head é igualado a *head prox (vai para o proximo item com a *head)
dá free no aux -> nome, free no aux -> descricao e free no aux 
l30 - l41 
*/

void desenhar_inventario(Inventario *head, int x, int y, int espacamento, Inventario *itemSelecionado) {
    for (int i = 1; i < 6; i++) {
        DrawCircle(100, i * 140, 50.0, DARKGRAY);
    }
    int i=0;
    Vector2 posicao;
    if (head != NULL) {
        while (head != NULL && i<5) {
            if (head == itemSelecionado) {
                head = head->prox;
                i++;
                continue;
            }
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

/*desenha inventário na tela, tem como parametros *head, x, y e o espacanto, 
ele faz um for para desenhar os circulos do inventário l45 - l48
depois ele inicializa i, vector2 posicao, faz um while para enquanto head for diferente de NULL
esse while tem 5 elementos (os 5 itens do inventário), define tamanho como 70
posi
original = parametros da imagem originalmente (como ela está no mapa)
final = parametros da imagem quando ela está no inventário
head -> hitbox = final (define a hitbox dos items como igual a final)
drawtexturepro(desenha os itens no inventario, com os tamanhos dos parametros dados)
i++ e head = head -> prox; (anda no inventario para o proximo item pra desenhar se tiver item)
l49 - l63
*/ 

void LiberarItens_j(Inventario **head) {
    Inventario *aux = *head;
    while (aux != NULL) {
        Inventario *prox = aux->prox;
        free(aux);
        aux = prox;
    }
    *head = NULL;
}

/*libera itens?, itens != inventário?
passa como parametro **head para alterar a lista
define *aux como igual a *head (*aux = *head) 
faz um while enquanto aux não for null/ tiver item
define invetário proximo e coloca como aux proximo para ele ir para lá
quando deletar o item atual, 
dá free no aux/deleta o item atual
define aux como prox (Inventario prox)
bota head como null quando acaba
l78 - l86
*/ 

void atualizar_drag_inventario(Inventario *head, Vector2 mouse, Inventario **itemSelecionado, bool *arrastandoItem){
    // comeca a arrastar

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Inventario *aux = head;
        while (aux != NULL) {

            // Verifica se clicou em algum item do inventário
            if (CheckCollisionPointRec(mouse, aux->hitbox)) {
                *itemSelecionado = aux;
                *arrastandoItem = true;
                break;
            }
            aux = aux->prox;
        }
    }
    // soltar item


    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
        
        *arrastandoItem = false;
        *itemSelecionado = NULL;
    }
}

void desenhar_item_arrastando(Vector2 mouse, Inventario *itemSelecionado, bool arrastandoItem){
    // Se não existir item sendo arrastado,
    // não desenha nada
    if (!arrastandoItem || itemSelecionado == NULL) {
        return;
    }

    float tamanho = 70;

    Rectangle original = {0, 0, itemSelecionado->imagem.width, itemSelecionado->imagem.height};

    // Faz o item seguir o mouse
    Rectangle destino = {mouse.x - tamanho / 2, mouse.y - tamanho / 2, tamanho, tamanho};

    DrawTexturePro(itemSelecionado->imagem, original, destino, (Vector2){0, 0},0.0,WHITE);
}





