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
                     Texture2D *img_ouro_local, Texture2D *img_ouro_conversa,
                     Texture2D *img_isqueiro) {
    (void)img_isqueiro;

    memset(mg, 0, sizeof(MinigameState));
    mg->fase             = MINIGAME_FASE_DIALOGO_INTRO;
    mg->tempo_restante   = MINIGAME_TEMPO_TOTAL;
    mg->img_observadora  = img_ouro_local;
    mg->img_observadora2 = img_ouro_conversa;
    mg->dialogo_finalizado = false;
    mg->gameover_timer   = 0.0f;

    // (fallback se a IA falhou)
    if (texto_ia && strlen(texto_ia) > 0) {
        strncpy(mg->texto_ia, texto_ia, sizeof(mg->texto_ia) - 1);
    } else {
        strncpy(mg->texto_ia,
                "Eu vejo tudo o que você faz nessas ruas... não vai escapar de mim.",
                sizeof(mg->texto_ia) - 1);
    }
    mg->texto_ia[sizeof(mg->texto_ia) - 1] = '\0';

    RayDialNode *fala1 = criar_node_dialogo(
        "Subconsciente",
        "--Algo está errado... você sente que alguém te observa.--"
    );
    RayDialNode *fala2 = criar_node_dialogo("Boca de Ouro", mg->texto_ia);
    RayDialNode *fala3 = criar_node_dialogo(
        "Subconsciente",
        "--Ele acendeu algo e jogou seu isqueiro escondido pelo bairro! Você tem 30 segundos para encontrá-lo antes que a chama se apague!--"
    );

    AddChoice(fala1, fala2);
    AddChoice(fala2, fala3);

    mg->dialogo_intro   = fala1;
    mg->manager_intro   = CreateDialogueManager(fala1);

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
                mg->fase = MINIGAME_FASE_SUCESSO;
                return true;
            }
        }
    }

    return false;
}

void MinigameDesenharIntro(MinigameState *mg) {
    if (!mg->manager_intro) return;

    DrawRectangle(0, 0, 1600, 900, (Color){0, 0, 0, 160});

    if (mg->img_observadora2 && mg->img_observadora2->id != 0) {
        DrawTextureEx(*mg->img_observadora2, (Vector2){0, 0}, 0.0f, 1.0f, WHITE);
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