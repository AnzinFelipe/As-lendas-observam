#include "iniciar_liberar_jogo.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lendas.h"
#include "raydial.h"

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

    //Para mudar estilo do mouse

    s->em_hitbox = false;

    //Inicializa locais do Recife

    s->enfeite = LoadTexture("assets/images/enfeite.png");
    s->marco_zero = LoadTexture("assets/images/locais/marco_zero.png");
    s->comercial = LoadTexture("assets/images/locais/comercial.png");
    s->rio_branco = LoadTexture("assets/images/locais/rio_branco.png");
    s->marques_de_olinda1 = LoadTexture("assets/images/locais/marques_de_olinda1.png");
    s->vigario_tenorio1 = LoadTexture("assets/images/locais/vigario_tenorio1.png");
    s->vigario_tenorio2 = LoadTexture("assets/images/locais/vigario_tenorio2.png");
    s->tomazina = LoadTexture("assets/images/locais/tomazina.png");
    s->madre_de_deus = LoadTexture("assets/images/locais/madre_de_deus.png");
    s->paco_alfandega = LoadTexture("assets/images/locais/paco_alfandega.png");
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

    s->saco = LoadTexture("assets/images/Itens/saco.png");
    GenTextureMipmaps(&s->saco);
    SetTextureFilter(s->saco, TEXTURE_FILTER_TRILINEAR);
    s->cara_la_ursa = LoadTexture("assets/images/Itens/cara_la_ursa.png");
    GenTextureMipmaps(&s->cara_la_ursa);
    SetTextureFilter(s->cara_la_ursa, TEXTURE_FILTER_TRILINEAR);
    s->marreta = LoadTexture("assets/images/Itens/marreta.png");
    GenTextureMipmaps(&s->marreta);
    SetTextureFilter(s->marreta, TEXTURE_FILTER_TRILINEAR);
    s->tesoura = LoadTexture("assets/images/Itens/tesoura.png");
    GenTextureMipmaps(&s->tesoura);
    SetTextureFilter(s->tesoura, TEXTURE_FILTER_TRILINEAR);
    s->bolo = LoadTexture("assets/images/Itens/bolo.png");
    GenTextureMipmaps(&s->bolo);
    SetTextureFilter(s->bolo, TEXTURE_FILTER_TRILINEAR);
    s->mingau = LoadTexture("assets/images/Itens/mingau.png");
    GenTextureMipmaps(&s->mingau);
    SetTextureFilter(s->mingau, TEXTURE_FILTER_TRILINEAR);
    s->bilhete = LoadTexture("assets/images/Itens/bilhete.png");
    GenTextureMipmaps(&s->bilhete);
    SetTextureFilter(s->bilhete, TEXTURE_FILTER_TRILINEAR);
    s->barbeador = LoadTexture("assets/images/Itens/barbeador.png");
    GenTextureMipmaps(&s->barbeador);
    SetTextureFilter(s->barbeador, TEXTURE_FILTER_TRILINEAR);
    s->isqueiro = LoadTexture("assets/images/Itens/isqueiro.png");
    GenTextureMipmaps(&s->isqueiro);
    SetTextureFilter(s->isqueiro, TEXTURE_FILTER_TRILINEAR);
    s->cracha = LoadTexture("assets/images/Itens/cracha.png");
    GenTextureMipmaps(&s->cracha);
    SetTextureFilter(s->cracha, TEXTURE_FILTER_TRILINEAR);

    //Inicializa lendas

    s->comadre_local = LoadTexture("assets/images/lendas/comadre_local.png");
    s->comadre1 = LoadTexture("assets/images/lendas/comadre_fulozinha1.png");
    s->comadre2 = LoadTexture("assets/images/lendas/comadre_fulozinha2.png");
    s->cabra_local = LoadTexture("assets/images/lendas/cabra_local.png");
    s->cabra = LoadTexture("assets/images/lendas/cabra_cabriola.png");
    GenTextureMipmaps(&s->cabra);
    SetTextureFilter(s->cabra, TEXTURE_FILTER_TRILINEAR);
    s->ouro1 = LoadTexture("assets/images/lendas/boca_de_ouro1.png");
    s->ouro2 = LoadTexture("assets/images/lendas/boca_de_ouro2.png");
    GenTextureMipmaps(&s->ouro2);
    SetTextureFilter(s->ouro2, TEXTURE_FILTER_TRILINEAR);
    s->moca_local = LoadTexture("assets/images/lendas/moca_local.png");
    s->moca = LoadTexture("assets/images/lendas/encanta_moca.png");
    GenTextureMipmaps(&s->moca);
    SetTextureFilter(s->moca, TEXTURE_FILTER_TRILINEAR);
    s->figo_local = LoadTexture("assets/images/lendas/figo_local.png");
    s->figo = LoadTexture("assets/images/lendas/papa_figo.png");
    GenTextureMipmaps(&s->figo);
    SetTextureFilter(s->figo, TEXTURE_FILTER_TRILINEAR);
    s->rachadura1 = LoadTexture("assets/images/lendas/rachadura1.png");
    s->rachadura2 = LoadTexture("assets/images/lendas/rachadura2.png");
    s->emparedada1 = LoadTexture("assets/images/lendas/emparedada1.png");
    GenTextureMipmaps(&s->emparedada1);
    SetTextureFilter(s->emparedada1, TEXTURE_FILTER_TRILINEAR);
    s->emparedada2 = LoadTexture("assets/images/lendas/emparedada2.png");
    GenTextureMipmaps(&s->emparedada2);
    SetTextureFilter(s->emparedada2, TEXTURE_FILTER_TRILINEAR);
    s->perna_local = LoadTexture("assets/images/lendas/perna_local.png");
    s->perna_cabeluda1 = LoadTexture("assets/images/lendas/perna_cabeluda1.png");
    s->perna_cabeluda2 = LoadTexture("assets/images/lendas/perna_cabeluda2.png");

    //Inicializa mapa

    s->mapa = NULL;

    inserir_local(&s->mapa, 500, "Marco Zero", s->marco_zero, (Rectangle){960, 600, 400, 200}, (Rectangle){240, 600, 400, 200}, (Rectangle){0});
    inserir_local(&s->mapa, 300, "Associação Comercial de Pernambuco", s->comercial, (Rectangle){240, 450, 200, 300}, (Rectangle){1160, 450, 200, 300}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 10, "Avenida Rio Branco", s->rio_branco, (Rectangle){0}, (Rectangle){590, 400, 350, 250}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 200, "Avenida Marquês de Olinda", s->marques_de_olinda1, (Rectangle){400, 400, 350, 250}, (Rectangle){900, 400, 350, 250}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 100, "Rua Vigário Tenório", s->vigario_tenorio1, (Rectangle){0}, (Rectangle){650, 370, 350, 250}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 101, "Rua Vigário Tenório", s->vigario_tenorio2, (Rectangle){0}, (Rectangle){700, 300, 350, 300}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 102, "Rua Tomazina", s->tomazina, (Rectangle){0}, (Rectangle){650, 400, 350, 250}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 103, "Rua Madre de Deus", s->madre_de_deus, (Rectangle){0}, (Rectangle){500, 350, 350, 300}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 104, "Paço Alfândega", s->paco_alfandega, (Rectangle){0}, (Rectangle){0}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 201, "Avenida Marquês de Olinda", s->marques_de_olinda2, (Rectangle){0}, (Rectangle){750, 400, 350, 250}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 202, "Avenida Marquês de Olinda", s->marques_de_olinda3, (Rectangle){0}, (Rectangle){630, 400, 350, 250}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 203, "Avenida Marquês de Olinda", s->marques_de_olinda4, (Rectangle){0}, (Rectangle){650, 400, 350, 250}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 204, "Cais da Alfândega", s->cais_alfandega1, (Rectangle){0}, (Rectangle){650, 350, 350, 250}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 210, "Cais da Alfândega", s->cais_alfandega2, (Rectangle){400, 330, 250, 300}, (Rectangle){1000, 290, 290, 350}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 206, "La Ursa", s->la_ursa, (Rectangle){0}, (Rectangle){0}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 211, "Caranguejo", s->caranguejo, (Rectangle){0}, (Rectangle){0}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 350, "Avenida Barbosa Lima", s->barbosa_lima1, (Rectangle){0}, (Rectangle){590, 400, 350, 250}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 400, "Avenida Barbosa Lima", s->barbosa_lima2, (Rectangle){340, 350, 200, 300}, (Rectangle){1160, 400, 200, 300}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 355, "Avenida Barbosa Lima", s->barbosa_lima3, (Rectangle){0}, (Rectangle){590, 450, 350, 200}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 356, "Avenida Barbosa Lima", s->barbosa_lima4, (Rectangle){0}, (Rectangle){800, 400, 350, 250}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 357, "Rua dos Amores", s->amores, (Rectangle){0}, (Rectangle){0}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 401, "Rua do Bom Jesus", s->bom_jesus1, (Rectangle){0}, (Rectangle){610, 350, 350, 250}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 402, "Rua do Bom Jesus", s->bom_jesus2, (Rectangle){0}, (Rectangle){610, 350, 350, 250}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 450, "Praça do Arsenal", s->arsenal, (Rectangle){240, 360, 200, 400}, (Rectangle){1160, 360, 200, 400}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 420, "Paço do Frevo", s->frevo, (Rectangle){0}, (Rectangle){1160, 300, 200, 400}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 425, "Rua Barão Rodrigues Mendes", s->rodrigues_mendes, (Rectangle){440, 350, 200, 300}, (Rectangle){1110, 360, 250, 300}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 422, "Parede", s->parede, (Rectangle){0}, (Rectangle){0}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 426, "Rua da Guia", s->guia, (Rectangle){0}, (Rectangle){610, 350, 350, 250}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 427, "Rua do Observatório", s->observatorio1, (Rectangle){0}, (Rectangle){590, 350, 350, 250}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 428, "Rua do Observatório", s->observatorio2, (Rectangle){0}, (Rectangle){640, 400, 350, 250}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 429, "Avenida Cais do Apolo", s->cais_apolo, (Rectangle){0}, (Rectangle){610, 350, 350, 250}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 430, "CESAR Brum", s->cesar_brum, (Rectangle){0}, (Rectangle){0}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 451, "Rua do Bom Jesus", s->bom_jesus3, (Rectangle){0}, (Rectangle){690, 350, 350, 250}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 452, "Torre Malakoff", s->malakoff, (Rectangle){0}, (Rectangle){0}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 501, "Caixa Cultural", s->caixa, (Rectangle){0}, (Rectangle){1050, 350, 300, 400}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 502, "Avenida Alfredo Lisboa", s->alfredo_lisboa1, (Rectangle){0}, (Rectangle){590, 400, 350, 250}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 503, "Avenida Alfredo Lisboa", s->alfredo_lisboa2, (Rectangle){0}, (Rectangle){630, 400, 350, 250}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 504, "Avenida Alfredo Lisboa", s->alfredo_lisboa3, (Rectangle){0}, (Rectangle){750, 350, 350, 300}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 505, "Rua Vital de Oliveira", s->vital_de_oliveira, (Rectangle){0}, (Rectangle){590, 400, 350, 250}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 506, "Rua de São Jorge", s->sao_jorge1, (Rectangle){0}, (Rectangle){590, 400, 350, 250}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 507, "Rua de São Jorge", s->sao_jorge2, (Rectangle){0}, (Rectangle){700, 350, 350, 300}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 508, "Travessa Tiradentes", s->travessa_tiradentes, (Rectangle){0}, (Rectangle){650, 400, 350, 250}, (Rectangle){540, 700, 500, 100});
    inserir_local(&s->mapa, 510, "Praça Tiradentes", s->praca_tiradentes, (Rectangle){0}, (Rectangle){0}, (Rectangle){540, 700, 500, 100});

    s->local_atual = NULL;
    s->chave_atual = 500;
    s->local_atual = buscar_local(s->mapa, s->chave_atual);

    //Inicializa itens no mapa

    s->itensNaoPegos = NULL;
    ColocarItemNoMapa(&s->itensNaoPegos, s->saco, "Saco de pano", (Vector2){200, 200}, "Um saco de pano velho, parece que tem algo dentro...", 357, 1);
    ColocarItemNoMapa(&s->itensNaoPegos, s->marreta, "Marreta", (Vector2){300, 200}, "Uma marreta de ferro, parece pesada.", 450, 10);
    ColocarItemNoMapa(&s->itensNaoPegos, s->cara_la_ursa, "Cara de La Ursa", (Vector2){400, 200}, "Uma máscara com a cara da La Ursa, parece que tem um cheiro estranho...", 206, 9);
    //Inicializa inventario

    s->inventario = NULL;

    // Inicializa sistema de drag do inventário
    s->itemSelecionado = NULL;
    s->arrastandoItem = false;

    //Inicializa lendas

    s->dialogo = NULL;

    s->lenda_atual = NULL;
    s->lenda_local = NULL;
    inserir_lenda(&s->lenda_local, "Comadre Fulozinha", true, s->comadre_local, s->comadre1, s->comadre2, (Rectangle){840, 320, 130, 200}, (Vector2){200, 20}, s->bilhete, "Mingau", 510);
    Lendas *lenda = pegar_lenda_atual(s->lenda_local, 510);

    //Criar nós de diálogo
    RayDialNode *comadre_fala1 = CreateDialogueNode("fala1", "");
    RayDialNode *comadre_fala2 = CreateDialogueNode("fala2", "");
    RayDialNode *comadre_fala3 = CreateDialogueNode("fala3", "");
    RayDialNode *comadre_fala4 = CreateDialogueNode("fala4", "");
    RayDialNode *comadre_fala5 = CreateDialogueNode("fala5", "");
    RayDialNode *comadre_fala6 = CreateDialogueNode("fala6", "");
    RayDialNode *comadre_fala7 = CreateDialogueNode("fala7", "");
    RayDialNode *comadre_fala8 = CreateDialogueNode("fala8", "");
    RayDialNode *comadre_fala9 = CreateDialogueNode("fala9", "");
    RayDialNode *comadre_fala10 = CreateDialogueNode("fala10", "");

    //Criar componentes
    comadre_fala1->components = criarComp("Subconsciente", "--Você encontra um vulto escuro, o assobio está muito baixo, mas parece vir dele.--");
    comadre_fala2->components = criarComp("Subconsciente", "--Ele está observando, parece que não quer falar com Você.--");
    comadre_fala3->components = criarComp("Subconsciente", "--Talvez ele mude de ideia se você oferecer algum agrado.--");
    comadre_fala4->components = criarComp("Subconsciente", "--Ele não quer falar com você por enquanto.--");
    comadre_fala5->components = criarComp(lenda->nome, "Um mingau!! Muito obrigada!!");
    comadre_fala6->components = criarComp(lenda->nome, "Tu tá perdido, não é? Como agradecimento por não maltratar a mata desse lugar e me oferecer um mingau, posso te ajudar te dizendo onde passar a noite.");
    comadre_fala7->components = criarComp(lenda->nome, "Sabe o prédio do CESAR Brum? Não sei o motivo, mas parece que ele tá aberto. Se tu conseguir passar das catracas de algum jeito até conseguiria dormir lá.");
    comadre_fala8->components = criarComp(lenda->nome, "A única coisa que tenho aqui comigo é um bilhete de passeio de catamarã, pode ficar, talvez te ajude de alguma forma.");
    comadre_fala9->components = criarComp("Subconsciente", "--Com certeza não vai dar para você sair daqui de catamarã, mas talvez alguém precise disso, vá procurar.--");
    comadre_fala10->components = criarComp(lenda->nome, "Obrigada pelo mingau, tava muito gostoso.");

    AddChoice(comadre_fala1, comadre_fala2);
    AddChoice(comadre_fala2, comadre_fala3);
    AddChoice(comadre_fala5, comadre_fala6);
    AddChoice(comadre_fala6, comadre_fala7);
    AddChoice(comadre_fala7, comadre_fala8);
    AddChoice(comadre_fala8, comadre_fala9);

    lenda->dialogo_raiz = comadre_fala1;
    lenda->dialogo_repetido = comadre_fala4;
    lenda->dialogo_final = comadre_fala5;
    lenda->dialogo_final_repetido = comadre_fala10;

    inserir_lenda(&s->lenda_local, "Cabra Cabriola", true, s->cabra_local, s->cabra, s->cabra, (Rectangle){250, 330, 220, 350}, (Vector2){240, 0}, s->tesoura, "Bolo de rolo", 422);
    lenda = pegar_lenda_atual(s->lenda_local, 422);

    RayDialNode *cabra_fala1 = CreateDialogueNode("fala1", "");
    RayDialNode *cabra_fala2 = CreateDialogueNode("fala2", "");
    RayDialNode *cabra_fala3 = CreateDialogueNode("fala3", "");
    RayDialNode *cabra_fala4 = CreateDialogueNode("fala4", "");
    RayDialNode *cabra_fala5 = CreateDialogueNode("fala5", "");
    RayDialNode *cabra_fala6 = CreateDialogueNode("fala6", "");
    RayDialNode *cabra_fala7 = CreateDialogueNode("fala7", "");
    RayDialNode *cabra_fala8 = CreateDialogueNode("fala8", "");
    RayDialNode *cabra_fala9 = CreateDialogueNode("fala9", "");
    RayDialNode *cabra_fala10 = CreateDialogueNode("fala10", "");
    RayDialNode *cabra_fala11 = CreateDialogueNode("fala11", "");
    RayDialNode *cabra_fala12 = CreateDialogueNode("fala12", "");

    cabra_fala1->components = criarComp("Subconsciente", "--Você se depara com uma cabra muito estranha, ela tem olhos e um bafo de fogo, não parece amigável.--");
    cabra_fala2->components = criarComp(lenda->nome, "Eu sou a Cabra Cabriola. Que como...");
    cabra_fala3->components = criarComp(lenda->nome, "...Poxa, um adulto? Pelo visto vou ficar morrendo de fome essa noite.");
    cabra_fala4->components = criarComp(lenda->nome, "Saia daqui e não me incomode, estou de barriga vazia e sem paciência para falar com um adulto estranho.");
    cabra_fala5->components = criarComp("Subconsciente", "--Pelo visto, essa cabra precisa comer para falar com você.--");
    cabra_fala6->components = criarComp("Subconsciente", "--Obviamente você não vai dar o que ela quer. Tente mudar o paladar dela com uma comida apropriada.--");
    cabra_fala7->components = criarComp("Subconsciente", "--Ache alguma comida, daí então ela vai querer falar com você.--");
    cabra_fala8->components = criarComp(lenda->nome, "Hmmmm o que é isso? Até que parece gostoso, acho que posso experimentar...");
    cabra_fala9->components = criarComp(lenda->nome, "Tá, isso é bem melhor do que aquilo que ando devorando minha vida inteira...");
    cabra_fala10->components = criarComp(lenda->nome, "Toma isso daqui, uma tesoura. Eu costumava roubar do velho feioso que tá por aqui por perto. Não vou precisar mais, já que você ampliou meu paladar.");
    cabra_fala11->components = criarComp("Subconsciente", "--É isso! Com essa tesoura você vai poder fazer um furo no saco de pano daquele velho antes de entregá-lo.--");
    cabra_fala12->components = criarComp(lenda->nome, "Por acaso tu não teria mais daquele bolo aí pra mim, né?");

    AddChoice(cabra_fala1, cabra_fala2);
    AddChoice(cabra_fala2, cabra_fala3);
    AddChoice(cabra_fala3, cabra_fala4);
    AddChoice(cabra_fala4, cabra_fala5);
    AddChoice(cabra_fala5, cabra_fala6);
    AddChoice(cabra_fala8, cabra_fala9);
    AddChoice(cabra_fala9, cabra_fala10);
    AddChoice(cabra_fala10, cabra_fala11);

    lenda->dialogo_raiz = cabra_fala1;
    lenda->dialogo_repetido = cabra_fala7;
    lenda->dialogo_final = cabra_fala8;
    lenda->dialogo_final_repetido = cabra_fala12;

    inserir_lenda(&s->lenda_local, "Papa-figo", true, s->figo_local, s->figo, s->figo, (Rectangle){730, 500, 150, 130}, (Vector2){200, 0}, s->barbeador, "Saco de pano", 452);
    lenda = pegar_lenda_atual(s->lenda_local, 452);

    RayDialNode *figo_fala1 = CreateDialogueNode("fala1", "");
    RayDialNode *figo_fala2 = CreateDialogueNode("fala2", "");
    RayDialNode *figo_fala3 = CreateDialogueNode("fala3", "");
    RayDialNode *figo_fala4 = CreateDialogueNode("fala4", "");
    RayDialNode *figo_fala5 = CreateDialogueNode("fala5", "");
    RayDialNode *figo_fala6 = CreateDialogueNode("fala6", "");
    RayDialNode *figo_fala7 = CreateDialogueNode("fala7", "");
    RayDialNode *figo_fala8 = CreateDialogueNode("fala8", "");
    RayDialNode *figo_fala9 = CreateDialogueNode("fala9", "");
    RayDialNode *figo_fala10 = CreateDialogueNode("fala10", "");
    RayDialNode *figo_fala11 = CreateDialogueNode("fala11", "");
    RayDialNode *figo_fala12 = CreateDialogueNode("fala12", "");

    figo_fala1->components = criarComp("Subconsciente", "--Você se encontra com um velho corcunda com uma aparência péssima, parece que está querendo algum favor seu.--");
    figo_fala2->components = criarComp(lenda->nome, "Boa noite, eu... estava perambulando por essas ruas e acabei me descuidando, perdi uma coisa muuuito importante.");
    figo_fala3->components = criarComp(lenda->nome, "Meu saco de pano... deixei cair em algum canto aqui no Recife Antigo, se você o achar, poderia trazer para mim?");
    figo_fala4->components = criarComp(lenda->nome, "Vou ficar muuuito agradecido, sem ele não posso curar minha doença.");
    figo_fala5->components = criarComp("Subconsciente", "--Você sabe o que ele faz com esse saco de pano. Você não pode simplesmente devolver para ele.--");
    figo_fala6->components = criarComp("Subconsciente", "--Mas... talvez ele te dê algo em troca, pense numa solução para esse dilema.--");
    figo_fala7->components = criarComp(lenda->nome, "Já achou o meu saco de pano? Não devo ter deixado cair tão longe daqui.");
    figo_fala8->components = criarComp(lenda->nome, "E não é que você realmente achou ele? Muuuito obrigado jovem.");
    figo_fala9->components = criarComp(lenda->nome, "Já estava preocupado com minha doença, se eu não comer fígado uma hora ou outra vou me tornar um lobisomem.");
    figo_fala10->components = criarComp(lenda->nome, "Isso não vai mais ocorrer graças a você... pode ficar com o meu barbeador.");
    figo_fala11->components = criarComp("Subconsciente", "--...talvez isso sirva para alguma coisa.--");
    figo_fala12->components = criarComp("Subconsciente", "--Melhor não falar mais com ele. Na próxima vez, vai saber se ele virou um lobisomem...--");

    AddChoice(figo_fala1, figo_fala2);
    AddChoice(figo_fala2, figo_fala3);
    AddChoice(figo_fala3, figo_fala4);
    AddChoice(figo_fala4, figo_fala5);
    AddChoice(figo_fala5, figo_fala6);
    AddChoice(figo_fala8, figo_fala9);
    AddChoice(figo_fala9, figo_fala10);
    AddChoice(figo_fala10, figo_fala11);

    lenda->dialogo_raiz = figo_fala1;
    lenda->dialogo_repetido = figo_fala7;
    lenda->dialogo_final = figo_fala8;
    lenda->dialogo_final_repetido = figo_fala12;

    inserir_lenda(&s->lenda_local, "Encanta Moça", true, s->moca_local, s->moca, s->moca, (Rectangle){1000, 420, 150, 200}, (Vector2){200, 0}, s->bolo, "Bilhete de catamarã", 211);
    lenda = pegar_lenda_atual(s->lenda_local, 211);

    RayDialNode *moca_fala1 = CreateDialogueNode("fala1", "");
    RayDialNode *moca_fala2 = CreateDialogueNode("fala2", "");
    RayDialNode *moca_fala3 = CreateDialogueNode("fala3", "");
    RayDialNode *moca_fala4 = CreateDialogueNode("fala4", "");
    RayDialNode *moca_fala5 = CreateDialogueNode("fala5", "");
    RayDialNode *moca_fala6 = CreateDialogueNode("fala6", "");
    RayDialNode *moca_fala7 = CreateDialogueNode("fala7", "");
    RayDialNode *moca_fala8 = CreateDialogueNode("fala8", "");
    RayDialNode *moca_fala9 = CreateDialogueNode("fala9", "");
    RayDialNode *moca_fala10 = CreateDialogueNode("fala10", "");
    RayDialNode *moca_fala11 = CreateDialogueNode("fala11", "");

    moca_fala1->components = criarComp("Subconsciente", "--Você se encontra com uma moça muito encantadora ao lado de um grande caranguejo.--");
    moca_fala2->components = criarComp("Subconsciente", "--Você sente que, em outra circunstância, cairia no encanto dela. Não há dúvidas.--");
    moca_fala3->components = criarComp(lenda->nome, "Este caranguejo me lembra o mangue. Meu querido mangue.");
    moca_fala4->components = criarComp(lenda->nome, "Não sei o que me fez vir para cá, mas preciso voltar pro lugar de onde vim.");
    moca_fala5->components = criarComp("Subconsciente", "--Talvez você possa ajudá-la a sair daqui, mas como?--");
    moca_fala6->components = criarComp(lenda->nome, "Quero voltar pro meu mangue...");
    moca_fala7->components = criarComp(lenda->nome, "Um bilhete prum passeio de catamarã? É, acho que com isso vou poder voltar pro mangue do Pina amanhã, talvez.");
    moca_fala8->components = criarComp(lenda->nome, "Obrigada viu. Eu até te encantaria pra vir comigo... mas vou deixar passar. Não pense que você vai se safar do meu encanto se passar pelo mangue do Pina algum outro dia.");
    moca_fala9->components = criarComp(lenda->nome, "Mas olha, eu tinha comprado um bolo de rolo mais cedo no café daqui perto. Pode ficar com ele, tinha me esquecido que sou um espectro e não como nada.");
    moca_fala10->components = criarComp("Subconsciente", "--Mais uma comida hein? Talvez ainda tenha alguém por aí que precise comer esse bolo de rolo.--");
    moca_fala11->components = criarComp(lenda->nome, "Ainda tá encantado com minha beleza?");

    AddChoice(moca_fala1, moca_fala2);
    AddChoice(moca_fala2, moca_fala3);
    AddChoice(moca_fala3, moca_fala4);
    AddChoice(moca_fala4, moca_fala5);
    AddChoice(moca_fala7, moca_fala8);
    AddChoice(moca_fala8, moca_fala9);
    AddChoice(moca_fala9, moca_fala10);

    lenda->dialogo_raiz = moca_fala1;
    lenda->dialogo_repetido = moca_fala6;
    lenda->dialogo_final = moca_fala7;
    lenda->dialogo_final_repetido = moca_fala11;

    inserir_lenda(&s->lenda_local, "Perna Cabeluda", true, s->perna_local, s->perna_cabeluda1, s->perna_cabeluda2, (Rectangle){900, 300, 200, 350}, (Vector2){200, 0}, s->cracha, "Barbeador", 357);
    lenda = pegar_lenda_atual(s->lenda_local, 357);

    RayDialNode *perna_fala1 = CreateDialogueNode("fala1", "");
    RayDialNode *perna_fala2 = CreateDialogueNode("fala2", "");
    RayDialNode *perna_fala3 = CreateDialogueNode("fala3", "");
    RayDialNode *perna_fala4 = CreateDialogueNode("fala4", "");
    RayDialNode *perna_fala5 = CreateDialogueNode("fala5", "");
    RayDialNode *perna_fala6 = CreateDialogueNode("fala6", "");
    RayDialNode *perna_fala7 = CreateDialogueNode("fala7", "");

    perna_fala1->components = criarComp(lenda->nome, "...");
    perna_fala2->components = criarComp("Subconsciente", "--Uma perna cabeluda... ela não fala... não da pra saber muito o que ela quer.--");
    perna_fala3->components = criarComp(lenda->nome, "...");
    perna_fala4->components = criarComp(lenda->nome, "...!!!");
    perna_fala5->components = criarComp("Subconsciente", "--Essa perna acabou de te dar um crachá da CESAR?--");
    perna_fala6->components = criarComp("Subconsciente", "--Que sorte, parece que ela estuda algum curso à noite... mas agora você pode finalmente entrar no prédio do CESAR Brum!!!--");
    perna_fala7->components = criarComp(lenda->nome, "...");

    AddChoice(perna_fala1, perna_fala2);
    AddChoice(perna_fala4, perna_fala5);
    AddChoice(perna_fala5, perna_fala6);

    lenda->dialogo_raiz = perna_fala1;
    lenda->dialogo_repetido = perna_fala3;
    lenda->dialogo_final = perna_fala4;
    lenda->dialogo_final_repetido = perna_fala7;

    inserir_lenda(&s->lenda_local, "Rachadura", true, s->rachadura1, s->rachadura1, s->rachadura1, (Rectangle){580, 150, 320, 420}, (Vector2){200, 20}, s->mingau, "Marreta", 104);
    lenda = pegar_lenda_atual(s->lenda_local, 104);

    RayDialNode *rachadura_fala1 = CreateDialogueNode("fala1", "");
    RayDialNode *rachadura_fala2 = CreateDialogueNode("fala2", "");
    RayDialNode *rachadura_fala3 = CreateDialogueNode("fala3", "");
    RayDialNode *rachadura_fala4 = CreateDialogueNode("fala4", "");

    rachadura_fala1->components = criarComp(lenda->nome, "SOCORRO!!!");
    rachadura_fala2->components = criarComp(lenda->nome, "ALGÚEM PODE ME AJUDAR A SAIR DAQUI?");
    rachadura_fala3->components = criarComp("Subconsciente", "--Tem alguém dentro daquela parede? Ela tá rachada, talvez você consiga ajudar a pessoa lá dentro se de alguma forma você conseguir quebrá-la.--");
    rachadura_fala4->components = criarComp(lenda->nome, "SOCORRO!!!");

    AddChoice(rachadura_fala1, rachadura_fala2);
    AddChoice(rachadura_fala2, rachadura_fala3);

    lenda->dialogo_raiz = rachadura_fala1;
    lenda->dialogo_repetido = rachadura_fala4;

    s->quests_completas = 0;
    s->quests_no_ultimo_sorteio = 0;
    s->minigame_ja_ocorreu = false;
}

