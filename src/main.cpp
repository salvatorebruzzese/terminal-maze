#include "utilities.hpp"
#include "menu.hpp"
#include "username.hpp"

int main(int argc, char ** argv) {
    init();

    string current_player = ask_username();
    menu(current_player);
    
    endwin();
}