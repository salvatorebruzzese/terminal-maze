#include "utilities.hpp"
#include "username.hpp"

constexpr int DIALOGUE_ROW    = 1;  // Dialogue row
constexpr int DIALOGUE_COL    = 3;  // Dialogue column

constexpr int ASK_ROW         = 3;  // Input row
constexpr int ASK_COL         = 3;  // Input column

constexpr int BRACKETS_ROW    = 3;  // Delimiter row
constexpr int BRACKET_LEFT    = 2;  // Delimiter columns
constexpr int BRACKET_RIGHT   = 17;

string ask_username() {
    
    WINDOW * username_window = new_boxed_window(POPUP_HEIGHT, POPUP_WIDTH);

    if (!username_window) {
        endwin();
        fprintf(stderr, "Unable to create username acquisition window\n");
        exit(2);
    }

    mvwprintw(username_window, DIALOGUE_ROW, DIALOGUE_COL, "Enter username");
    mvwprintw(username_window, BRACKETS_ROW, BRACKET_LEFT, "<");
    mvwprintw(username_window, BRACKETS_ROW, BRACKET_RIGHT, ">");
    
    wrefresh(username_window);

    echo(); curs_set(1);

    string new_username(MAX_USERNAME_LENGTH, '\0');
    int rc = mvwgetnstr(username_window, ASK_ROW, ASK_COL, new_username.data(), MAX_USERNAME_LENGTH);

    noecho(); curs_set(0);

    if (rc == ERR) {
        endwin();
        fprintf(stderr, "Unable to get username string\n");
        exit(3);
    }

    werase(username_window);
    wrefresh(username_window);
    delwin(username_window);
    return new_username;
}