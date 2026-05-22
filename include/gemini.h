#ifndef GEMINI_H
#define GEMINI_H

#include <stdbool.h>
#include <pthread.h>

#define GEMINI_RESPOSTA_MAX 512

typedef enum {
    GEMINI_IDLE,       
    GEMINI_LOADING,    
    GEMINI_PRONTO,     
    GEMINI_ERRO        
} GeminiStatus;

// Contexto da thread
typedef struct {
    char prompt[1024];
    char resposta[GEMINI_RESPOSTA_MAX];
    GeminiStatus status;
    pthread_t thread;
    pthread_mutex_t mutex;
} GeminiContext;

void GeminiInit(GeminiContext *ctx);

void GeminiFree(GeminiContext *ctx);

bool GeminiPedirDialogo(GeminiContext *ctx, int quests_completas, const char *ultima_lenda);

GeminiStatus GeminiGetStatus(GeminiContext *ctx);

void GeminiPegarResposta(GeminiContext *ctx, char *dest, int dest_size);

#endif