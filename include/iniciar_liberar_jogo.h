#ifndef INICIAR_LIBERAR_JOGO_H
#define INICIAR_LIBERAR_JOGO_H

#include <stdlib.h>
#include "mapa.h"
#include "inventario.h"
#include "raylib.h"
#include <math.h>
#include "item.h"
#include <string.h>
#include "lendas.h"
#include "raydial.h"
#include "falas.h"

typedef struct Vars_structs_inicio_jogo{
    RenderTexture2D tela;
    
    Music pink;

    Texture2D comercial;
    Texture2D marco_zero;
    Texture2D barbosa_lima1;
    Texture2D barbosa_lima2;
    Texture2D barbosa_lima3;
    Texture2D barbosa_lima4;
    Texture2D amores;
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
    Texture2D caixa;
    Texture2D alfredo_lisboa1;
    Texture2D alfredo_lisboa2;
    Texture2D alfredo_lisboa3;
    Texture2D vital_de_oliveira;
    Texture2D sao_jorge1;
    Texture2D sao_jorge2;
    Texture2D travessa_tiradentes;
    Texture2D praca_tiradentes;
    Texture2D item_teste;
    Texture2D honglu;
    Texture2D queenOfHatred;
    Texture2D comadre1;
    Texture2D comadre2;
    Texture2D cabra;
    Texture2D ouro1;
    Texture2D ouro2;
    Texture2D figo;
    Texture2D moca;
    Texture2D emparedada1;

    Arvore_mapa *mapa;
    Arvore_mapa *local_atual;
    int chave_atual;

    Item *itensNaoPegos;

    Inventario *inventario;

    RayDialManager *dialogo;

    Lendas *lenda_atual;
    Lendas *lenda_local;
} Vars_structs_inicio_jogo;

void iniciar_jogo(Vars_structs_inicio_jogo *s);
void free_dados_jogo(Vars_structs_inicio_jogo *s);

#endif