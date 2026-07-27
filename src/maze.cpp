#include "maze.hpp"
#include "curses.h"
#include "utilities.hpp"
#include <random>
#include <vector>

void gridify(WINDOW* game_window, std::vector<pair>& walls) {
    // Overestimate number of walls
    walls.reserve(GAME_HEIGHT_NO_BORDERS * GAME_WIDTH_NO_BORDERS);

    for (int y = 1; y <= GAME_HEIGHT_NO_BORDERS; y++) {
        for (int x = 1; x <= GAME_WIDTH_NO_BORDERS; x++) {
            if ((y % 2 == 1 && x % 2 == 0) || y % 2 == 0) {
                if (x % 2 != 0)
                    walls.emplace_back(y, x);
                mvwadd_wch(game_window, y, x, WACS_BLOCK);
            }
        }
        wrefresh(game_window);
        napms(20);
    }
}

// TODO: Randomize the end marker position
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

void kruskal(std::vector<pair> walls) {
    dsu cells;

    std::random_device rd;
    std::ranlux48_base generator(rd());
    std::uniform_int_distribution<int> dist(1, walls.size());

    while (walls.size() != 0) {
        int random_index = dist(generator);
        pair pos = walls.at(random_index % walls.size());
    }
}

void maze(WINDOW* game_window) {
    std::vector<pair> walls;
    gridify(game_window, walls);

    start_end_markers(game_window);
}