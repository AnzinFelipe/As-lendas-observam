#include "iniciar_liberar_jogo.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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

    s->marco_zero = LoadTexture("assets/images/locais/marco_zero.png");
    s->comercial = LoadTexture("assets/images/locais/comercial.png");
    s->rio_branco = LoadTexture("assets/images/locais/rio_branco.png");
    s->marques_de_olinda1 = LoadTexture("assets/images/locais/marques_de_olinda1.png");
    s->marques_de_olinda2 = LoadTexture("assets/images/locais/marques_de_olinda2.png");
    s->marques_de_olinda3 = LoadTexture("assets/images/locais/marques_de_olinda3.png");
    s->marques_de_olinda4 = LoadTexture("assets/images/locais/marques_de_olinda4.png");
    s->cais_alfandega1 = LoadTexture("assets/images/locais/cais_alfandega1.png");
    s->cais_alfandega2 = LoadTexture("assets/images/locais/cais_alfandega2.png");
    s->la_ursa = LoadTexture("assets/images/locais/la_ursa.png");
    s->caranguejo = LoadTexture("assets/images/locais/caranguejo.png");
    s->barbosa_lima1 = LoadTexture("assets/images/locais/barbosa_lima1.png");
    s->barbosa_lima2 = LoadTexture("assets/images/locais/barbosa_lima2.png");
    s->barbosa_lima3 = LoadTexture("assets/images/locais/barbosa_lima3.png");
    s->barbosa_lima4 = LoadTexture("assets/images/locais/barbosa_lima4.png");
    s->amores = LoadTexture("assets/images/locais/amores.png");
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
    s->caixa = LoadTexture("assets/images/locais/caixa.png");
    s->alfredo_lisboa1 = LoadTexture("assets/images/locais/alfredo_lisboa1.png");
    s->alfredo_lisboa2 = LoadTexture("assets/images/locais/alfredo_lisboa2.png");
    s->alfredo_lisboa3 = LoadTexture("assets/images/locais/alfredo_lisboa3.png");
    s->vital_de_oliveira = LoadTexture("assets/images/locais/vital_de_oliveira.png");
    s->sao_jorge1 = LoadTexture("assets/images/locais/sao_jorge1.png");
    s->sao_jorge2 = LoadTexture("assets/images/locais/sao_jorge2.png");
    s->travessa_tiradentes = LoadTexture("assets/images/locais/travessa_tiradentes.png");
    s->praca_tiradentes = LoadTexture("assets/images/locais/praca_tiradentes.png");

    //Inicializa itens

    s->item_teste = LoadTexture("assets/images/item_teste.jpg");
    s->honglu = LoadTexture("assets/images/Itens/Honglu.png");
    s->queenOfHatred = LoadTexture ("assets/images/Itens/QOH.png");

    //Inicializa lendas

    s->comadre1 = LoadTexture("assets/images/lendas/comadre_fulozinha1.png");
    s->comadre2 = LoadTexture("assets/images/lendas/comadre_fulozinha2.png");
    s->cabra = LoadTexture("assets/images/lendas/cabra_cabriola.png");
    GenTextureMipmaps(&s->cabra);
    SetTextureFilter(s->cabra, TEXTURE_FILTER_TRILINEAR);
    s->ouro1 = LoadTexture("assets/images/lendas/boca_de_ouro1.png");
    s->ouro2 = LoadTexture("assets/images/lendas/boca_de_ouro2.png");
    GenTextureMipmaps(&s->ouro2);
    SetTextureFilter(s->ouro2, TEXTURE_FILTER_TRILINEAR);
    s->moca = LoadTexture("assets/images/lendas/encanta_moca.png");
    GenTextureMipmaps(&s->moca);
    SetTextureFilter(s->moca, TEXTURE_FILTER_TRILINEAR);
    s->figo = LoadTexture("assets/images/lendas/papa_figo.png");
    GenTextureMipmaps(&s->figo);
    SetTextureFilter(s->figo, TEXTURE_FILTER_TRILINEAR);
    s->emparedada1 = LoadTexture("assets/images/lendas/emparedada1.png");
    GenTextureMipmaps(&s->emparedada1);
    SetTextureFilter(s->emparedada1, TEXTURE_FILTER_TRILINEAR);

    //Inicializa mapa

    s->mapa = NULL;

    inserir_local(&s->mapa, 500, "Marco Zero", s->marco_zero, NULL, (Rectangle){960, 600, 400, 200}, (Rectangle){240, 600, 400, 200}, (Rectangle){0});
    inserir_local(&s->mapa, 300, "Associação Comercial de Pernambuco", s->comercial, NULL, (Rectangle){240, 450, 200, 300}, (Rectangle){1160, 450, 200, 300}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 10, "Avenida Rio Branco", s->rio_branco, NULL, (Rectangle){0}, (Rectangle){590, 400, 350, 250}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 200, "Avenida Marquês de Olinda", s->marques_de_olinda1, NULL, (Rectangle){0}, (Rectangle){900, 400, 350, 250}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 201, "Avenida Marquês de Olinda", s->marques_de_olinda2, NULL, (Rectangle){0}, (Rectangle){750, 400, 350, 250}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 202, "Avenida Marquês de Olinda", s->marques_de_olinda3, NULL, (Rectangle){0}, (Rectangle){630, 400, 350, 250}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 203, "Avenida Marquês de Olinda", s->marques_de_olinda4, NULL, (Rectangle){0}, (Rectangle){650, 400, 350, 250}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 204, "Cais da Alfândega", s->cais_alfandega1, NULL, (Rectangle){0}, (Rectangle){650, 350, 350, 250}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 210, "Cais da Alfândega", s->cais_alfandega2, NULL, (Rectangle){400, 330, 250, 300}, (Rectangle){1000, 290, 290, 350}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 206, "La Ursa", s->la_ursa, NULL, (Rectangle){0}, (Rectangle){0}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 211, "Caranguejo", s->caranguejo, NULL, (Rectangle){0}, (Rectangle){0}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 350, "Avenida Barbosa Lima", s->barbosa_lima1, NULL, (Rectangle){0}, (Rectangle){590, 400, 350, 250}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 400, "Avenida Barbosa Lima", s->barbosa_lima2, NULL, (Rectangle){340, 350, 200, 300}, (Rectangle){1160, 400, 200, 300}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 355, "Avenida Barbosa Lima", s->barbosa_lima3, NULL, (Rectangle){0}, (Rectangle){590, 450, 350, 200}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 356, "Avenida Barbosa Lima", s->barbosa_lima4, NULL, (Rectangle){0}, (Rectangle){800, 400, 350, 250}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 357, "Rua dos Amores", s->amores, NULL, (Rectangle){0}, (Rectangle){0}, (Rectangle){540, 700, 500, 100});
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
    inserir_local(&s->mapa, 501, "Caixa Cultural", s->caixa, NULL, (Rectangle){0}, (Rectangle){1050, 350, 300, 400}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 502, "Avenida Alfredo Lisboa", s->alfredo_lisboa1, NULL, (Rectangle){0}, (Rectangle){590, 400, 350, 250}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 503, "Avenida Alfredo Lisboa", s->alfredo_lisboa2, NULL, (Rectangle){0}, (Rectangle){630, 400, 350, 250}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 504, "Avenida Alfredo Lisboa", s->alfredo_lisboa3, NULL, (Rectangle){0}, (Rectangle){750, 350, 350, 300}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 505, "Rua Vital de Oliveira", s->vital_de_oliveira, NULL, (Rectangle){0}, (Rectangle){590, 400, 350, 250}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 506, "Rua de São Jorge", s->sao_jorge1, NULL, (Rectangle){0}, (Rectangle){590, 400, 350, 250}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 507, "Rua de São Jorge", s->sao_jorge2, NULL, (Rectangle){0}, (Rectangle){700, 350, 350, 300}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 508, "Travessa Tiradentes", s->travessa_tiradentes, NULL, (Rectangle){0}, (Rectangle){650, 400, 350, 250}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 510, "Praça Tiradentes", s->praca_tiradentes, NULL, (Rectangle){0}, (Rectangle){0}, (Rectangle){540, 700, 500, 100});

    s->local_atual = NULL;
    s->chave_atual = 500;
    s->local_atual = buscar_local(s->mapa, s->chave_atual);

    //Inicializa itens no mapa

    s->itensNaoPegos = NULL;
    ColocarItemNoMapa(&s->itensNaoPegos, s->honglu, "Chibi Lu", (Vector2){100, 200}, "Um chibi Honglu, o que pode acontecer?...", 401);
    ColocarItemNoMapa(&s->itensNaoPegos, s->queenOfHatred, "Arcana Slave!", (Vector2){100, 90}, "Arcna Slave!!!!!!!", 401);

    //Inicializa inventario

    s->inventario = NULL;

    //Inicializa lendas

    s->dialogo = NULL;

    s->lenda_atual = NULL;
    s->lenda_local = NULL;
    inserir_lenda(&s->lenda_local, "Comadre Fulozinha", true, s->item_teste, s->comadre1, s->comadre2, (Rectangle){500, 300, 200, 200}, (Vector2){500, 300}, 510);
    Lendas *lenda = pegar_lenda_atual(s->lenda_local, 510);

    //Criar nós de diálogo
    RayDialNode *comadre_fala1 = CreateDialogueNode("fala1", "");
    RayDialNode *comadre_fala2 = CreateDialogueNode("fala2", "");
    RayDialNode *comadre_fala3 = CreateDialogueNode("fala3", "");
    RayDialNode *comadre_fala4 = CreateDialogueNode("fala4", "");

    //Criar componentes
    comadre_fala1->components = criarComp("Subconsciente", "--Você encontra um vulto escuro, o assobio está muito baixo, mas parece vir dele.--");
    comadre_fala2->components = criarComp("Subconsciente", "--Ele está observando, parece que não quer falar com Você.--");
    comadre_fala3->components = criarComp("Subconsciente", "--Talvez ele mude de ideia se você oferecer algum agrado.--");
    comadre_fala4->components = criarComp("Subconsciente", "--Ele não quer falar com você por enquanto.--");

    AddChoice(comadre_fala1, comadre_fala2);
    AddChoice(comadre_fala2, comadre_fala3);

    lenda->dialogo_raiz = comadre_fala1;
    lenda->dialogo_repetido = comadre_fala4;

    inserir_lenda(&s->lenda_local, "Cabra Cabriola", true, s->item_teste, s->cabra, s->cabra, (Rectangle){500, 300, 200, 200}, (Vector2){500, 300}, 422);
    lenda = pegar_lenda_atual(s->lenda_local, 422);

    RayDialNode *cabra_fala1 = CreateDialogueNode("fala1", "");
    RayDialNode *cabra_fala2 = CreateDialogueNode("fala2", "");
    RayDialNode *cabra_fala3 = CreateDialogueNode("fala3", "");
    RayDialNode *cabra_fala4 = CreateDialogueNode("fala4", "");
    RayDialNode *cabra_fala5 = CreateDialogueNode("fala5", "");
    RayDialNode *cabra_fala6 = CreateDialogueNode("fala6", "");
    RayDialNode *cabra_fala7 = CreateDialogueNode("fala7", "");

    cabra_fala1->components = criarComp("Subconsciente", "--Você se depara com uma cabra muito estranha, ela tem olhos e um bafo de fogo, não parece amigável.--");
    cabra_fala2->components = criarComp("Cabra Cabriola", "Eu sou a Cabra Cabriola. Que como...");
    cabra_fala3->components = criarComp("Cabra Cabriola", "...Poxa, um adulto? Pelo visto vou ficar morrendo de fome essa noite.");
    cabra_fala4->components = criarComp("Cabra Cabriola", "Saia daqui e não me incomode, estou de barriga vazia e sem paciência para falar com um adulto estranho.");
    cabra_fala5->components = criarComp("Subconsciente", "--Pelo visto, essa cabra precisa comer para falar com você.--");
    cabra_fala6->components = criarComp("Subconsciente", "--Obviamente você não vai dar o que ela quer. Tente mudar o paladar dela com uma comida apropriada.--");
    cabra_fala7->components = criarComp("Subconsciente", "--Ache alguma comida, daí então ela vai querer falar com você.--");

    AddChoice(cabra_fala1, cabra_fala2);
    AddChoice(cabra_fala2, cabra_fala3);
    AddChoice(cabra_fala3, cabra_fala4);
    AddChoice(cabra_fala4, cabra_fala5);
    AddChoice(cabra_fala5, cabra_fala6);

    lenda->dialogo_raiz = cabra_fala1;
    lenda->dialogo_repetido = cabra_fala7;

    inserir_lenda(&s->lenda_local, "Papa-figo", true, s->item_teste, s->figo, s->figo, (Rectangle){700, 450, 200, 200}, (Vector2){700, 450}, 452);
    lenda = pegar_lenda_atual(s->lenda_local, 452);

    RayDialNode *figo_fala1 = CreateDialogueNode("fala1", "");
    RayDialNode *figo_fala2 = CreateDialogueNode("fala2", "");
    RayDialNode *figo_fala3 = CreateDialogueNode("fala3", "");
    RayDialNode *figo_fala4 = CreateDialogueNode("fala4", "");
    RayDialNode *figo_fala5 = CreateDialogueNode("fala5", "");
    RayDialNode *figo_fala6 = CreateDialogueNode("fala6", "");
    RayDialNode *figo_fala7 = CreateDialogueNode("fala7", "");

    figo_fala1->components = criarComp("Subconsciente", "--Você se encontra com um velho corcunda com uma aparência péssima, parece que está querendo algum favor seu.--");
    figo_fala2->components = criarComp("Papa-figo", "Boa noite, eu... estava perambulando por essas ruas e acabei me descuidando, perdi uma coisa muuuito importante.");
    figo_fala3->components = criarComp("Papa-figo", "Meu saco de pano... deixei cair em algum canto aqui no Recife Antigo, se você o achar, poderia trazer para mim?");
    figo_fala4->components = criarComp("Papa-figo", "Vou ficar muuuito agradecido, sem ele não posso curar minha doença.");
    figo_fala5->components = criarComp("Subconsciente", "--Você sabe o que ele faz com esse saco de pano. Você não pode simplesmente devolver para ele.--");
    figo_fala6->components = criarComp("Subconsciente", "--Mas... talvez ele te dê algo em troca, pense numa solução para esse dilema.--");
    figo_fala7->components = criarComp("Papa-figo", "--Já achou o meu saco de pano? Não devo ter deixado cair tão longe daqui.--");

    AddChoice(figo_fala1, figo_fala2);
    AddChoice(figo_fala2, figo_fala3);
    AddChoice(figo_fala3, figo_fala4);
    AddChoice(figo_fala4, figo_fala5);
    AddChoice(figo_fala5, figo_fala6);

    lenda->dialogo_raiz = figo_fala1;
    lenda->dialogo_repetido = figo_fala7;

    inserir_lenda(&s->lenda_local, "Encanta Moça", true, s->item_teste, s->moca, s->moca, (Rectangle){500, 300, 200, 200}, (Vector2){500, 300}, 211);
    lenda = pegar_lenda_atual(s->lenda_local, 211);

    RayDialNode *moca_fala1 = CreateDialogueNode("fala1", "");
    RayDialNode *moca_fala2 = CreateDialogueNode("fala2", "");
    RayDialNode *moca_fala3 = CreateDialogueNode("fala3", "");
    RayDialNode *moca_fala4 = CreateDialogueNode("fala4", "");
    RayDialNode *moca_fala5 = CreateDialogueNode("fala5", "");
    RayDialNode *moca_fala6 = CreateDialogueNode("fala6", "");

    moca_fala1->components = criarComp("Subconsciente", "--Você se encontra com uma moça muito encantadora ao lado de um grande caranguejo.--");
    moca_fala2->components = criarComp("Subconsciente", "--Você sente que, em outra circunstância, cairia no encanto dela. Não há dúvidas.--");
    moca_fala3->components = criarComp("Encanta Moça", "Este caranguejo me lembra o mangue. Meu querido mangue.");
    moca_fala4->components = criarComp("Encanta Moça", "Não sei o que me fez vir para cá, mas preciso voltar pro lugar de onde vim.");
    moca_fala5->components = criarComp("Subconsciente", "--Talvez você possa ajudá-la a sair daqui, mas como?--");
    moca_fala6->components = criarComp("Encanta Moça", "Quero voltar pro meu mangue...");

    AddChoice(moca_fala1, moca_fala2);
    AddChoice(moca_fala2, moca_fala3);
    AddChoice(moca_fala3, moca_fala4);
    AddChoice(moca_fala4, moca_fala5);

    lenda->dialogo_raiz = moca_fala1;
    lenda->dialogo_repetido = moca_fala6;
}

