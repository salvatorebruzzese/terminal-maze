#include <array>
#include "curses.h"
#include "maze.hpp"

void gridify(WINDOW * game_window) {
    int starting_y = 1;
    while (starting_y <= GAME_HEIGHT_NO_BORDERS) {
        if ((starting_y - 1) % 2 == 0) {
            bool is_a_wall = false;
            for (int starting_x = 1; starting_x <= GAME_WIDTH_NO_BORDERS; starting_x++) {
                if (is_a_wall) {
                    mvwaddch(game_window, starting_y, starting_x, ACS_BLOCK);
                    is_a_wall = false;
                }
                else is_a_wall = true;
            }
        } else {
            for (int starting_x = 1; starting_x <= GAME_WIDTH_NO_BORDERS; starting_x++) {
                mvwaddch(game_window, starting_y, starting_x, ACS_BLOCK);
            }
        }
        wrefresh(game_window);
        napms(20);
        starting_y++;
    }
}

void start_end_markers(WINDOW * game_window) {

    int top_left_y = 1;
    int top_left_x = 1;
    int bottom_right_y = GAME_HEIGHT - 2;
    int bottom_right_x = GAME_WIDTH - 2;

    mvwaddch(game_window, top_left_y, top_left_x, ACS_BLOCK | COLOR_PAIR(1));

    mvwaddch(game_window, bottom_right_y, bottom_right_x, ACS_BLOCK | COLOR_PAIR(2));
    
    wrefresh(game_window);
}