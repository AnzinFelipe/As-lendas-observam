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

    bool em_hitbox;

    //Ruas
    Texture2D marco_zero;
    Texture2D comercial;
    Texture2D rio_branco;
    Texture2D marques_de_olinda1;
    Texture2D vigario_tenorio1;
    Texture2D vigario_tenorio2;
    Texture2D tomazina;
    Texture2D madre_de_deus;
    Texture2D paco_alfandega;
    Texture2D marques_de_olinda2;
    Texture2D marques_de_olinda3;
    Texture2D marques_de_olinda4;
    Texture2D cais_alfandega1;
    Texture2D cais_alfandega2;
    Texture2D la_ursa;
    Texture2D caranguejo;
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

    //Itens
    Texture2D item_teste;
    Texture2D honglu;
    Texture2D queenOfHatred;
    Texture2D saco;
    Texture2D marreta;
    Texture2D cara_la_ursa;
    Texture2D tesoura;
    Texture2D mingau;
    Texture2D isqueiro;
    Texture2D bolo;
    Texture2D bilhete;
    Texture2D barbeador;
    Texture2D cracha;

    //Lendas
    Texture2D comadre_local;
    Texture2D comadre1;
    Texture2D comadre2;
    Texture2D cabra_local;
    Texture2D cabra;
    Texture2D ouro1;
    Texture2D ouro2;
    Texture2D figo_local;
    Texture2D figo;
    Texture2D moca_local;
    Texture2D moca;
    Texture2D rachadura1;
    Texture2D rachadura2;
    Texture2D emparedada1;
    Texture2D emparedada2;
    Texture2D perna_local;
    Texture2D perna_cabeluda1;
    Texture2D perna_cabeluda2;

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