void free_dados_jogo(Vars_structs_inicio_jogo *s){
    liberar_arvore(&s->mapa);
    liberar_inventario(&s->inventario);
    LiberarItens_j(&s->inventario);
    LiberarItens_i(&s->itensNaoPegos);
    liberar_lendas(&s->lenda_local);
    UnloadTexture(s->marco_zero);
    UnloadTexture(s->comercial);
    UnloadTexture(s->barbosa_lima1);
    UnloadTexture(s->barbosa_lima2);
    UnloadTexture(s->barbosa_lima3);
    UnloadTexture(s->barbosa_lima4);
    UnloadTexture(s->amores);
    UnloadTexture(s->bom_jesus1);
    UnloadTexture(s->bom_jesus2);
    UnloadTexture(s->arsenal);
    UnloadTexture(s->frevo);
    UnloadTexture(s->rodrigues_mendes);
    UnloadTexture(s->parede);
    UnloadTexture(s->guia);
    UnloadTexture(s->observatorio1);
    UnloadTexture(s->observatorio2);
    UnloadTexture(s->cais_apolo);
    UnloadTexture(s->cesar_brum);
    UnloadTexture(s->bom_jesus3);
    UnloadTexture(s->malakoff);
    UnloadTexture(s->caixa);
    UnloadTexture(s->alfredo_lisboa1);
    UnloadTexture(s->alfredo_lisboa2);
    UnloadTexture(s->alfredo_lisboa3);
    UnloadTexture(s->vital_de_oliveira);
    UnloadTexture(s->sao_jorge1);
    UnloadTexture(s->sao_jorge2);
    UnloadTexture(s->travessa_tiradentes);
    UnloadTexture(s->praca_tiradentes);
    UnloadTexture(s->honglu);
    UnloadTexture(s->queenOfHatred);
    UnloadTexture(s->comadre1);
    UnloadTexture(s->comadre2);
    UnloadTexture(s->cabra);
    UnloadTexture(s->ouro1);
    UnloadTexture(s->ouro2);
    UnloadTexture(s->emparedada1);
    UnloadTexture(s->moca);
    UnloadTexture(s->figo);
    UnloadTexture(s->item_teste);

    UnloadMusicStream(s->pink);
    CloseAudioDevice();
}