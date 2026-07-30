#include "curses.h"
#include "menu.hpp"
#include "utilities.hpp"
#include <string>

constexpr int MENU_HEIGHT = 15;
constexpr int MENU_WIDTH = 30;

int main(void) {
    init_curses();

    std::vector<std::string> anchors = {
        {" New maze ", " Leaderboard ", " Exit "}};
    MainMenu menu(MENU_HEIGHT, MENU_WIDTH, anchors);
    menu.run();

    endwin();
}