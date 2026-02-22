#include <string>
#include "curses.h"
#include "menu.hpp"
#include "username.hpp"
#include "utilities.hpp"

int main(int argc, char ** argv) {
    init_curses();

    std::string current_player = ask_username();
    menu(current_player);
    
    endwin();
}