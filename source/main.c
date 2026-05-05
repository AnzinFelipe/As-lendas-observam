#include <stdlib.h>
#include "mapa.h"
#include "inventario.h"
#include "raylib.h"
#include <math.h>
#include "item.h"

int main() {

    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_MAXIMIZED);
    InitWindow(1600, 900, "As Lendas Observam");
    SetWindowMinSize(640, 360);

    RenderTexture2D tela = LoadRenderTexture(1600, 900);
    SetTextureFilter(tela.texture, TEXTURE_FILTER_BILINEAR);

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
    Texture2D parede = LoadTexture("assets/images/locais/parede.png");
    Texture2D guia = LoadTexture("assets/images/locais/guia.png");
    Texture2D observatorio1 = LoadTexture("assets/images/locais/observatorio1.png");
    Texture2D observatorio2 = LoadTexture("assets/images/locais/observatorio2.png");
    Texture2D cais_apolo = LoadTexture("assets/images/locais/cais_apolo.png");
    Texture2D cesar_brum = LoadTexture("assets/images/locais/cesar_brum.png");
    Texture2D bom_jesus3 = LoadTexture("assets/images/locais/bom_jesus3.png");
    Texture2D malakoff = LoadTexture("assets/images/locais/malakoff.png");
    Texture2D item_teste = LoadTexture("assets/images/item_teste.jpg");
    Texture2D honglu= LoadTexture("assets/images/Itens/Honglu.png");
    Texture2D queenOfHatred = LoadTexture ("assets/images/Itens/QOH.png");
    PlayMusicStream(pink);

    Arvore_mapa *mapa = NULL;
    inserir_local(&mapa, 500, "Marco Zero", marco_zero, NULL, &(Rectangle){960, 600, 400, 200}, &(Rectangle){240, 600, 400, 200}, NULL);
    inserir_local(&mapa, 300, "Associação Comercial de Pernambuco", comercial, NULL, &(Rectangle){240, 450, 200, 300}, &(Rectangle){1160, 450, 200, 300}, &(Rectangle){540, 700, 500, 100});
    inserir_local(&mapa, 350, "Avenida Barbosa Lima", barbosa_lima1, NULL, NULL, &(Rectangle){590, 400, 350, 250}, &(Rectangle){540, 700, 500, 100});
    inserir_local(&mapa, 400, "Avenida Barbosa Lima", barbosa_lima2, NULL, &(Rectangle){340, 350, 200, 300}, &(Rectangle){1160, 400, 200, 300}, &(Rectangle){540, 700, 500, 100});
    inserir_local(&mapa, 401, "Rua do Bom Jesus", bom_jesus1, NULL, NULL, &(Rectangle){610, 350, 350, 250}, &(Rectangle){540, 700, 500, 100});
    inserir_local(&mapa, 402, "Rua do Bom Jesus", bom_jesus2, NULL, NULL, &(Rectangle){610, 350, 350, 250}, &(Rectangle){540, 700, 500, 100});
    inserir_local(&mapa, 450, "Praça do Arsenal", arsenal, NULL, &(Rectangle){240, 360, 200, 400}, &(Rectangle){1160, 360, 200, 400}, &(Rectangle){540, 700, 500, 100});
    inserir_local(&mapa, 420, "Paço do Frevo", frevo, NULL, NULL, &(Rectangle){1160, 300, 200, 400}, &(Rectangle){540, 700, 500, 100});
    inserir_local(&mapa, 425, "Rua Barão Rodrigues Mendes", rodrigues_mendes, NULL, &(Rectangle){440, 350, 200, 300}, &(Rectangle){1110, 360, 250, 300}, &(Rectangle){540, 700, 500, 100});
    inserir_local(&mapa, 422, "Parede", parede, NULL, NULL, NULL, &(Rectangle){540, 700, 500, 100});
    inserir_local(&mapa, 426, "Rua da Guia", guia, NULL, NULL, &(Rectangle){610, 350, 350, 250}, &(Rectangle){540, 700, 500, 100});
    inserir_local(&mapa, 427, "Rua do Observatório", observatorio1, NULL, NULL, &(Rectangle){590, 350, 350, 250}, &(Rectangle){540, 700, 500, 100});
    inserir_local(&mapa, 428, "Rua do Observatório", observatorio2, NULL, NULL, &(Rectangle){640, 400, 350, 250}, &(Rectangle){540, 700, 500, 100});
    inserir_local(&mapa, 429, "Avenida Cais do Apolo", cais_apolo, NULL, NULL, &(Rectangle){610, 350, 350, 250}, &(Rectangle){540, 700, 500, 100});
    inserir_local(&mapa, 430, "CESAR Brum", cesar_brum, NULL, NULL, NULL, &(Rectangle){540, 700, 500, 100});
    inserir_local(&mapa, 451, "Rua do Bom Jesus", bom_jesus3, NULL, NULL, &(Rectangle){690, 350, 350, 250}, &(Rectangle){540, 700, 500, 100});
    inserir_local(&mapa, 452, "Torre Malakoff", malakoff, NULL, NULL, NULL, &(Rectangle){540, 700, 500, 100});
    Arvore_mapa *local_atual = NULL;
    int chave_atual = 500;
    local_atual = buscar_local(mapa, chave_atual);

    Item *itensNaoPegos = NULL;
    ColocarItemNoMapa(&itensNaoPegos, honglu, "Chibi Lu", (Vector2){100, 200}, "Um chibi Honglu, o que pode acontecer?...", 401);
    ColocarItemNoMapa(&itensNaoPegos, queenOfHatred, "Arcana Slave!", (Vector2){100, 90}, "Arcna Slave!!!!!!!", 401);

    Inventario *inventario = NULL;

    while(!WindowShouldClose()) {
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

        UpdateMusicStream(pink);
        mudar_local(local_atual, &chave_atual, mouse_novo);
        local_atual = buscar_local(mapa, chave_atual);
        
        BeginTextureMode(tela);
        
            ClearBackground(BLACK);
            desenhar_local(local_atual);
            desenhar_hitbox(local_atual);

            desenhar_inventario(inventario, 90, 140, 140);

            ItemAparecerNoCenario(&itensNaoPegos, chave_atual);
            PegarItemEEntrarInventário(&itensNaoPegos, chave_atual, mouse_novo, &inventario);
        
        EndTextureMode();
        
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexturePro(tela.texture, (Rectangle){0, 0, 1600, -900}, nova_tela, (Vector2){0, 0}, 0.0f, WHITE);
        EndDrawing();
    }

    liberar_arvore(&mapa);
    liberar_inventario(&inventario);
    LiberarItens_j(&inventario);
    LiberarItens_i(&itensNaoPegos);
    UnloadTexture(marco_zero);
    UnloadTexture(comercial);
    UnloadTexture(barbosa_lima1);
    UnloadTexture(barbosa_lima2);
    UnloadTexture(bom_jesus1);
    UnloadTexture(bom_jesus2);
    UnloadTexture(arsenal);
    UnloadTexture(frevo);
    UnloadTexture(rodrigues_mendes);
    UnloadTexture(parede);
    UnloadTexture(guia);
    UnloadTexture(observatorio1);
    UnloadTexture(observatorio2);
    UnloadTexture(cais_apolo);
    UnloadTexture(cesar_brum);
    UnloadTexture(bom_jesus3);
    UnloadTexture(malakoff);
    UnloadTexture(honglu);
    UnloadTexture(queenOfHatred);
    UnloadMusicStream(pink);

    CloseAudioDevice();

    CloseWindow();

    return 0;
}   