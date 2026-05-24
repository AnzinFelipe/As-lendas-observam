TARGET = As_Lendas_Observam
CC = gcc
CFLAGS   = -Wall -Wextra -O2 -I include -I external/raydial/include
PASTA_SRC = source
PASTA_OBJ = objects
PASTA_INC = include

SRCS         = $(wildcard $(PASTA_SRC)/*.c)
RAYDIAL_SRCS = external/raydial/src/raydial.c external/raydial/src/raydial_i18n.c
ALL_SRCS     = $(SRCS) $(RAYDIAL_SRCS)
OBJS         = $(patsubst %.c, $(PASTA_OBJ)/%.o, $(notdir $(ALL_SRCS)))

ifeq ($(OS),Windows_NT)
	EXE         = $(TARGET).exe
	W64_PATH    = C:/raylib/w64devkit
	RAYLIB_PATH = C:/raylib/raylib-5.0_win64_mingw-w64
	CURL_PATH   = C:/curl
	CC          = $(W64_PATH)/bin/gcc.exe
	export PATH := $(W64_PATH)/bin;$(PATH)
	CFLAGS     += -I$(RAYLIB_PATH)/include -I$(W64_PATH)/include -I$(CURL_PATH)/include
	LDFLAGS     = -L$(RAYLIB_PATH)/lib -L$(W64_PATH)/lib -L$(CURL_PATH)/lib \
	              -lraylib -lopengl32 -lgdi32 -lwinmm -lpthread -lcurl
else
	EXE     = $(TARGET)
	LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -lcurl
endif

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

$(PASTA_OBJ)/%.o: $(PASTA_SRC)/%.c | $(PASTA_OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(PASTA_OBJ)/%.o: external/raydial/src/%.c | $(PASTA_OBJ)
	$(CC) -w $(CFLAGS) -c $< -o $@

$(PASTA_OBJ):
	mkdir -p $(PASTA_OBJ)

run: all
	./$(EXE)

clean:
	rm -rf $(PASTA_OBJ) $(EXE)