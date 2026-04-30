TARGET = As_Lendas_Observam
CC = gcc
CFLAGS   = -Wall -Wextra -O2 -I include
LDFLAGS  = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

PASTA_SRC = source
PASTA_OBJ = objects
PASTA_INC = include 

SRCS = $(wildcard $(PASTA_SRC)/*.c)
OBJS = $(patsubst $(PASTA_SRC)/%.c, $(PASTA_OBJ)/%.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

$(PASTA_OBJ)/%.o: $(PASTA_SRC)/%.c | $(PASTA_OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(PASTA_OBJ):
	mkdir -p $(PASTA_OBJ)

run: all
	./$(TARGET)

clean:
	rm -rf $(PASTA_OBJ) $(TARGET)
