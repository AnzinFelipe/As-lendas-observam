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
    Texture2D comercial = LoadTexture("assets/images/locais/comercial.png");
    Texture2D marco_zero = LoadTexture("assets/images/locais/marco_zero.png");
    Texture2D barbosa_lima1 = LoadTexture("assets/images/locais/barbosa_lima1.png");
    Texture2D barbosa_lima2 = LoadTexture("assets/images/locais/barbosa_lima2.png");
    Texture2D bom_jesus1 = LoadTexture("assets/images/locais/bom_jesus1.png");
    Texture2D bom_jesus2 = LoadTexture("assets/images/locais/bom_jesus2.png");
    Texture2D arsenal = LoadTexture("assets/images/locais/arsenal.png");
    Texture2D frevo = LoadTexture("assets/images/locais/frevo.png");
    Texture2D rodrigues_mendes = LoadTexture("assets/images/locais/rodrigues_mendes.png");
    Texture2D bom_jesus3 = LoadTexture("assets/images/locais/bom_jesus3.png");
    Texture2D malakoff = LoadTexture("assets/images/locais/malakoff.png");
    Texture2D item_teste = LoadTexture("assets/images/item_teste.jpg");
    PlayMusicStream(pink);

    Arvore_mapa *mapa = NULL;
    inserir_local(&mapa, 100, "Marco Zero", marco_zero, NULL, &(Rectangle){920, 600, 400, 200}, &(Rectangle){200, 600, 400, 200}, NULL);
    inserir_local(&mapa, 150, "Associação Comercial de Pernambuco", comercial, NULL, &(Rectangle){200, 450, 200, 300}, &(Rectangle){1120, 450, 200, 300}, &(Rectangle){500, 700, 500, 100});
    inserir_local(&mapa, 151, "Avenida Barbosa Lima", barbosa_lima1, NULL, NULL, &(Rectangle){550, 400, 350, 250}, &(Rectangle){500, 700, 500, 100});
    inserir_local(&mapa, 200, "Avenida Barbosa Lima", barbosa_lima2, NULL, &(Rectangle){300, 350, 200, 300}, &(Rectangle){1120, 400, 200, 300}, &(Rectangle){500, 700, 500, 100});
    inserir_local(&mapa, 201, "Rua do Bom Jesus", bom_jesus1, NULL, NULL, &(Rectangle){570, 350, 350, 250}, &(Rectangle){500, 700, 500, 100});
    inserir_local(&mapa, 202, "Rua do Bom Jesus", bom_jesus2, NULL, NULL, &(Rectangle){570, 350, 350, 250}, &(Rectangle){500, 700, 500, 100});
    inserir_local(&mapa, 230, "Praça do Arsenal", arsenal, NULL, &(Rectangle){200, 360, 200, 400}, &(Rectangle){1120, 360, 200, 400}, &(Rectangle){500, 700, 500, 100});
    inserir_local(&mapa, 215, "Paço do Frevo", frevo, NULL, NULL, &(Rectangle){1120, 300, 200, 400}, &(Rectangle){500, 700, 500, 100});
    inserir_local(&mapa, 220, "Rua Barão Rodrigues Mendes", rodrigues_mendes, NULL, &(Rectangle){400, 350, 200, 300}, &(Rectangle){1070, 360, 250, 300}, &(Rectangle){500, 700, 500, 100});
    inserir_local(&mapa, 240, "Rua do Bom Jesus", bom_jesus3, NULL, NULL, &(Rectangle){650, 350, 350, 250}, &(Rectangle){500, 700, 500, 100});
    inserir_local(&mapa, 250, "Torre Malakoff", malakoff, NULL, NULL, NULL, &(Rectangle){500, 700, 500, 100});
    Arvore_mapa *local_atual = NULL;
    int chave_atual = 100;
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
        desenhar_hitbox(local_atual);
        desenhar_inventario(inventario);

        EndDrawing();
    }

    liberar_arvore(&mapa);
    liberar_inventario(&inventario);

    UnloadTexture(marco_zero);
    UnloadTexture(comercial);
    UnloadTexture(barbosa_lima1);
    UnloadTexture(barbosa_lima2);
    UnloadTexture(bom_jesus1);
    UnloadTexture(bom_jesus2);
    UnloadTexture(arsenal);
    UnloadTexture(frevo);
    UnloadTexture(rodrigues_mendes);
    UnloadTexture(bom_jesus3);
    UnloadTexture(malakoff);
    UnloadTexture(item_teste);
    UnloadMusicStream(pink);

    CloseAudioDevice();

    CloseWindow();

    return 0;
}