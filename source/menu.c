#include "raylib.h"
#include "screens.h"
#include <math.h>

GameScreen RunMenu(void) {
    Rectangle Iniciar = (Rectangle){ 800 - MeasureText("INICIAR JOGO", 40) / 2, 300, 285, 40};
    Rectangle Sair = (Rectangle){ 800 - MeasureText("SAIR", 40) / 2, 390, 100, 40 };

    RenderTexture2D tela_menu = LoadRenderTexture(1600, 900);
    Texture2D enfeite = LoadTexture("assets/images/enfeite2.png");
    
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
            UnloadTexture(enfeite);
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            return CUTSCENE;
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse_novo, Sair)) {
            UnloadRenderTexture(tela_menu);
            return SAIR;
        }

        
        bool cursor = false;
        BeginTextureMode(tela_menu);
            ClearBackground(BLACK);
            DrawTexture(enfeite, 0, 0, WHITE);
            DrawRectangle(300, 0, 1000, 600, (Color){0, 0, 0, 150});

            DrawText("As Lendas Observam", 800 - MeasureText("As Lendas Observam", 55) / 2, 200, 55, WHITE);
            // DrawText(local->nome, 800 - MeasureText(local->nome, 25) / 2, 15, 25, WHITE);

            
            // DrawRectangleRec(Iniciar, BLUE);
            // DrawRectangleRec(Sair, RED); 2
            if (CheckCollisionPointRec(mouse_novo, Iniciar)){
                DrawText("INICIAR JOGO", 800 - MeasureText("INICIAR JOGO", 40) / 2, 300, 40, hover);
                cursor = true;
            }
            else {
                DrawText("INICIAR JOGO", 800 - MeasureText("INICIAR JOGO", 40) / 2, 300, 40, naohover);
            }

            if (CheckCollisionPointRec(mouse_novo, Sair)){
                DrawText("SAIR", 800 - MeasureText("SAIR", 40) / 2, 390, 40, hover);
                cursor = true;
            }
            else {
                DrawText("SAIR", 800 - MeasureText("SAIR", 40) / 2, 390, 40, naohover);
            }
            
            if (cursor == true) {
                SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            } else {
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            }

            DrawText("Créditos:", 100, 690, 20, WHITE);
            DrawText("Desenhos - Ian Felipe", 100, 720, 20, WHITE);
            DrawText("Programação - Ian Felipe, Rafael Chiappetta,", 100, 750, 20, WHITE);
            DrawText("Thiago Neiva, Sofia Pan Yu e Guilherme Rapela", 100, 780, 20, WHITE);
               
        EndTextureMode();
        
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexturePro(tela_menu.texture, (Rectangle){0, 0, 1600, -900}, nova_tela, (Vector2){0, 0}, 0.0f, WHITE);
        EndDrawing();
    }

    return SAIR;
}
