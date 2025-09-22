#include "utilities.hpp"
#include "menu.hpp"
#include "username.hpp"

int main(int argc, char ** argv) {
    init();

    ask_username();
    menu();
    
    endwin();
}