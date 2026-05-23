#ifndef GROQ_H
#define GROQ_H

#include <stdbool.h>
#include <pthread.h>

#define GROQ_RESPOSTA_MAX 512

typedef enum {
    GROQ_IDLE,       
    GROQ_LOADING,    
    GROQ_PRONTO,     
    GROQ_ERRO        
} GroqStatus;

// Contexto da thread
typedef struct {
    char prompt[1024];
    char resposta[GROQ_RESPOSTA_MAX];
    GroqStatus status;
    pthread_t thread;
    pthread_mutex_t mutex;
} GroqContext;

void GroqInit(GroqContext *ctx);

void GroqFree(GroqContext *ctx);

bool GroqPedirDialogo(GroqContext *ctx, const char *ultima_lenda);

GroqStatus GroqGetStatus(GroqContext *ctx);

void GroqPegarResposta(GroqContext *ctx, char *dest, int dest_size);

#endif