CC = clang
CFLAGS = -g -std=c99 -Wall

GEN_SOURCES = ttt.c
GEN_HEADERS = ttt.h

.PHONY: all clean

all: ttt

ttt: $(GEN_SOURCES) $(GEN_HEADERS)
	$(CC) $(CFLAGS) $(GEN_SOURCES) -o $@
clean:
	rm -f ttt
	rm -rf ttt.dSYM
