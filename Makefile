CC = clang
CFLAGS = -g -std=c99 -Wall -Wextra -Wpedantic
LFLAGS = -lncurses

GEN_SOURCES = ttt.c
GEN_HEADERS = ttt.h

.PHONY: all clean

all: ttt

ttt: $(GEN_SOURCES) $(GEN_HEADERS)
	$(CC) $(CFLAGS) -o $@ $(GEN_SOURCES) $(LFLAGS)
clean:
	rm -f ttt
	rm -rf ttt.dSYM
