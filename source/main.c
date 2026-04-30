#include <stdlib.h>
#include "mapa.h"
#include "raylib.h"

int main() {

    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(1600, 900, "Joguinho");
    SetTargetFPS(60);

    InitAudioDevice();
    Music pink = LoadMusicStream("assets/musics/Pink.mp3");
    PlayMusicStream(pink);

    while(!WindowShouldClose()) {

        UpdateMusicStream(pink);

        BeginDrawing();

        ClearBackground(BLUE);

        EndDrawing();
    }

    UnloadMusicStream(pink);

    CloseAudioDevice();

    CloseWindow();

    return 0;
}