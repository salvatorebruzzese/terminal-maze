#include "utilities.hpp"

void init() {
    initscr();
    curs_set(0);
    noecho();
    refresh();
}

WINDOW * new_boxed_window(int height, int width) {
    int screen_height = getmaxy(stdscr);
    int screen_width = getmaxx(stdscr);

    if (height > screen_height || width > screen_width) return nullptr;

    WINDOW * win = newwin(height, width, screen_height/2 - height/2, screen_width/2 - width/2);

    box(win, ACS_VLINE, ACS_HLINE);

    wrefresh(win);

    return win;
}