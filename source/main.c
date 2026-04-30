#include <stdlib.h>
#include "mapa.h"
#include "raylib.h"

int main() {

    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(1600, 900, "As Lendas Observam");
    SetTargetFPS(60);

    InitAudioDevice();
    Music pink = LoadMusicStream("assets/musics/Pink.mp3");
    Texture2D teste = LoadTexture("assets/images/teste.png");
    PlayMusicStream(pink);

    while(!WindowShouldClose()) {

        UpdateMusicStream(pink);

        BeginDrawing();

        ClearBackground(BLACK);
        DrawTextureEx(teste, (Vector2){200, 50}, 0.0, 0.7, WHITE);

        EndDrawing();
    }

    UnloadTexture(teste);
    UnloadMusicStream(pink);

    CloseAudioDevice();

    CloseWindow();

    return 0;
}