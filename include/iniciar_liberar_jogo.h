#ifndef INICIAR_LIBERAR_JOGO_H
#define INICIAR_LIBERAR_JOGO_H

#include <stdlib.h>
#include "mapa.h"
#include "inventario.h"
#include "raylib.h"
#include <math.h>
#include "item.h"
#include <string.h>

typedef struct Vars_structs_inicio_jogo{
    RenderTexture2D tela;
    
    Music pink;

    Texture2D comercial;
    Texture2D marco_zero;
    Texture2D barbosa_lima1;
    Texture2D barbosa_lima2;
    Texture2D bom_jesus1;
    Texture2D bom_jesus2;
    Texture2D bom_jesus3;
    Texture2D arsenal;
    Texture2D frevo;
    Texture2D rodrigues_mendes;
    Texture2D parede;
    Texture2D guia;
    Texture2D observatorio1;
    Texture2D observatorio2;
    Texture2D cais_apolo;
    Texture2D cesar_brum;
    Texture2D malakoff;
    Texture2D item_teste;
    Texture2D honglu;
    Texture2D queenOfHatred;
    Texture2D comadre1;
    Texture2D comadre2;
    Texture2D cabra;
    Texture2D ouro2;

    Arvore_mapa *mapa;
    Arvore_mapa *local_atual;
    int chave_atual;

    Item *itensNaoPegos;

    Inventario *inventario;
} Vars_structs_inicio_jogo;

void iniciar_jogo(Vars_structs_inicio_jogo *s);

#endif