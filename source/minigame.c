#include "minigame.h"
#include "falas.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

static int escolher_no_aleatorio(void) {
    return MINIGAME_NOS_SEM_LENDA[GetRandomValue(0, MINIGAME_NOS_SEM_LENDA_COUNT - 1)];
}

static RayDialNode *criar_node_dialogo(const char *speaker, const char *texto) {
    RayDialNode *node = CreateDialogueNode("obs", "");
    node->components = criarComp_ouro(speaker, texto);
    return node;
}

void MinigameIniciar(MinigameState *mg, const char *texto_ia,
                     Texture2D *img_ouro_conversa1, Texture2D *img_ouro_conversa2,
                     Texture2D *img_isqueiro) {
    (void)img_isqueiro;

    memset(mg, 0, sizeof(MinigameState));
    mg->fase             = MINIGAME_FASE_DIALOGO_INTRO;
    mg->tempo_restante   = MINIGAME_TEMPO_TOTAL;
    mg->img1  = img_ouro_conversa1;
    mg->img2 = img_ouro_conversa2;
    mg->dialogo_finalizado = false;
    mg->gameover_timer   = 0.0f;

    // (fallback se a IA falhou)
    if (texto_ia && strlen(texto_ia) > 0) {
        strncpy(mg->texto_ia, texto_ia, sizeof(mg->texto_ia) - 1);
    } else {
        strncpy(mg->texto_ia,
                "Ei... estive te vendo a um tempo... muito tempo na verdade. Já falastes com umas figuras interessantes não? Pois agora é a minha vez de te atormentar.",
                sizeof(mg->texto_ia) - 1);
    }
    mg->texto_ia[sizeof(mg->texto_ia) - 1] = '\0';

    RayDialNode *fala1 = criar_node_dialogo(
        "Subconsciente",
        "--Um moço pertubador entrou na sua frente... você não consegue desviar o olhar da grande arcada dentária dourada dele.--"
    );
    RayDialNode *fala2 = criar_node_dialogo("Boca de Ouro", mg->texto_ia);
    RayDialNode *fala3 = criar_node_dialogo("Boca de Ouro", "Peço-te fogo. Se você conseguir achar um isqueiro, esclarecerei algumas coisas.");
    RayDialNode *fala4 = criar_node_dialogo("Boca de Ouro", "Porém se não achar nada... é melhor correr para bem longe, mas saiba que não importa o quanto corra, eu sempre estarei bem atrás de você...");

    AddChoice(fala1, fala2);
    AddChoice(fala2, fala3);
    AddChoice(fala3, fala4);

    mg->dialogo_intro   = fala1;
    mg->manager_intro   = CreateDialogueManager(fala1);

    RayDialNode *final1 = criar_node_dialogo("Boca de Ouro", "Agradecido... sabes porque tantas lendas estão aqui no meu Recife Velho?");
    RayDialNode *final2 = criar_node_dialogo("Boca de Ouro", "Há um aglomerado de pessoas aqui por perto... o imaginário coletivo nunca esteve tão vívido. Talvez seu destino seja encontrá-los.");
    RayDialNode *final3 = criar_node_dialogo("Boca de Ouro", "Encontre-se com eles e passe esta noite seguro, se conseguir. Até mais.");
    RayDialNode *final4 = criar_node_dialogo("Subconsciente", "--Você sobreviveu desta vez. Você ficou com o isqueiro, mas não parece ter nada mais para fazer com ele.--");
    RayDialNode *final5 = criar_node_dialogo("Subconsciente", "--Tente descobrir onde está esse aglomerado de pessoas.--");

    AddChoice(final1, final2);
    AddChoice(final2, final3);
    AddChoice(final3, final4);
    AddChoice(final4, final5);

    mg->dialogo_final   = final1;
    mg->manager_final   = NULL;

    // Escolhe nó aleatório para o isqueiro
    SetRandomSeed((unsigned int)time(NULL));
    mg->chave_isqueiro = escolher_no_aleatorio();

    mg->hitbox_isqueiro = (Rectangle){ 750, 250, 60, 60 };
    mg->isqueiro_visivel = false;
}

void MinigameFinalizar(MinigameState *mg) {
    if (mg->manager_intro) {
        FreeDialogueManager(mg->manager_intro);
        mg->manager_intro = NULL;
    }
    if (mg->manager_final) {
        FreeDialogueManager(mg->manager_final);
        mg->manager_final = NULL;
    }
    // Os nós são liberados junto com o manager
    mg->dialogo_intro = NULL;
}

