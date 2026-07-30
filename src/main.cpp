#include "curses.h"
#include "menu.hpp"
#include "utilities.hpp"

constexpr int MENU_HEIGHT = 15;
constexpr int MENU_WIDTH = 30;

int main(void) {
    init_curses();

    MainMenu menu(MENU_HEIGHT, MENU_WIDTH);
    menu.run();

    endwin();
}