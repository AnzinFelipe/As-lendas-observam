#include <stdlib.h>
#include <string.h>
#include "mapa.h"
#include "inventario.h"
#include "raylib.h"
#include <math.h>
#include "item.h"
#include "iniciar_liberar_jogo.h"
#include "screens.h"

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_MAXIMIZED);
    InitWindow(1600, 900, "As Lendas Observam");
    SetWindowMinSize(640, 360);

    GameScreen currentScreen = MENU;

    int primeiro = 1;
    Vars_structs_inicio_jogo *novo_jogo = (Vars_structs_inicio_jogo*)malloc(sizeof(Vars_structs_inicio_jogo));
    memset(novo_jogo, 0, sizeof(Vars_structs_inicio_jogo));

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
                    mudar_local(novo_jogo->local_atual, &novo_jogo->chave_atual, mouse_novo);
                    novo_jogo->local_atual = buscar_local(novo_jogo->mapa, novo_jogo->chave_atual);
                    
                    BeginTextureMode(novo_jogo->tela);
                    
                        ClearBackground(BLACK);
                        desenhar_local(novo_jogo->local_atual);
                        desenhar_hitbox(novo_jogo->local_atual);

                        desenhar_inventario(novo_jogo->inventario, 90, 140, 140);

                        ItemAparecerNoCenario(&novo_jogo->itensNaoPegos, novo_jogo->chave_atual);
                        PegarItemEEntrarInventário(&novo_jogo->itensNaoPegos, novo_jogo->chave_atual, mouse_novo, &novo_jogo->inventario);
                    
                    EndTextureMode();
                    
                    BeginDrawing();
                    ClearBackground(BLACK);
                    DrawTexturePro(novo_jogo->tela.texture, (Rectangle){0, 0, 1600, -900}, nova_tela, (Vector2){0, 0}, 0.0f, WHITE);
                    EndDrawing();
                        }  
                    
                    }
                    
                     
        }
    
    free_dados_jogo(novo_jogo);
    free(novo_jogo);

    CloseWindow();

    return 0;
}   
