#include "./ttt.h"

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define NUM_WORDS 9  // TODO: don't hardcode

int main(int argc, char const *argv[]) {
    // TODO: use argc and argv to display (or not) an options menu
    char *str = "The quick brown fox jumps over the lazy dog.";

    initscr();
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_BLACK, COLOR_BLUE);
    } else {
        // TODO: address this case. for now, just exit
        fprintf(stderr, "error: terminal colors not available\n");
        finish(1);
    }
    noecho();

    struct timeval start;
    struct timeval end;

    printw("%s\n", str);
    printw("\nYour test will begin when you press the first letter...");
    // TODO: have this line (^) change to wpm during the middle of the test,
    // then the results afterwards
    refresh();

    move(0, 0);  // TODO: don't hardcode
    attrset(COLOR_PAIR(1));

    int started = 0;

    while (*str) {
        char ch = getch();
        if (!started) {
            // start timer
            if (gettimeofday(&start, NULL)) {
                // TODO: how does perror work in ncurses?
                perror("gettimeofday");
                finish(1);
            }
            started = 1;
        }

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

    attrset(COLOR_PAIR(0));

    long delta_sec = end.tv_sec - start.tv_sec;
    long delta_usec = end.tv_usec - start.tv_usec;

    float sec = delta_sec + (float)delta_usec / 1000000;
    float min = sec / 60;
    float wpm = NUM_WORDS / min;

    printw("\n\nTook %.2fs (%.0f wpm). Press any key to exit.", sec, wpm);
    refresh();

    getch();

    finish(0);
}

static void finish(int status) {
    if (endwin()) {
        fprintf(stderr, "error: while closing ncurses window\n");
    }
    exit(status);
}
