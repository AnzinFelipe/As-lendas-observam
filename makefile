TARGET = As_Lendas_Observam
CC = gcc
CFLAGS   = -Wall -Wextra -O2 -I include -I external/raydial/include
LDFLAGS  = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

PASTA_SRC = source
PASTA_OBJ = objects
PASTA_INC = include 

SRCS = $(wildcard $(PASTA_SRC)/*.c)

RAYDIAL_SRCS = external/raydial/src/raydial.c external/raydial/src/raydial_i18n.c 
ALL_SRCS = $(SRCS) $(RAYDIAL_SRCS)

OBJS = $(patsubst %.c, $(PASTA_OBJ)/%.o, $(notdir $(ALL_SRCS)))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

$(PASTA_OBJ)/%.o: $(PASTA_SRC)/%.c | $(PASTA_OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(PASTA_OBJ)/%.o: external/raydial/src/%.c | $(PASTA_OBJ)
	$(CC) -w $(CFLAGS) -c $< -o $@

$(PASTA_OBJ):
	mkdir -p $(PASTA_OBJ)

run: all
	./$(TARGET)

clean:
	rm -rf $(PASTA_OBJ) $(TARGET)
