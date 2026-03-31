#include "username.hpp"
#include "curses.h"
#include "utilities.hpp"
#include <cstdio>
#include <cstdlib>
#include <string>

constexpr int DIALOGUE_ROW = 2; // Dialogue row
constexpr int DIALOGUE_COL = 3; // Dialogue column

constexpr int ASK_ROW = 4; // Input row
constexpr int ASK_COL = 3; // Input column

constexpr int INPUT_LENGTH = 14;

std::string ask_username() {

    WINDOW* username_window = new_boxed_window(POPUP_HEIGHT, POPUP_WIDTH);

    if (!username_window) {
        endwin();
        fprintf(stderr, "Unable to create username acquisition window\n");
        exit(2);
    }

    mvwprintw(username_window, DIALOGUE_ROW, DIALOGUE_COL, "Enter username");

    for (int i = 0; i < INPUT_LENGTH; i++) {
        mvwaddch(username_window, ASK_ROW, ASK_COL + i, ACS_BLOCK);
    }

    wrefresh(username_window);

    echo();
    curs_set(1);
    wattron(username_window, A_REVERSE);

    std::string new_username(MAX_USERNAME_LENGTH, '\0');
    int rc = mvwgetnstr(username_window, ASK_ROW, ASK_COL, new_username.data(),
                        MAX_USERNAME_LENGTH);

    noecho();
    curs_set(0);
    wattroff(username_window, A_REVERSE);

    if (rc == ERR) {
        endwin();
        fprintf(stderr, "Unable to get username std::string\n");
        exit(3);
    }

    werase(username_window);
    wrefresh(username_window);
    delwin(username_window);
    return new_username;
}