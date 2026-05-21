#ifndef SCREENS_H
#define SCREENS_H

#include "raylib.h"

typedef enum GameScreen {
    MENU,
    JOGO,
    SAIR,
    GAME_OVER
} GameScreen;

GameScreen RunMenu(void);
GameScreen RunGameOver(void);

#endif