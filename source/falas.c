#include "falas.h"
#include "raydial.h"

RayDialComponent *criarComp(const char *titulo, const char *texto) {
    RayDialComponent *comp = CreatePortraitDialogue(
        (Rectangle){250, 520, 1100, 270},
        titulo,
        texto,
        (Color){0, 0, 0, 0}
    );

    SetPortraitDialogueBoxStyle(
        comp,
        (Color){33, 19, 13, 255},
        (Color){110, 59, 37, 255},
        3,
        40
    );  

    SetPortraitDialogueCornerRadius(comp, 40);
    SetPortraitDialogueAnimation(comp, true, 30.0f);

    return comp;
}

RayDialComponent *criarComp_ouro(const char *titulo, const char *texto) {
    RayDialComponent *comp = CreatePortraitDialogue(
        (Rectangle){25, 420, 800, 450},
        titulo,
        texto,
        (Color){0, 0, 0, 0}
    );

    SetPortraitDialogueBoxStyle(
        comp,
        (Color){33, 19, 13, 255},
        (Color){110, 59, 37, 255},
        3,
        40
    );  

    SetPortraitDialogueCornerRadius(comp, 40);
    SetPortraitDialogueAnimation(comp, true, 30.0f);

    return comp;
}
