#include "curses.h"
#include "game.hpp"
#include "utilities.hpp"

void game() {
    WINDOW * game_window = new_boxed_window(20, 60);

    wgetch(game_window);

    wclear(game_window);    
    wrefresh(game_window);
    delwin(game_window);
}