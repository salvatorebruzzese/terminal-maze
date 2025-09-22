#include "utilities.hpp"
#include "username.hpp"

void ask_username() {
    WINDOW * username_window = new_boxed_window(USER_HEIGHT, USER_WIDTH);

    string dialogue = "Enter username";
    string placeholders = "______________";

    mvwprintw(username_window, 1, 3, dialogue.data());
    
    mvwprintw(username_window, 3, 3, placeholders.data());
    
    wrefresh(username_window);

    echo(); curs_set(1);

    string new_username(MAX_USERNAME_LENGTH, '\0');
    if (mvwgetnstr(username_window, 3, 3, new_username.data(), new_username.size()) == ERR) 
        new_username.clear();
    new_username.resize((new_username.length()));

    noecho(); curs_set(0); delwin(username_window);
}