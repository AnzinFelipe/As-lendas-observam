#include <stdlib.h>
#include <stdio.h>
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
#include "gemini.h"
#include "minigame.h"

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(1600, 900, "As Lendas Observam");
    SetWindowMinSize(640, 360);

    GameScreen currentScreen = MENU;

    int primeiro = 1;
    Vars_structs_inicio_jogo *novo_jogo = (Vars_structs_inicio_jogo*)malloc(sizeof(Vars_structs_inicio_jogo));
    memset(novo_jogo, 0, sizeof(Vars_structs_inicio_jogo));

    GameState state = EXPLORACAO;
    char gemini_error_message[256] = "";
    char gemini_fallback_text[512] = "A sua lenda observa em silêncio, e o vento responde de volta com mistério.";
    float gemini_error_timer = 0.0f;
    float gemini_retry_timer = 0.0f;
    bool gemini_disabled = false;

    SetTargetFPS(60);

    while(!WindowShouldClose()) {
        switch (currentScreen){
            case SAIR:
                GeminiFree(&novo_jogo->gemini);
                MinigameFinalizar(&novo_jogo->minigame);
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
                        GeminiInit(&novo_jogo->gemini);
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

                    if (gemini_retry_timer > 0.0f) {
                        gemini_retry_timer -= GetFrameTime();
                        if (gemini_retry_timer < 0.0f) gemini_retry_timer = 0.0f;
                    }

                    if (state == MINIGAME_AGUARDANDO_IA) {
                        GeminiStatus gs = GeminiGetStatus(&novo_jogo->gemini);

                        if (gs == GEMINI_PRONTO) {
                            char texto_ia[512] = "";
                            GeminiPegarResposta(&novo_jogo->gemini, texto_ia, sizeof(texto_ia));

                            MinigameIniciar(
                                &novo_jogo->minigame,
                                texto_ia,
                                &novo_jogo->ouro1,
                                &novo_jogo->ouro1,
                                &novo_jogo->isqueiro
                            );
                            state = MINIGAME_INTRO;
                        } else if (gs == GEMINI_ERRO) {
                            GeminiPegarResposta(&novo_jogo->gemini, gemini_error_message, sizeof(gemini_error_message));
                            gemini_disabled = true;
                            gemini_error_timer = 5.0f;
                            gemini_retry_timer = 10.0f;
                            MinigameIniciar(
                                &novo_jogo->minigame,
                                gemini_fallback_text,
                                &novo_jogo->ouro1,
                                &novo_jogo->ouro1,
                                &novo_jogo->isqueiro
                            );
                            state = MINIGAME_INTRO;
                        }
                        // enquanto aguarda: o jogo renderiza normalmente abaixo
                    } else if (state == MINIGAME_INTRO) {
                        MinigameUpdateIntro(&novo_jogo->minigame);
                        if (novo_jogo->minigame.fase == MINIGAME_FASE_BUSCA) {
                            state = MINIGAME_BUSCA;
                        }
                    } else if (state == MINIGAME_BUSCA) {
                        // Permite o jogador navegar pelo mapa normalmente
                        novo_jogo->em_hitbox = false;
                        mudar_local(novo_jogo->local_atual, novo_jogo->mapa,
                                    &novo_jogo->chave_atual, mouse_novo);
                        novo_jogo->local_atual = buscar_local(novo_jogo->mapa, novo_jogo->chave_atual);
                        mudar_mouse_mapa(novo_jogo->local_atual, mouse_novo, &novo_jogo->em_hitbox);
                        if (!novo_jogo->em_hitbox) SetMouseCursor(0);
    
                        bool terminou = MinigameUpdateBusca(
                            &novo_jogo->minigame,
                            novo_jogo->chave_atual,
                            mouse_novo,
                            GetFrameTime()
                        );
    
                        if (terminou) {
                            if (novo_jogo->minigame.fase == MINIGAME_FASE_SUCESSO) {
                                inserir_inventario(&novo_jogo->inventario, "Isqueiro",
                                                "Um isqueiro legal.",
                                                novo_jogo->isqueiro, 2);
                                insertion_sort_iventario(&novo_jogo->inventario);
                                MinigameFinalizar(&novo_jogo->minigame);
                                memset(&novo_jogo->minigame, 0, sizeof(MinigameState));
                                state = EXPLORACAO;
                            } else {
                                state = EXPLORACAO;
                                //state = MINIGAME_GAMEOVER;
                            }
                        }
                    } else if (state == MINIGAME_GAMEOVER) {
                        
                    }

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
                    
                    if ((state == EXPLORACAO || state == MINIGAME_AGUARDANDO_IA) && !dialogo_acabou_esse_frame) {
                        novo_jogo->em_hitbox = false;
                        mudar_local(novo_jogo->local_atual, novo_jogo->mapa, &novo_jogo->chave_atual, mouse_novo);
                        novo_jogo->local_atual = buscar_local(novo_jogo->mapa, novo_jogo->chave_atual);
                        novo_jogo->lenda_atual = pegar_lenda_atual(novo_jogo->lenda_local, novo_jogo->chave_atual);
                        PegarItemEEntrarInventário(&novo_jogo->itensNaoPegos, novo_jogo->chave_atual, mouse_novo, &novo_jogo->inventario, &novo_jogo->em_hitbox);
                        insertion_sort_iventario(&novo_jogo->inventario);
                        bool clicada = false;
                        if (state == EXPLORACAO) {
                            clicada = interagir_lenda(novo_jogo->lenda_atual, mouse_novo, &novo_jogo->em_hitbox);
                        }
                        mudar_mouse_mapa(novo_jogo->local_atual, mouse_novo, &novo_jogo->em_hitbox);
                        dar_item(&novo_jogo->lenda_local, novo_jogo->lenda_atual, &novo_jogo->itemSelecionado, mouse_novo, &novo_jogo->inventario, novo_jogo);
                        novo_jogo->lenda_atual = pegar_lenda_atual(novo_jogo->lenda_local, novo_jogo->chave_atual);

                        if (state == EXPLORACAO && !novo_jogo->minigame_ja_ocorreu &&
                            novo_jogo->quests_completas > novo_jogo->quests_no_ultimo_sorteio &&
                            novo_jogo->lenda_atual == NULL) {

                            int chance = novo_jogo->quests_completas * 100;
                            if (chance > 90) chance = 90;

                            if (GetRandomValue(1, 100) <= chance && gemini_retry_timer <= 0.0f) {
                                strncpy(novo_jogo->ultima_lenda_nome,
                                        novo_jogo->lenda_atual ? novo_jogo->lenda_atual->nome : "",
                                        sizeof(novo_jogo->ultima_lenda_nome) - 1);
                                if (!gemini_disabled) {
                                    if (GeminiPedirDialogo(
                                        &novo_jogo->gemini,
                                        novo_jogo->quests_completas,
                                        novo_jogo->ultima_lenda_nome
                                    )) {
                                        novo_jogo->minigame_ja_ocorreu = true;
                                        novo_jogo->quests_no_ultimo_sorteio = novo_jogo->quests_completas;
                                        state = MINIGAME_AGUARDANDO_IA;
                                    }
                                } else {
                                    MinigameIniciar(
                                        &novo_jogo->minigame,
                                        gemini_fallback_text,
                                        &novo_jogo->ouro1,
                                        &novo_jogo->ouro2,
                                        &novo_jogo->isqueiro
                                    );
                                    novo_jogo->minigame_ja_ocorreu = true;
                                    novo_jogo->quests_no_ultimo_sorteio = novo_jogo->quests_completas;
                                    state = MINIGAME_INTRO;
                                }
                            }
                        }

                        if (state == EXPLORACAO && clicada == true && novo_jogo->dialogo == NULL && !dialogo_acabou_esse_frame) {
                            Lendas *conversa = novo_jogo->lenda_atual;
                            if (conversa->quest_completa == false) {
                                if (conversa->ja_conversou == false) {
                                    novo_jogo->dialogo = CreateDialogueManager(conversa->dialogo_raiz);
                                    conversa->ja_conversou = true;
                                }
                                else {
                                    novo_jogo->dialogo = CreateDialogueManager(conversa->dialogo_repetido);
                                }
                            } else {
                                if (conversa->ja_conversou == false) {
                                    novo_jogo->dialogo = CreateDialogueManager(conversa->dialogo_final);
                                    conversa->ja_conversou = true;
                                    if (strcmp(conversa->nome, "Emparedada da Rua Nova") == 0) {
                                        inserir_inventario(&novo_jogo->inventario, "Mingau", "Um mingau quentinho.", conversa->item, 8);
                                        novo_jogo->quests_completas++;
                                    } else if (strcmp(conversa->nome, "Comadre Fulozinha") == 0) {
                                        inserir_inventario(&novo_jogo->inventario, "Bilhete de catamarã", "Um bilhete valendo um passeio de catamaran aqui em Recife.", conversa->item, 7);
                                        novo_jogo->quests_completas++;
                                    } else if (strcmp(conversa->nome, "Encanta Moça") == 0) {
                                        inserir_inventario(&novo_jogo->inventario, "Bolo de rolo", "Um bolo de rolo bem gostoso.", conversa->item, 6);
                                        novo_jogo->quests_completas++;
                                    } else if (strcmp(conversa->nome, "Cabra Cabriola") == 0) {
                                        inserir_inventario(&novo_jogo->inventario, "Tesoura", "Uma tesoura normal.", conversa->item, 5);
                                        novo_jogo->quests_completas++;
                                    } else if (strcmp(conversa->nome, "Papa-figo") == 0) {
                                        inserir_inventario(&novo_jogo->inventario, "Barbeador", "Um barbeador.", conversa->item, 4);
                                        novo_jogo->quests_completas++;
                                    } else if (strcmp(conversa->nome, "Perna Cabeluda") == 0) {
                                        inserir_inventario(&novo_jogo->inventario, "Crachá", "Um crachá da CESAR School.", conversa->item, 3);
                                        novo_jogo->quests_completas++;
                                    }
                                }
                                else {
                                    novo_jogo->dialogo = CreateDialogueManager(conversa->dialogo_final_repetido);
                                }
                            }
                            state = DIALOGO;    
                        }
                    }
                    
                    if (novo_jogo->em_hitbox == false && state != MINIGAME_BUSCA) {
                            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
                    }

                    //Desenhar na textura
                    BeginTextureMode(novo_jogo->tela);
                    
                        ClearBackground(BLACK);
                        DrawTexture(novo_jogo->enfeite, 0, 0, WHITE);
                        desenhar_local(novo_jogo->local_atual);
                        if (state == EXPLORACAO) {
                            desenhar_lendas(novo_jogo->lenda_atual);
                        } else if (state == DIALOGO) {
                            desenhar_lendas_conversa(novo_jogo->lenda_atual);
                        }

                        desenhar_inventario(novo_jogo->inventario, 90, 140, 140, novo_jogo->itemSelecionado);

                        ItemAparecerNoCenario(&novo_jogo->itensNaoPegos, novo_jogo->chave_atual);

                        // Atualiza clique e arrasto dos itens do inventário
                        atualizar_drag_inventario(novo_jogo->inventario, mouse_novo, &novo_jogo->itemSelecionado, &novo_jogo->arrastandoItem);
                        
                        // Desenha item sendo arrastado por cima da tela
                        if (novo_jogo->arrastandoItem){
                            desenhar_item_arrastando(mouse_novo, novo_jogo->itemSelecionado, novo_jogo->arrastandoItem);
                        }

                        if (state == DIALOGO) {
                            DrawDialogueManager(novo_jogo->dialogo);
                        } else if (state == MINIGAME_INTRO) {
                            MinigameDesenharIntro(&novo_jogo->minigame);
                        } else if (state == MINIGAME_BUSCA) {
                            MinigameDesenharBusca(&novo_jogo->minigame, novo_jogo->chave_atual, &novo_jogo->isqueiro);
                        } else if (state == MINIGAME_GAMEOVER) {
                            MinigameFinalizar(&novo_jogo->minigame);
                            memset(&novo_jogo->minigame, 0, sizeof(MinigameState));
                        }
                        
                    EndTextureMode();
                    
                    //Desenhar a textura
                    BeginDrawing();
                    ClearBackground(BLACK);
                    DrawTexturePro(novo_jogo->tela.texture, (Rectangle){0, 0, 1600, -900}, nova_tela, (Vector2){0, 0}, 0.0f, WHITE);
                    if (state == MINIGAME_AGUARDANDO_IA) {
                        DrawRectangle(0, 0, 1600, 900, (Color){0, 0, 0, 150});
                        DrawText("Aguardando resposta da IA...", 560, 420, 30, WHITE);
                    }
                    if (gemini_error_timer > 0.0f) {
                        DrawText("Gemini indisponível, usando fallback local.", 20, 860, 20, RED);
                        gemini_error_timer -= GetFrameTime();
                        if (gemini_error_timer < 0.0f) gemini_error_timer = 0.0f;
                    }
                    if (gemini_retry_timer > 0.0f && state != MINIGAME_AGUARDANDO_IA) {
                        char retry_message[128];
                        snprintf(retry_message, sizeof(retry_message), "Gerando localmente enquanto aguarda nova tentativa (%ds)...", (int)ceilf(gemini_retry_timer));
                        DrawText(retry_message, 20, 830, 20, YELLOW);
                    }
                    if (novo_jogo->em_hitbox) {
                        //DrawCircleGradient((Vector2){mouse.x, mouse.y}, 40 * escala, (Color){255, 255, 255, 100}, (Color){255, 255, 255, 0});
                        //DrawCircleLines(mouse.x, mouse.y, 20 * escala, WHITE);
                    }
                    EndDrawing();
                }  
                    
            }
                    
                     
        }
    
    GeminiFree(&novo_jogo->gemini);
    MinigameFinalizar(&novo_jogo->minigame);
    free_dados_jogo(novo_jogo);
    free(novo_jogo);

    CloseWindow();

    return 0;
}   
