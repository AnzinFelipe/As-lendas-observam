#include <stdlib.h>
#include "mapa.h"
#include "inventario.h"
#include "raylib.h"
#include <math.h>
#include "item.h"
#include "iniciar_liberar_jogo.h"
#include "screens.h"
#include "lendas.h"
#include "raydial.h"
#include "state.h"

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_MAXIMIZED);
    InitWindow(1600, 900, "As Lendas Observam");
    SetWindowMinSize(640, 360);

    GameScreen currentScreen = MENU;

    int primeiro = 1;
    Vars_structs_inicio_jogo *novo_jogo = (Vars_structs_inicio_jogo*)malloc(sizeof(Vars_structs_inicio_jogo));

    GameState state = EXPLORACAO;

    SetTargetFPS(60);

    while(!WindowShouldClose()) {
        switch (currentScreen){
            case SAIR:
                if (IsAudioDeviceReady()) {
                    CloseAudioDevice();
                    }
                CloseWindow();
                return 0;
            case MENU:
                currentScreen = RunMenu();
                break; 
            case JOGO:
                if (currentScreen == JOGO) {
                    if (primeiro == 1){
                        iniciar_jogo(novo_jogo);
                        primeiro = 0;
                    }
                    
                    int largura_tela = GetScreenWidth();
                    int altura_tela = GetScreenHeight();

                    float escala = fminf((float)largura_tela / 1600, (float)altura_tela / 900);

                    Rectangle nova_tela = {
                        (largura_tela - 1600 * escala) / 2.0f,
                        (altura_tela - 900 * escala) / 2.0f,
                        1600 * escala, 900 * escala
                    };

                    Vector2 mouse = GetMousePosition();
                    Vector2 mouse_novo = {
                        (mouse.x - nova_tela.x) / escala,
                        (mouse.y - nova_tela.y) / escala
                    };

                    UpdateMusicStream(novo_jogo->pink);

                    bool dialogo_acabou_esse_frame = false;
                    if (state == DIALOGO) {

                        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_SPACE)) {
                            AdvanceDialogue(novo_jogo->dialogo);
                        }

                        UpdateDialogueManager(novo_jogo->dialogo);

                        if (novo_jogo->dialogo && !novo_jogo->dialogo->isActive) {
                            FreeDialogueManager(novo_jogo->dialogo);
                            novo_jogo->dialogo = NULL;
                            state = EXPLORACAO;
                            dialogo_acabou_esse_frame = true;
                        }
                    }
                    if (state == EXPLORACAO && !dialogo_acabou_esse_frame) {
                        mudar_local(novo_jogo->local_atual, &novo_jogo->chave_atual, mouse_novo);
                        novo_jogo->local_atual = buscar_local(novo_jogo->mapa, novo_jogo->chave_atual);
                        novo_jogo->lenda_atual = pegar_lenda_atual(novo_jogo->lenda_local, novo_jogo->chave_atual);
                        bool clicada = interagir_lenda(novo_jogo->lenda_atual, mouse_novo);

                        if (clicada == true && novo_jogo->dialogo == NULL && !dialogo_acabou_esse_frame) {
                            Lendas *conversa = novo_jogo->lenda_atual;
                            if (conversa->ja_conversou == false) {
                                novo_jogo->dialogo = CreateDialogueManager(conversa->dialogo_raiz);
                                conversa->ja_conversou = true;
                            }
                            else {
                                novo_jogo->dialogo = CreateDialogueManager(conversa->dialogo_repetido);
                            }
                            state = DIALOGO;    
                        }
                    }
                    
                    //Desenhar na textura
                    BeginTextureMode(novo_jogo->tela);
                    
                        ClearBackground(BLACK);
                        desenhar_local(novo_jogo->local_atual);
                        desenhar_hitbox(novo_jogo->local_atual);
                        desenhar_lendas(novo_jogo->lenda_atual);

                        desenhar_inventario(novo_jogo->inventario, 90, 140, 140);

                        ItemAparecerNoCenario(&novo_jogo->itensNaoPegos, novo_jogo->chave_atual);
                        PegarItemEEntrarInventário(&novo_jogo->itensNaoPegos, novo_jogo->chave_atual, mouse_novo, &novo_jogo->inventario);

                        if (state == DIALOGO) {
                            DrawDialogueManager(novo_jogo->dialogo);
                        }
                    
                    EndTextureMode();
                    
                    //Desenhar a textura
                    BeginDrawing();
                    ClearBackground(BLACK);
                    DrawTexturePro(novo_jogo->tela.texture, (Rectangle){0, 0, 1600, -900}, nova_tela, (Vector2){0, 0}, 0.0f, WHITE);
                    EndDrawing();
                }
        }             
    }

    liberar_arvore(&novo_jogo->mapa);
    liberar_inventario(&novo_jogo->inventario);
    LiberarItens_j(&novo_jogo->inventario);
    LiberarItens_i(&novo_jogo->itensNaoPegos);
    liberar_lendas(&novo_jogo->lenda_local);
    UnloadTexture(novo_jogo->marco_zero);
    UnloadTexture(novo_jogo->comercial);
    UnloadTexture(novo_jogo->barbosa_lima1);
    UnloadTexture(novo_jogo->barbosa_lima2);
    UnloadTexture(novo_jogo->bom_jesus1);
    UnloadTexture(novo_jogo->bom_jesus2);
    UnloadTexture(novo_jogo->arsenal);
    UnloadTexture(novo_jogo->frevo);
    UnloadTexture(novo_jogo->rodrigues_mendes);
    UnloadTexture(novo_jogo->parede);
    UnloadTexture(novo_jogo->guia);
    UnloadTexture(novo_jogo->observatorio1);
    UnloadTexture(novo_jogo->observatorio2);
    UnloadTexture(novo_jogo->cais_apolo);
    UnloadTexture(novo_jogo->cesar_brum);
    UnloadTexture(novo_jogo->bom_jesus3);
    UnloadTexture(novo_jogo->malakoff);
    UnloadTexture(novo_jogo->honglu);
    UnloadTexture(novo_jogo->queenOfHatred);
    UnloadTexture(novo_jogo->comadre1);
    UnloadTexture(novo_jogo->comadre2);
    UnloadTexture(novo_jogo->cabra);
    UnloadTexture(novo_jogo->ouro2);
    UnloadMusicStream(novo_jogo->pink);
    free(novo_jogo);
    CloseAudioDevice();

    CloseWindow();

    return 0;
}   
