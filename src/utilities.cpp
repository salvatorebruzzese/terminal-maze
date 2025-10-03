#include "utilities.hpp"

int center_string(int width, const char * str) {
    return width/2 - strlen(str)/2;
}

void init() {
    if (!initscr()) {
        fprintf(stderr, "Failed to initialize curses\n");
        exit(1);
    }

    curs_set(0);
    noecho();
    cbreak();
    refresh();
}

WINDOW* new_boxed_window(int height, int width) {
    if (height < 2 || width < 2) return nullptr;

    int sh, sw;
    getmaxyx(stdscr, sh, sw);

    if (height > sh || width > sw) return nullptr;

    int y = (sh - height) / 2;
    int x = (sw - width) / 2;

    WINDOW* win = newwin(height, width, y, x);
    if (!win) return nullptr;

    if (box(win, ACS_VLINE, ACS_HLINE) == ERR) {
        delwin(win);
        return nullptr;
    }

    if (wrefresh(win) == ERR) {
        delwin(win);
        return nullptr;
    }

    return win;
}