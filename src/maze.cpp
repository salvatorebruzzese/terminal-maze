#include "maze.hpp"
#include "curses.h"
#include "utilities.hpp"
#include <algorithm>
#include <exception>
#include <random>
#include <stdexcept>
#include <vector>

void gridify(WINDOW* game_window, std::vector<pair>& walls) {
    // Overestimate number of walls
    walls.reserve(GAME_HEIGHT_NO_BORDERS * GAME_WIDTH_NO_BORDERS);

    for (int y = 1; y <= GAME_HEIGHT_NO_BORDERS; y++) {
        for (int x = 1; x <= GAME_WIDTH_NO_BORDERS; x++) {
            if (y % 2 == 0 && x % 2 == 0) {
                mvwadd_wch(game_window, y, x, WACS_BLOCK);
            } else if ((y % 2 == 1 && x % 2 == 0) ||
                       (y % 2 == 0 && x % 2 == 1)) {
                walls.emplace_back(y, x);
                mvwadd_wch(game_window, y, x, WACS_BLOCK);
            }
        }
        wrefresh(game_window);
        napms(20);
    }
}

// Implementation note: the first mark is the y of the start position marker
// whereas the second mark is the y of the target cell to reach.
markers start_end_markers(WINDOW* game_window) {

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> height(0, GAME_HEIGHT);

    markers mark;
    char char1[2], char2[2];
    do {
        mark.first = height(generator);
        mark.second = height(generator);
        mvwinnstr(game_window, mark.first, FIRST_COLUMN, char1, READCHAR);
        mvwinnstr(game_window, mark.second, LAST_COLUMN, char2, READCHAR);
        char1[1] = '\0';
        char2[1] = '\0';
    } while (char1[0] != ' ' || char2[0] != ' ');

    wattron(game_window, COLOR_PAIR(1));
    mvwadd_wch(game_window, mark.first, FIRST_COLUMN, WACS_BLOCK);
    wattroff(game_window, COLOR_PAIR(1));

    wattron(game_window, COLOR_PAIR(2));
    mvwadd_wch(game_window, mark.second, LAST_COLUMN, WACS_BLOCK);
    wattroff(game_window, COLOR_PAIR(2));

    wrefresh(game_window);
    return mark;
}

void kruskal(WINDOW* game_window, std::vector<pair> walls) {
    dsu cells;

    std::random_device rd;
    std::mt19937 generator(rd());
    std::shuffle(walls.begin(), walls.end(), generator);

    while (!walls.empty()) {
        pair wall = walls.back();
        walls.pop_back();

        pair cell1, cell2;

        // Up and down cells
        if (wall.first % 2 == 0 && wall.second % 2 == 1) {
            cell1 = {wall.first - 1, wall.second};
            cell2 = {wall.first + 1, wall.second};
        } // Left and right cells
        else if (wall.first % 2 == 1 && wall.second % 2 == 0) {
            cell1 = {wall.first, wall.second - 1};
            cell2 = {wall.first, wall.second + 1};
        } else
            continue;

        try {
            if (cells.find(cell1) != cells.find(cell2)) {
                cells.merge(cell1, cell2);
                mvwaddch(game_window, wall.first, wall.second, ' ');
                wrefresh(game_window);
                napms(3);
            }
        } catch (const std::out_of_range& e) {
            continue;
        }
    }
}

markers maze(WINDOW* game_window) {
    std::vector<pair> walls;
    gridify(game_window, walls);

    kruskal(game_window, walls);
    return start_end_markers(game_window);
}