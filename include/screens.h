#ifndef SCREENS_H
#define SCREENS_H

#include "raylib.h"

typedef enum GameScreen {
    MENU,
    JOGO,
    SAIR,
    CUTSCENE,
    GAME_OVER
} GameScreen;

GameScreen RunMenu(void);
GameScreen RunGameOver(int motivo);
GameScreen RunCutscene(void);

#endif