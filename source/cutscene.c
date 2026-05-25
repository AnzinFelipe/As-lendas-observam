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

    Cutscene_fala1->components = criarComp("Subconsciente", "--Você se depara com uma cabra muito estranha, ela tem olhos e um bafo de fogo, não parece amigável.--");
    Cutscene_fala2->components = criarComp("bi", "Eu sou a Cabra Cabriola. Que como...");
    Cutscene_fala3->components = criarComp("bi", "...Poxa, um adulto? Pelo visto vou ficar morrendo de fome essa noite.");
    Cutscene_fala4->components = criarComp("bi", "Saia daqui e não me incomode, estou de barriga vazia e sem paciência para falar com um adulto estranho.");
    Cutscene_fala5->components = criarComp("Subconsciente", "--Pelo visto, essa cabra precisa comer para falar com você.--");
    Cutscene_fala6->components = criarComp("Subconsciente", "--Obviamente você não vai dar o que ela quer. Tente mudar o paladar dela com uma comida apropriada.--");
    Cutscene_fala7->components = criarComp("Subconsciente", "--Ache alguma comida, daí então ela vai querer falar com você.--");
    Cutscene_fala8->components = criarComp("bi", "Hmmmm o que é isso? Até que parece gostoso, acho que posso experimentar...");
    Cutscene_fala9->components = criarComp("bi", "Tá, isso é bem melhor do que aquilo que ando devorando minha vida inteira...");
    Cutscene_fala10->components = criarComp("bi", "Toma isso daqui, uma tesoura. Eu costumava roubar do velho feioso que tá por aqui por perto. Não vou precisar mais, já que você ampliou meu paladar.");
    Cutscene_fala11->components = criarComp("Subconsciente", "--É isso! Com essa tesoura você vai poder fazer um furo no saco de pano daquele velho antes de entregá-lo.--");
    Cutscene_fala12->components = criarComp("bi", "Por acaso tu não teria mais daquele bolo aí pra mim, né?");

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