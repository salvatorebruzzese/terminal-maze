#include <string>
#include "curses.h"
#include "menu.hpp"
#include "username.hpp"
#include "utilities.hpp"

int main() {
    init_curses();

    std::string current_player = ask_username();
    menu(current_player);
    
    endwin();
}