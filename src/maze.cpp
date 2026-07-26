#include "maze.hpp"
#include "curses.h"
#include "utilities.hpp"

void gridify(WINDOW* game_window) {

    for (int starting_y = 1; starting_y <= GAME_HEIGHT_NO_BORDERS;
         starting_y++) {
        for (int starting_x = 1; starting_x <= GAME_WIDTH_NO_BORDERS;
             starting_x++) {
            if (starting_y % 2 == 0 && starting_x % 2 == 1) {
                mvwadd_wch(game_window, starting_y, starting_x, WACS_BLOCK);
            } else if (starting_y % 2 == 1 && starting_x % 2 == 0)
                mvwadd_wch(game_window, starting_y, starting_x, WACS_BLOCK);
        }
        wrefresh(game_window);
        napms(20);
    }
}

void maze(WINDOW* game_window) {}

void start_end_markers(WINDOW* game_window) {

    wattron(game_window, COLOR_PAIR(1));
    mvwadd_wch(game_window, TOP_LEFT_CORNER, TOP_LEFT_CORNER, WACS_BLOCK);
    wattroff(game_window, COLOR_PAIR(1));

    wattron(game_window, COLOR_PAIR(2));
    mvwadd_wch(game_window, BOTTOM_RIGHT_CORNER_Y, BOTTOM_RIGHT_CORNER_X,
               WACS_BLOCK);
    wattroff(game_window, COLOR_PAIR(2));

    wrefresh(game_window);
}