bool MinigameUpdateIntro(MinigameState *mg) {
    if (!mg->manager_intro) return true;

    // Avança o diálogo com clique ou espaço
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_SPACE)) {
        AdvanceDialogue(mg->manager_intro);
    }

    UpdateDialogueManager(mg->manager_intro);

    if (!mg->manager_intro->isActive) {
        FreeDialogueManager(mg->manager_intro);
        mg->manager_intro = NULL;
        mg->fase = MINIGAME_FASE_BUSCA;
        return true;
    }

    return false;
}

bool MinigameUpdateBusca(MinigameState *mg, int chave_atual, Vector2 mouse, float delta) {
    mg->isqueiro_visivel = (chave_atual == mg->chave_isqueiro);

    // Atualiza timer
    mg->tempo_restante -= delta;
    if (mg->tempo_restante <= 0.0f) {
        mg->tempo_restante = 0.0f;
        mg->fase = MINIGAME_FASE_GAMEOVER;
        return true;
    }

    // Verifica se o jogador clicou no isqueiro
    if (mg->isqueiro_visivel) {
        if (CheckCollisionPointRec(mouse, mg->hitbox_isqueiro)) {
            SetMouseCursor(4);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                mg->fase = MINIGAME_FASE_DIALOGO_FINAL;
                mg->manager_final = CreateDialogueManager(mg->dialogo_final);
                mg->ignorar_proximo_clique = true;
                return true;
            }
        }
    }

    return false;
}

bool MinigameUpdateDialogoFinal(MinigameState *mg) {
    if (!mg->manager_final) return true;

    if (mg->ignorar_proximo_clique) {
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            mg->ignorar_proximo_clique = false;
        }
        UpdateDialogueManager(mg->manager_final);
        return false;
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_SPACE)) {
        AdvanceDialogue(mg->manager_final);
    }
    UpdateDialogueManager(mg->manager_final);

    if (!mg->manager_final->isActive) {
        FreeDialogueManager(mg->manager_final);
        mg->manager_final = NULL;
        mg->fase = MINIGAME_FASE_SUCESSO;
        return true;
    }
    return false;
}

void MinigameDesenharIntro(MinigameState *mg) {
    if (!mg->manager_intro) return;

    DrawRectangle(0, 0, 1600, 900, (Color){0, 0, 0, 160});

    if (mg->img1 && mg->img1->id != 0) {
        DrawTextureEx(*mg->img1, (Vector2){0, 0}, 0.0f, 1.0f, WHITE);
    }

    DrawDialogueManager(mg->manager_intro);
}

void MinigameDesenharBusca(MinigameState *mg, int chave_atual, Texture2D *img_isqueiro) {
    // Timer
    float pct = mg->tempo_restante / MINIGAME_TEMPO_TOTAL;

    Color cor_timer;
    if (pct > 0.5f) {
        cor_timer = GREEN;
    } else if (pct > 0.25f) {
        cor_timer = YELLOW;
    } else {
        int pisca = (int)(mg->tempo_restante * 4) % 2;
        cor_timer = pisca ? RED : ORANGE;
    }

    // Barra de progresso
    int barra_w = 500;
    int barra_h = 22;
    int barra_x = 800 - barra_w / 2;
    int barra_y = 830;

    DrawRectangle(barra_x - 2, barra_y - 2, barra_w + 4, barra_h + 4, DARKGRAY);
    DrawRectangle(barra_x, barra_y, (int)(barra_w * pct), barra_h, cor_timer);
    DrawRectangleLines(barra_x, barra_y, barra_w, barra_h, WHITE);

    // Texto do timer
    char buf[32];
    snprintf(buf, sizeof(buf), "%.0fs", mg->tempo_restante);
    int tw = MeasureText(buf, 20);
    DrawText(buf, 800 - tw / 2, barra_y + 25, 20, cor_timer);

    // Isqueiro no cenário
    if (chave_atual == mg->chave_isqueiro && img_isqueiro && img_isqueiro->id != 0) {
        // Efeito de brilho/pulsação simples
        float pulso = 0.85f + 0.15f * sinf(GetTime() * 5.0f);
        Color tint = { 255, (unsigned char)(200 * pulso), 0, 255 };

        Rectangle src = { 0, 0, (float)img_isqueiro->width, (float)img_isqueiro->height };
        Rectangle dst = mg->hitbox_isqueiro;
        DrawTexturePro(*img_isqueiro, src, dst, (Vector2){0, 0}, 0.0f, tint);
    }
}

void MinigameDesenharDialogoFinal(MinigameState *mg) {
    if (!mg->manager_final) return;
    DrawRectangle(0, 0, 1600, 900, (Color){0, 0, 0, 160});
    if (mg->img2 && mg->img2->id != 0) {
        DrawTextureEx(*mg->img2, (Vector2){0, 0}, 0.0f, 1.0f, WHITE);
    }
    DrawDialogueManager(mg->manager_final);
}