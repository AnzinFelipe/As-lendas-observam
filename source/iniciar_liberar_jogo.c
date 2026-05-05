#include "iniciar_liberar_jogo.h"
#include <string.h>
#include <stdlib.h>

void iniciar_jogo(Vars_structs_inicio_jogo *s){
    //Inicializa tela

    s->tela = LoadRenderTexture(1600, 900);
    SetTextureFilter(s->tela.texture, TEXTURE_FILTER_BILINEAR);

    if (!IsAudioDeviceReady()) {
        InitAudioDevice();
    }

    //Inicializa musica

    s->pink = LoadMusicStream("assets/musics/Pink.mp3");
    PlayMusicStream(s->pink);

    //Inicializa locais do Recife

    s->comercial = LoadTexture("assets/images/locais/comercial.png");
    s->marco_zero = LoadTexture("assets/images/locais/marco_zero.png");
    s->barbosa_lima1 = LoadTexture("assets/images/locais/barbosa_lima1.png");
    s->barbosa_lima2 = LoadTexture("assets/images/locais/barbosa_lima2.png");
    s->bom_jesus1 = LoadTexture("assets/images/locais/bom_jesus1.png");
    s->bom_jesus2 = LoadTexture("assets/images/locais/bom_jesus2.png");
    s->bom_jesus3 = LoadTexture("assets/images/locais/bom_jesus3.png");
    s->arsenal = LoadTexture("assets/images/locais/arsenal.png");
    s->frevo = LoadTexture("assets/images/locais/frevo.png");
    s->rodrigues_mendes = LoadTexture("assets/images/locais/rodrigues_mendes.png");
    s->parede = LoadTexture("assets/images/locais/parede.png");
    s->guia = LoadTexture("assets/images/locais/guia.png");
    s->observatorio1 = LoadTexture("assets/images/locais/observatorio1.png");
    s->observatorio2 = LoadTexture("assets/images/locais/observatorio2.png");
    s->cais_apolo = LoadTexture("assets/images/locais/cais_apolo.png");
    s->cesar_brum = LoadTexture("assets/images/locais/cesar_brum.png");
    s->malakoff = LoadTexture("assets/images/locais/malakoff.png");

    //Inicializa itens

    s->item_teste = LoadTexture("assets/images/item_teste.jpg");
    s->honglu = LoadTexture("assets/images/Itens/Honglu.png");
    s->queenOfHatred = LoadTexture ("assets/images/Itens/QOH.png");

    //Inicializa mapa

    s->mapa = NULL;

    inserir_local(&s->mapa, 500, "Marco Zero", s->marco_zero, NULL, (Rectangle){960, 600, 400, 200}, (Rectangle){240, 600, 400, 200}, (Rectangle){0});
    inserir_local(&s->mapa, 300, "Associação Comercial de Pernambuco", s->comercial, NULL, (Rectangle){240, 450, 200, 300}, (Rectangle){1160, 450, 200, 300}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 350, "Avenida Barbosa Lima", s->barbosa_lima1, NULL, (Rectangle){0}, (Rectangle){590, 400, 350, 250}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 400, "Avenida Barbosa Lima", s->barbosa_lima2, NULL, (Rectangle){340, 350, 200, 300}, (Rectangle){1160, 400, 200, 300}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 401, "Rua do Bom Jesus", s->bom_jesus1, NULL, (Rectangle){0}, (Rectangle){610, 350, 350, 250}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 402, "Rua do Bom Jesus", s->bom_jesus2, NULL, (Rectangle){0}, (Rectangle){610, 350, 350, 250}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 450, "Praça do Arsenal", s->arsenal, NULL, (Rectangle){240, 360, 200, 400}, (Rectangle){1160, 360, 200, 400}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 420, "Paço do Frevo", s->frevo, NULL, (Rectangle){0}, (Rectangle){1160, 300, 200, 400}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 425, "Rua Barão Rodrigues Mendes", s->rodrigues_mendes, NULL, (Rectangle){440, 350, 200, 300}, (Rectangle){1110, 360, 250, 300}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 422, "Parede", s->parede, NULL, (Rectangle){0}, (Rectangle){0}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 426, "Rua da Guia", s->guia, NULL, (Rectangle){0}, (Rectangle){610, 350, 350, 250}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 427, "Rua do Observatório", s->observatorio1, NULL, (Rectangle){0}, (Rectangle){590, 350, 350, 250}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 428, "Rua do Observatório", s->observatorio2, NULL, (Rectangle){0}, (Rectangle){640, 400, 350, 250}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 429, "Avenida Cais do Apolo", s->cais_apolo, NULL, (Rectangle){0}, (Rectangle){610, 350, 350, 250}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 430, "CESAR Brum", s->cesar_brum, NULL, (Rectangle){0}, (Rectangle){0}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 451, "Rua do Bom Jesus", s->bom_jesus3, NULL, (Rectangle){0}, (Rectangle){690, 350, 350, 250}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 452, "Torre Malakoff", s->malakoff, NULL, (Rectangle){0}, (Rectangle){0}, (Rectangle){540, 700, 500, 100});

    s->local_atual = NULL;
    s->chave_atual = 500;
    s->local_atual = buscar_local(s->mapa, s->chave_atual);

    //Inicializa itens no mapa

    s->itensNaoPegos = NULL;
    ColocarItemNoMapa(&s->itensNaoPegos, s->honglu, "Chibi Lu", (Vector2){100, 200}, "Um chibi Honglu, o que pode acontecer?...", 401);
    ColocarItemNoMapa(&s->itensNaoPegos, s->queenOfHatred, "Arcana Slave!", (Vector2){100, 90}, "Arcna Slave!!!!!!!", 401);

    //Inicializa inventario

    s->inventario = NULL;
}