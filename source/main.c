#include <stdlib.h>
#include "mapa.h"
#include "inventario.h"
#include "raylib.h"

int main() {

    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_MAXIMIZED);
    InitWindow(1600, 900, "As Lendas Observam");
    SetTargetFPS(60);

    InitAudioDevice();
    Music pink = LoadMusicStream("assets/musics/Pink.mp3");
    Texture2D teste = LoadTexture("assets/images/teste.png");
    Texture2D marco_zero = LoadTexture("assets/images/marco_zero.png");
    Texture2D item_teste = LoadTexture("assets/images/item_teste.jpg");
    PlayMusicStream(pink);

    Arvore_mapa *mapa = NULL;
    inserir_local(&mapa, 50, "Marco Zero", marco_zero, NULL);
    inserir_local(&mapa, 48, "Prédio que eu não sei o nome", teste, NULL);
    Arvore_mapa *local_atual = NULL;
    int chave_atual = 50;
    local_atual = buscar_local(mapa, chave_atual);

    Inventario *inventario = NULL;
    inserir_inventario(&inventario, "Teste", "Bla bla bla", item_teste);
    inserir_inventario(&inventario, "Teste", "Bla bla bla", item_teste);

    while(!WindowShouldClose()) {

        UpdateMusicStream(pink);

        mudar_local(local_atual, &chave_atual);
        local_atual = buscar_local(mapa, chave_atual);

        BeginDrawing();

        ClearBackground(BLACK);
        desenhar_local(local_atual);
        desenhar_inventario(inventario);

        EndDrawing();
    }

    liberar_arvore(&mapa);
    liberar_inventario(&inventario);

    UnloadTexture(teste);
    UnloadTexture(marco_zero);
    UnloadTexture(item_teste);
    UnloadMusicStream(pink);

    CloseAudioDevice();

    CloseWindow();

    return 0;
}