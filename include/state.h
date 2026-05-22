#ifndef STATE_H
#define STATE_H

typedef enum GameState{
    EXPLORACAO,
    DIALOGO,
    MINIGAME_AGUARDANDO_IA,
    MINIGAME_INTRO,
    MINIGAME_BUSCA,
    MINIGAME_GAMEOVER
} GameState;

#endif
