#include <stdio.h>
#include "raydial.h"
#include <math.h>
#include "screens.h"
#include "state.h"
#include "falas.h"

GameScreen RunCutscene(void){
    RenderTexture2D tela_cutscene = LoadRenderTexture(1600, 900);
    GameState state = DIALOGO;
    RayDialManager *dialogo;

    RayDialNode *Cutscene_fala1 = CreateDialogueNode("fala1", "");
    RayDialNode *Cutscene_fala2 = CreateDialogueNode("fala2", "");
    RayDialNode *Cutscene_fala3 = CreateDialogueNode("fala3", "");
    RayDialNode *Cutscene_fala4 = CreateDialogueNode("fala4", "");
    RayDialNode *Cutscene_fala5 = CreateDialogueNode("fala5", "");
    RayDialNode *Cutscene_fala6 = CreateDialogueNode("fala6", "");
    RayDialNode *Cutscene_fala7 = CreateDialogueNode("fala7", "");
    RayDialNode *Cutscene_fala8 = CreateDialogueNode("fala8", "");
    RayDialNode *Cutscene_fala9 = CreateDialogueNode("fala9", "");
    RayDialNode *Cutscene_fala10 = CreateDialogueNode("fala10", "");
    RayDialNode *Cutscene_fala11 = CreateDialogueNode("fala11", "");
    RayDialNode *Cutscene_fala12 = CreateDialogueNode("fala12", "");
    RayDialNode *Cutscene_fala13 = CreateDialogueNode("fala13", "");
    RayDialNode *Cutscene_fala14 = CreateDialogueNode("fala14", "");
    RayDialNode *Cutscene_fala15 = CreateDialogueNode("fala15", "");
    RayDialNode *Cutscene_fala16 = CreateDialogueNode("fala16", "");
    RayDialNode *Cutscene_fala17 = CreateDialogueNode("fala17", "");
    RayDialNode *Cutscene_fala18 = CreateDialogueNode("fala18", "");
    RayDialNode *Cutscene_fala19 = CreateDialogueNode("fala19", "");
    RayDialNode *Cutscene_fala20 = CreateDialogueNode("fala20", "");
    RayDialNode *Cutscene_fala21 = CreateDialogueNode("fala21", "");
     
    Cutscene_fala1->components = criarComp("TUTORIAL", "Clique em personagens para interagir com eles. Clique na tela ou aperte a barra de ESPAÇO para prosseguir nas conversas.");
    Cutscene_fala2->components = criarComp("TUTORIAL", "Para se movimentar pelos locais, procure e clique em áreas no cenário onde o cursor do mouse mudar de aparência.");
    Cutscene_fala3->components = criarComp("TUTORIAL", "SOBRE ITENS: Clique em itens para pegá-los. Para entregá-los a personagens, clique, segure e arraste-os para cima da imagem deles e solte.");    
    Cutscene_fala4->components = criarComp("TUTORIAL", "SOBRE ITENS: Clique, segure e arraste um item para cima de outro no inventário para combiná-los.");
    Cutscene_fala5->components = criarComp("TUTORIAL", "Isso é tudo. Se divirta......... E boa sorte.");
    Cutscene_fala6->components = criarComp("Telefone", "*TRRRIIMMM TRRRIIIMM TRRRIIIIMMM");
    Cutscene_fala7->components = criarComp("Diego", "Alô?");
    Cutscene_fala8->components = criarComp("Edgar", "Opa mano, tás livre hoje de noite? Tava pensando em eu e tu sair junto pra um barzinho aqui no antigo, tá ligado?");
    Cutscene_fala9->components = criarComp("Diego", "Pô, vamo vei. Tava no tédio o dia todo também, me salvasse. Não aguentava mais ficar dentro de casa.");
    Cutscene_fala10->components = criarComp("Edgar", "Massa. A gente se vê às 7 da noite no Marco Zero, Demorô?");
    Cutscene_fala11->components = criarComp("Diego", "Beleza, irmão. Até mais tarde.");
    Cutscene_fala12->components = criarComp("...", "--HORAS DEPOIS...--");
    Cutscene_fala13->components = criarComp("Motorista de Uber", "Estamos perto. Olha, amigo, se eu fosse você não ficava muito tempo no Recife Antigo hoje.");
    Cutscene_fala14->components = criarComp("Diego", "Ué? Tá rolando muito assalto ultimamente? Se for isso, pelo menos eu sei como andar por aqui e sei em quais ruas não entrar nesse horário.");
    Cutscene_fala15->components = criarComp("Motorista de Uber", "Não, não é isso. Muitos motoristas que passaram por aqui agora a pouco relataram ver coisas bizarras...");
    Cutscene_fala16->components = criarComp("Motorista de Uber", "Vultos e silhuetas nas ruas. Animais de aparência distorcida. assobios distantes, como se algo os chamasse para becos obscuros...");
    Cutscene_fala17->components = criarComp("Motoristas de Uber", "Eu queria estar brincando só para te botar medo, mas é sério garoto. O quê quer que tenha vindo fazer aqui, é bom que seja breve.");
    Cutscene_fala18->components = criarComp("Diego", "... éééé... beleza patrão. Peguei a mensagem. Pode me deixar descer aqui no Marco Zero mesmo");
    Cutscene_fala19->components = criarComp("Diego", "(Acho que esse mano num tá batendo bem da cabeça. Enfim, vou ligar pro Edgar, era pra ele tá aqui já.)");
    Cutscene_fala20->components = criarComp("Diego", "(Ah não. Só pode tá de sacanagem. Sem serviço??? Lascou. Vou ter que andar por aí pra procurar ele... Melhor me ligar para não ser roubado.)");
    Cutscene_fala21->components = criarComp("Diego", "(Pra ser honesto, olhando agora, aqui tá bem vazio... tem nem carro passando... É perigoso se eu ficar parado aqui sozinho.)");

    AddChoice(Cutscene_fala1, Cutscene_fala2);
    AddChoice(Cutscene_fala2, Cutscene_fala3);
    AddChoice(Cutscene_fala3, Cutscene_fala4);
    AddChoice(Cutscene_fala4, Cutscene_fala5);
    AddChoice(Cutscene_fala5, Cutscene_fala6);
    AddChoice(Cutscene_fala6, Cutscene_fala7);
    AddChoice(Cutscene_fala7, Cutscene_fala8);
    AddChoice(Cutscene_fala8, Cutscene_fala9);
    AddChoice(Cutscene_fala9, Cutscene_fala10);
    AddChoice(Cutscene_fala10, Cutscene_fala11);
    AddChoice(Cutscene_fala11, Cutscene_fala12);
    AddChoice(Cutscene_fala12, Cutscene_fala13);
    AddChoice(Cutscene_fala13, Cutscene_fala14);
    AddChoice(Cutscene_fala14, Cutscene_fala15);
    AddChoice(Cutscene_fala15, Cutscene_fala16);
    AddChoice(Cutscene_fala16, Cutscene_fala17);
    AddChoice(Cutscene_fala17, Cutscene_fala18);
    AddChoice(Cutscene_fala18, Cutscene_fala19);
    AddChoice(Cutscene_fala19, Cutscene_fala20);
    AddChoice(Cutscene_fala20, Cutscene_fala21);

    dialogo = CreateDialogueManager(Cutscene_fala1);
    
    while (!WindowShouldClose()) {
        int largura_tela = GetScreenWidth();
        int altura_tela = GetScreenHeight();

        float escala = fminf((float)largura_tela / 1600, (float)altura_tela / 900);

        Rectangle nova_tela = {
            (largura_tela - 1600 * escala) / 2.0f,
            (altura_tela - 900 * escala) / 2.0f,
            1600 * escala, 900 * escala
        };

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_SPACE)) {
            AdvanceDialogue(dialogo);
        }

        UpdateDialogueManager(dialogo);

        if (dialogo && !dialogo->isActive) {
            FreeDialogueManager(dialogo);
            dialogo = NULL;
            return JOGO;
        }
    
        BeginTextureMode(tela_cutscene);
            ClearBackground(BLACK);

            if (state == DIALOGO) {
                DrawDialogueManager(dialogo);
            }
               
        EndTextureMode();
        
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexturePro(tela_cutscene.texture, (Rectangle){0, 0, 1600, -900}, nova_tela, (Vector2){0, 0}, 0.0f, WHITE);
        EndDrawing();
    }
    
    return SAIR;
}