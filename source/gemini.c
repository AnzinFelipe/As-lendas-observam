    #include "gemini.h"
    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>
    #include <curl/curl.h>

    #define GEMINI_URL "https://generativelanguage.googleapis.com/v1beta/models/gemini-2.0-flash:generateContent?key="

    // Leitura da chave
    static int ler_chave_api(char *dest, int dest_size) {
        const char *env = getenv("GEMINI_API_KEY");
        if (env && strlen(env) > 0) {
            strncpy(dest, env, dest_size - 1);
            dest[dest_size - 1] = '\0';
            return 1;
        }

        FILE *f = fopen("gemini.key", "r");
        if (!f) return 0;
        if (fgets(dest, dest_size, f)) {
            dest[strcspn(dest, "\r\n")] = '\0';
            fclose(f);
            return strlen(dest) > 0;
        }
        fclose(f);
        return 0;
    }

    // Buffer para acumular a resposta HTTP
    typedef struct {
        char *data;
        size_t tamanho;
    } CurlBuffer;

    static size_t curl_write_cb(void *conteudo, size_t size, size_t nmemb, void *userp) {
        size_t total = size * nmemb;
        CurlBuffer *buf = (CurlBuffer *)userp;
        char *novo = realloc(buf->data, buf->tamanho + total + 1);
        if (!novo) return 0;
        buf->data = novo;
        memcpy(buf->data + buf->tamanho, conteudo, total);
        buf->tamanho += total;
        buf->data[buf->tamanho] = '\0';
        return total;
    }

    // Extrai o texto da resposta JSON
    static void extrair_texto(const char *json, char *dest, int dest_size) {
        const char *p = strstr(json, "\"text\"");
        while (p) {
            p += strlen("\"text\"");
            while (*p && (*p == ' ' || *p == '\t' || *p == '\r' || *p == '\n')) p++;
            if (*p != ':') {
                p = strstr(p, "\"text\"");
                continue;
            }
            p++;
            while (*p && (*p == ' ' || *p == '\t' || *p == '\r' || *p == '\n')) p++;
            if (*p != '"') {
                p = strstr(p, "\"text\"");
                continue;
            }
            p++;

            int i = 0;
            while (*p && i < dest_size - 1) {
                if (*p == '\\') {
                    p++;
                    if (*p == '"')  { dest[i++] = '"'; }
                    else if (*p == 'n')  { dest[i++] = ' '; }
                    else if (*p == 'r')  { dest[i++] = ' '; }
                    else if (*p == 't')  { dest[i++] = ' '; }
                    else if (*p == '\\') { dest[i++] = '\\'; }
                    else { dest[i++] = *p; }
                    if (*p) p++;
                    continue;
                }
                if (*p == '"') break;
                dest[i++] = *p++;
            }
            dest[i] = '\0';
            return;
        }

        strncpy(dest, "As lendas te observam em silencio...", dest_size - 1);
        dest[dest_size - 1] = '\0';
    }

    // Thread
    typedef struct {
        GeminiContext *ctx;
        char prompt[1024];
    } ThreadArgs;

    static void *gemini_thread_func(void *arg) {
        ThreadArgs *args = (ThreadArgs *)arg;
        GeminiContext *ctx = args->ctx;

        char resposta_local[GEMINI_RESPOSTA_MAX] =
            "Eu vejo tudo o que voce faz nessas ruas... nao vai escapar.";

        // Lê a chave
        char api_key[256] = "";
        bool sucesso = false;
        if (!ler_chave_api(api_key, sizeof(api_key))) {
            goto finalizar; // sem chave: usa fallback e não trava o jogo
        }

        {
            // Monta a URL
            char url[512];
            snprintf(url, sizeof(url), "%s%s", GEMINI_URL, api_key);

            // Monta o corpo JSON
            char body[2048];
            snprintf(body, sizeof(body),
                "{\"contents\":[{\"parts\":[{\"text\":\"%s\"}]}],"
                "\"generationConfig\":{\"maxOutputTokens\":80,\"temperature\":0.9}}",
                args->prompt);

            // Inicializa buffer
            CurlBuffer buf = {NULL, 0};
            buf.data = malloc(1);
            buf.data[0] = '\0';

            CURL *curl = curl_easy_init();
            if (curl) {
                struct curl_slist *headers = NULL;
                headers = curl_slist_append(headers, "Content-Type: application/json");
                
                curl_easy_setopt(curl, CURLOPT_URL, url);
                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body);
                curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_write_cb);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buf);
                curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
                
                CURLcode res = curl_easy_perform(curl);
                long http_code = 0;
                curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
                printf("HTTP %ld\nResposta: %s\n", http_code, buf.data ? buf.data : "(vazio)");

                if (res == CURLE_OK && http_code == 200 && buf.data) {
                    extrair_texto(buf.data, resposta_local, GEMINI_RESPOSTA_MAX);
                    sucesso = true;
                } else if (http_code == 429) {
                    snprintf(resposta_local, sizeof(resposta_local),
                            "Erro Gemini: TooManyRequests (limite de requisições atingido)");
                } else if (buf.data && strlen(buf.data) > 0) {
                    snprintf(resposta_local, sizeof(resposta_local),
                            "Erro Gemini: HTTP %ld", http_code);
                }

                curl_slist_free_all(headers);
                curl_easy_cleanup(curl);
            }

            free(buf.data);
        }

    finalizar:
        pthread_mutex_lock(&ctx->mutex);
        strncpy(ctx->resposta, resposta_local, GEMINI_RESPOSTA_MAX - 1);
        ctx->resposta[GEMINI_RESPOSTA_MAX - 1] = '\0';
        ctx->status = sucesso ? GEMINI_PRONTO : GEMINI_ERRO;
        pthread_mutex_unlock(&ctx->mutex);
        free(args);
        return NULL;
    }

    // API pública

    void GeminiInit(GeminiContext *ctx) {
        memset(ctx, 0, sizeof(GeminiContext));
        ctx->status = GEMINI_IDLE;
        pthread_mutex_init(&ctx->mutex, NULL);
        curl_global_init(CURL_GLOBAL_DEFAULT);
    }

    void GeminiFree(GeminiContext *ctx) {
        pthread_mutex_lock(&ctx->mutex);
        GeminiStatus s = ctx->status;
        pthread_mutex_unlock(&ctx->mutex);
        if (s == GEMINI_LOADING) {
            pthread_join(ctx->thread, NULL);
        }
        pthread_mutex_destroy(&ctx->mutex);
        curl_global_cleanup();
    }

    bool GeminiPedirDialogo(GeminiContext *ctx, int quests_completas, const char *ultima_lenda) {
        pthread_mutex_lock(&ctx->mutex);
        GeminiStatus s = ctx->status;
        pthread_mutex_unlock(&ctx->mutex);
        if (s == GEMINI_LOADING) return false;

        ThreadArgs *args = malloc(sizeof(ThreadArgs));
        if (!args) return false;

        args->ctx = ctx;
        snprintf(args->prompt, sizeof(args->prompt),
            "Voce e Boca de Ouro, uma lenda do Recife Antigo, misteriosa e intimidadora, "
            "que observa silenciosamente as acoes de um viajante pelas ruas historicas. "
            "O viajante ja completou %d quests e a ultima lenda com quem interagiu foi: %s. "
            "Fale diretamente com ele em 2 frases curtas em portugues do Brasil, "
            "tom ameacador e misterioso, referenciando o que ele fez recentemente. "
            "Responda APENAS o dialogo, sem aspas, sem narracao, sem introducao.",
            quests_completas,
            ultima_lenda && strlen(ultima_lenda) > 0 ? ultima_lenda : "nenhuma ainda");

        pthread_mutex_lock(&ctx->mutex);
        ctx->status = GEMINI_LOADING;
        pthread_mutex_unlock(&ctx->mutex);

        if (pthread_create(&ctx->thread, NULL, gemini_thread_func, args) != 0) {
            pthread_mutex_lock(&ctx->mutex);
            ctx->status = GEMINI_ERRO;
            pthread_mutex_unlock(&ctx->mutex);
            free(args);
            return false;
        }

        pthread_detach(ctx->thread);
        return true;
    }

    GeminiStatus GeminiGetStatus(GeminiContext *ctx) {
        pthread_mutex_lock(&ctx->mutex);
        GeminiStatus s = ctx->status;
        pthread_mutex_unlock(&ctx->mutex);
        return s;
    }

    void GeminiPegarResposta(GeminiContext *ctx, char *dest, int dest_size) {
        pthread_mutex_lock(&ctx->mutex);
        strncpy(dest, ctx->resposta, dest_size - 1);
        dest[dest_size - 1] = '\0';
        ctx->status = GEMINI_IDLE;
        pthread_mutex_unlock(&ctx->mutex);
    }