#ifndef MINIGAME_H
#define MINIGAME_H

#include "raylib.h"
#include "mapa.h"
#include "lendas.h"
#include "falas.h"
#include "gemini.h"
#include <stdbool.h>

#define MINIGAME_TEMPO_TOTAL 40.0f

#define MINIGAME_NOS_SEM_LENDA_COUNT 37
static const int MINIGAME_NOS_SEM_LENDA[MINIGAME_NOS_SEM_LENDA_COUNT] = {
    500,
    300,
    10,
    200,
    100,
    101,
    102,
    103,
    201,
    202,
    203,
    204,
    210,
    206,
    350,
    400,
    355,
    356,
    401,
    402,
    450,
    420,
    425,
    426,
    427,
    428,
    429,
    430,
    451,
    501,
    502,
    503,
    504,
    505,
    506,
    507,
    508,
};

typedef enum MinigameFase{
    MINIGAME_FASE_DIALOGO_INTRO,
    MINIGAME_FASE_BUSCA,
    MINIGAME_FASE_GAMEOVER,
    MINIGAME_FASE_SUCESSO
} MinigameFase;

typedef struct {
    MinigameFase fase;

    RayDialNode  *dialogo_intro;
    RayDialManager *manager_intro;
    int chave_isqueiro;
    Rectangle hitbox_isqueiro;
    bool isqueiro_visivel;
    float tempo_restante;
    Texture2D *img_observadora;
    Texture2D *img_observadora2;

    char texto_ia[512];
    bool dialogo_finalizado;
    float gameover_timer;
} MinigameState;

void MinigameIniciar(MinigameState *mg, const char *texto_ia,
                     Texture2D *img_ouro_local, Texture2D *img_ouro_conversa,
                     Texture2D *img_isqueiro);

void MinigameFinalizar(MinigameState *mg);

bool MinigameUpdateIntro(MinigameState *mg);

bool MinigameUpdateBusca(MinigameState *mg, int chave_atual, Vector2 mouse, float delta);

void MinigameDesenharIntro(MinigameState *mg);

void MinigameDesenharBusca(MinigameState *mg, int chave_atual, Texture2D *img_isqueiro);

#endif