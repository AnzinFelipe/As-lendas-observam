#include "raylib.h"
#include "screens.h"
#include <math.h>

GameScreen RunGameOver(int motivo) {
    const char *subtitulo = "base";

    Texture2D fundo_gameover;
    Color texto;
    int offset = 0;

    if (motivo == 0) {
        subtitulo = "Horas se passaram mas o dia nunca chegou... voce se encontra preso no Marco Zero";
        fundo_gameover = LoadTexture("assets/images/telas/marco1.jpg");
        texto = MAROON;
        offset = 0;
    } 
    else if (motivo == 1){
        subtitulo = "O isqueiro se apagou e seu destino se sela no Recife Antigo para sempre...";
        fundo_gameover = LoadTexture("assets/images/telas/Gameover2.png");
        texto = YELLOW;
        offset = -400;
    }
    else if (motivo == 2){
        subtitulo = "Voce ajudou o papa figo a atormentar as ruas do Recife";
        fundo_gameover = LoadTexture("assets/images/telas/Gameover1.5.png");
        texto = MAROON;
        offset = -400;
    }

    else if (motivo == 3){
        subtitulo = "Voce encontra abrigo no Cesar e sobrevive essa noite";
        fundo_gameover = LoadTexture("assets/images/telas/Gameover1.5.png");
        texto = GREEN;
        offset = 0;
    }

    Rectangle Menu = (Rectangle){ 800 - MeasureText("MENU", 40) / 2 - offset, 400, 150, 40 };
    Rectangle Sair = (Rectangle){ 800 - MeasureText("SAIR", 40) / 2 - offset, 475, 100, 40 };
    
    RenderTexture2D tela_gameover = LoadRenderTexture(1600, 900);

    
    Color hover = RED; 
    Color naohover = WHITE;
    GameScreen proxima_tela = SAIR;

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
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse_novo, Menu)) {
            proxima_tela = MENU;
            break; 
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse_novo, Sair)) {
            proxima_tela = SAIR;
            break; 
        }

        bool cursor = false;

        BeginTextureMode(tela_gameover);
            ClearBackground(BLACK); 

            DrawTexturePro(
                fundo_gameover, 
                (Rectangle){ 0, 0, (float)fundo_gameover.width, (float)fundo_gameover.height }, 
                (Rectangle){ 0, 0, 1600, 900 }, 
                (Vector2){ 0, 0 }, 
                0.0f, 
                WHITE
            );

            

            DrawText("FIM DE JOGO", 800 - MeasureText("FIM DE JOGO", 60) / 2 - offset, 250, 60, RED);
            DrawText(subtitulo, 800 - MeasureText(subtitulo, 20) / 2 - offset, 320, 20, texto);

            if (CheckCollisionPointRec(mouse_novo, Menu)) {
                DrawText("MENU", 800 - MeasureText("MENU", 40) / 2 - offset, 400, 40, hover);
                cursor = true;
            } else {
                DrawText("MENU", 800 - MeasureText("MENU", 40) / 2 - offset, 400, 40, naohover);
            }

            if (CheckCollisionPointRec(mouse_novo, Sair)) {
                DrawText("SAIR", 800 - MeasureText("SAIR", 40) / 2 - offset, 475, 40, hover);
                cursor = true;
            } else {
                DrawText("SAIR", 800 - MeasureText("SAIR", 40) / 2 - offset, 475, 40, naohover);
            }
            
            if (cursor) {
                SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            } else {
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            }
               
        EndTextureMode();
        
        BeginDrawing();
            ClearBackground(BLACK);
            DrawTexturePro(tela_gameover.texture, (Rectangle){0, 0, 1600, -900}, nova_tela, (Vector2){0, 0}, 0.0f, WHITE);
        EndDrawing();
    }
    
    UnloadTexture(fundo_gameover);
    UnloadRenderTexture(tela_gameover);
    
    return proxima_tela;
}