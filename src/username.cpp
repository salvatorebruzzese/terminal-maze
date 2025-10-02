#include "utilities.hpp"
#include "username.hpp"

string ask_username() {
    
    WINDOW * username_window = new_boxed_window(POPUP_HEIGHT, POPUP_WIDTH);

    string dialogue     = "Enter username";

    mvwprintw(username_window, 1, 3, dialogue.c_str());
    mvwprintw(username_window, 3, 2, "<");
    mvwprintw(username_window, 3, 17, ">");
    
    wrefresh(username_window);

    echo(); curs_set(1);

    string new_username(MAX_USERNAME_LENGTH, '\0');
    if (mvwgetnstr(username_window, 3, 3, new_username.data(), new_username.size()) == ERR) 
        new_username.clear();
    
    std::erase(new_username, '_');
    new_username.resize((new_username.length()));

    noecho(); curs_set(0);
    delwin(username_window);

    return new_username;
}