void free_dados_jogo(Vars_structs_inicio_jogo *s){
    Lendas *lenda = s->lenda_local;
    while (lenda != NULL) {
        if (lenda->dialogo_raiz) {
            FreeDialogueNode(lenda->dialogo_raiz);
            lenda->dialogo_raiz = NULL;
        }
        if (lenda->dialogo_repetido) {
            FreeDialogueNode(lenda->dialogo_repetido);
            lenda->dialogo_repetido = NULL;
        }
        if (lenda->dialogo_final) {
            FreeDialogueNode(lenda->dialogo_final);
            lenda->dialogo_final = NULL;
        }
        if (lenda->dialogo_final_repetido) {
            FreeDialogueNode(lenda->dialogo_final_repetido);
            lenda->dialogo_final_repetido = NULL;
        }
        lenda = lenda->prox;
    }

    FreeDialogueManager(s->dialogo);
    liberar_arvore(&s->mapa);
    liberar_inventario(&s->inventario);
    LiberarItens_j(&s->inventario);
    LiberarItens_i(&s->itensNaoPegos);
    liberar_lendas(&s->lenda_local);
    UnloadTexture(s->marco_zero);
    UnloadTexture(s->comercial);
    UnloadTexture(s->rio_branco);
    UnloadTexture(s->marques_de_olinda1);
    UnloadTexture(s->vigario_tenorio1);
    UnloadTexture(s->vigario_tenorio2);
    UnloadTexture(s->tomazina);
    UnloadTexture(s->madre_de_deus);
    UnloadTexture(s->paco_alfandega);
    UnloadTexture(s->marques_de_olinda2);
    UnloadTexture(s->marques_de_olinda3);
    UnloadTexture(s->marques_de_olinda4);
    UnloadTexture(s->cais_alfandega1);
    UnloadTexture(s->cais_alfandega2);
    UnloadTexture(s->la_ursa);
    UnloadTexture(s->caranguejo);
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
    UnloadTexture(s->saco);
    UnloadTexture(s->cara_la_ursa);
    UnloadTexture(s->marreta);
    UnloadTexture(s->tesoura);
    UnloadTexture(s->isqueiro);
    UnloadTexture(s->bolo);
    UnloadTexture(s->mingau);
    UnloadTexture(s->bilhete);
    UnloadTexture(s->barbeador);
    UnloadTexture(s->cracha);
    UnloadTexture(s->perna_cabeluda1);
    UnloadTexture(s->perna_cabeluda2);
    UnloadTexture(s->perna_local);
    UnloadTexture(s->comadre_local);
    UnloadTexture(s->comadre1);
    UnloadTexture(s->comadre2);
    UnloadTexture(s->cabra_local);
    UnloadTexture(s->cabra);
    UnloadTexture(s->ouro1);
    UnloadTexture(s->ouro2);
    UnloadTexture(s->rachadura1);
    UnloadTexture(s->rachadura2);
    UnloadTexture(s->emparedada1);
    UnloadTexture(s->emparedada2);
    UnloadTexture(s->moca_local);
    UnloadTexture(s->moca);
    UnloadTexture(s->figo_local);
    UnloadTexture(s->figo);

    UnloadMusicStream(s->pink);
    CloseAudioDevice();
}