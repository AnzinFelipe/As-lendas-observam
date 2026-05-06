#ifndef SCREENS_H
#define SCREENS_H

#include "raylib.h"

typedef enum GameScreen {
    MENU,
    JOGO,
    SAIR
} GameScreen;

GameScreen RunMenu(void);

#endif