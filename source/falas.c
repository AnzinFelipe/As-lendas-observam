#include "falas.h"
#include "raydial.h"

RayDialComponent *criarComp(const char *titulo, const char *texto) {
    RayDialComponent *comp = CreatePortraitDialogue(
        (Rectangle){250, 450, 1100, 300},
        titulo,
        texto,
        (Color){20, 20, 40, 255}
    );

    SetPortraitDialogueBoxStyle(
        comp,
        (Color){20, 20, 40, 255},
        (Color){150, 100, 200, 255},
        3,
        40
    );

    SetPortraitDialogueCornerRadius(comp, 40);
    SetPortraitDialogueAnimation(comp, true, 30.0f);

    return comp;
}