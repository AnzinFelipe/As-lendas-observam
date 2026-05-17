#include <stdlib.h>
#include <string.h>
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
    memset(novo_jogo, 0, sizeof(Vars_structs_inicio_jogo));

    GameState state = EXPLORACAO;

    SetTargetFPS(60);

    while(!WindowShouldClose()) {
        switch (currentScreen){
            case SAIR:
                free_dados_jogo(novo_jogo);
                free(novo_jogo);
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
                        novo_jogo->em_hitbox = false;
                        mudar_local(novo_jogo->local_atual, novo_jogo->mapa, &novo_jogo->chave_atual, mouse_novo);
                        novo_jogo->local_atual = buscar_local(novo_jogo->mapa, novo_jogo->chave_atual);
                        novo_jogo->lenda_atual = pegar_lenda_atual(novo_jogo->lenda_local, novo_jogo->chave_atual);
                        PegarItemEEntrarInventário(&novo_jogo->itensNaoPegos, novo_jogo->chave_atual, mouse_novo, &novo_jogo->inventario, &novo_jogo->em_hitbox);
                        bool clicada = interagir_lenda(novo_jogo->lenda_atual, mouse_novo, &novo_jogo->em_hitbox);
                        mudar_mouse_mapa(novo_jogo->local_atual, mouse_novo, &novo_jogo->em_hitbox);

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
                    
                    if (novo_jogo->em_hitbox == false) {
                        SetMouseCursor(0);
                    }

                    //Desenhar na textura
                    BeginTextureMode(novo_jogo->tela);
                    
                        ClearBackground(BLACK);
                        desenhar_local(novo_jogo->local_atual);
                        //desenhar_hitbox(novo_jogo->local_atual);
                        if (state == EXPLORACAO) {
                            desenhar_lendas(novo_jogo->lenda_atual);
                        } else if (state == DIALOGO) {
                            desenhar_lendas_conversa(novo_jogo->lenda_atual);
                        }

                        desenhar_inventario(novo_jogo->inventario, 90, 140, 140);

                        ItemAparecerNoCenario(&novo_jogo->itensNaoPegos, novo_jogo->chave_atual);

                        if (state == DIALOGO) {
                            DrawDialogueManager(novo_jogo->dialogo);
                        }
                        
                    EndTextureMode();
                    
                    //Desenhar a textura
                    BeginDrawing();
                    ClearBackground(BLACK);
                    DrawTexturePro(novo_jogo->tela.texture, (Rectangle){0, 0, 1600, -900}, nova_tela, (Vector2){0, 0}, 0.0f, WHITE);
                    if (novo_jogo->em_hitbox) {
                        DrawCircleGradient(mouse.x, mouse.y, 40 * escala, (Color){255, 255, 255, 100}, (Color){255, 255, 255, 0});
                        //DrawCircleLines(mouse.x, mouse.y, 20 * escala, WHITE);
                    }
                    EndDrawing();
                }  
                    
            }
                    
                     
        }
    
    free_dados_jogo(novo_jogo);
    free(novo_jogo);

    CloseWindow();

    return 0;
}   
