#include "raylib.h"
#include "screens.h"
#include <math.h>

GameScreen RunMenu(void) {
    Rectangle Iniciar = (Rectangle){ 800 - MeasureText("INICIAR JOGO", 40) / 2, 250, 285, 40};
    Rectangle Sair = (Rectangle){ 800 - MeasureText("SAIR", 40) / 2, 325, 100, 40 };


    RenderTexture2D tela_menu = LoadRenderTexture(1600, 900);
    
    Color hover = YELLOW;
    Color naohover = WHITE;

    while (!WindowShouldClose()) {
        
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
        
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse_novo, Iniciar)) {
            UnloadRenderTexture(tela_menu);
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            return JOGO;
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse_novo, Sair)) {
            UnloadRenderTexture(tela_menu);
            return SAIR;
        }

        
        bool cursor = false;
        BeginTextureMode(tela_menu);
            ClearBackground(GRAY);

            DrawText("As Lendas Observam", 800 - MeasureText("As Lendas Observam", 50) / 2, 150, 50, WHITE);
            // DrawText(local->nome, 800 - MeasureText(local->nome, 25) / 2, 15, 25, WHITE);

            
            // DrawRectangleRec(Iniciar, BLUE);
            // DrawRectangleRec(Sair, RED); 2
            if (CheckCollisionPointRec(mouse_novo, Iniciar)){
                DrawText("INICIAR JOGO", 800 - MeasureText("INICIAR JOGO", 40) / 2, 250, 40, hover);
                cursor = true;
            }
            else {
                DrawText("INICIAR JOGO", 800 - MeasureText("INICIAR JOGO", 40) / 2, 250, 40, naohover);
            }

            if (CheckCollisionPointRec(mouse_novo, Sair)){
                DrawText("SAIR", 800 - MeasureText("SAIR", 40) / 2, 325, 40, hover);
                cursor = true;
            }
            else {
                DrawText("SAIR", 800 - MeasureText("SAIR", 40) / 2, 325, 40, naohover);
            }
            
            if (cursor == true) {
                SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            } else {
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            }
               
        EndTextureMode();
        
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexturePro(tela_menu.texture, (Rectangle){0, 0, 1600, -900}, nova_tela, (Vector2){0, 0}, 0.0f, WHITE);
        EndDrawing();
    }
    
    return SAIR;
}
