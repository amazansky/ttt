#include "./ttt.h"

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define NUM_WORDS 9  // TODO: don't hardcode

int main(int argc, char const *argv[]) {
    char *str = "The quick brown fox jumps over the lazy dog.";

    initscr();
    noecho();

    struct timeval start;
    struct timeval end;

    // TODO: make it so that the first keypress of the test starts the timer
    printw("Press any key to begin...\n");
    refresh();

    getch();  // start timer on keypress
    printw("%s\n", str);
    refresh();
    if (gettimeofday(&start, NULL)) {
        perror("gettimeofday");  // TODO: how does perror work in ncurses?
        finish(1);
    }

    while (*str) {
        char ch = getch();
        if (ch == ERR) {
            finish(1);
        } else if (ch == str[0]) {
            // TODO: change vscode format style to line break on else-ifs
            addch(ch);
            refresh();
            str++;
        }
    }

    if (gettimeofday(&end, NULL)) {
        perror("gettimeofday");
        finish(1);
    }

    long delta_sec = end.tv_sec - start.tv_sec;
    long delta_usec = end.tv_usec - start.tv_usec;

    float sec = delta_sec + (float)delta_usec / 1000000;
    float min = sec / 60;
    float wpm = NUM_WORDS / min;

    printw("\nTook %.2fs (%.0f wpm). Press any key to exit.\n", sec, wpm);
    refresh();

    getch();

    finish(0);
}

static void finish(int status) {
    if (endwin()) {
        fprintf(stderr, "error closing ncurses window");
    }
    exit(status);
}
