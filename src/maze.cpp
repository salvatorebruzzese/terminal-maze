#include "maze.hpp"
#include "dsu.hpp"
#include "utilities.hpp"
#include <algorithm>
#include <stdexcept>

MazeGenerator::MazeGenerator(WINDOW* game_window)
    : game_window_(game_window), generator_(std::random_device{}()) {}

pair MazeGenerator::generate() {
    walls_.clear();
    gridify();
    kruskal();
    return start_end_markers();
}

void MazeGenerator::gridify() {
    // Overestimate number of walls
    walls_.reserve(GAME_HEIGHT_NO_BORDERS * GAME_WIDTH_NO_BORDERS);

    wattron(game_window_, A_REVERSE);

    for (int y = 1; y <= GAME_HEIGHT_NO_BORDERS; y++) {
        for (int x = 1; x <= GAME_WIDTH_NO_BORDERS; x++) {
            if (y % 2 == 0 && x % 2 == 0) {
                mvwaddch(game_window_, y, x, ' ');
            } else if ((y % 2 == 1 && x % 2 == 0) ||
                       (y % 2 == 0 && x % 2 == 1)) {
                walls_.emplace_back(y, x);
                mvwaddch(game_window_, y, x, ' ');
            }
        }
        wrefresh(game_window_);
        napms(20);
    }

    wattroff(game_window_, A_REVERSE);
}

void MazeGenerator::kruskal() {
    dsu cells;

    std::shuffle(walls_.begin(), walls_.end(), generator_);

    while (!walls_.empty()) {
        pair wall = walls_.back();
        walls_.pop_back();

        pair cell1, cell2;

        // Up and down cells
        if (wall.first % 2 == 0 && wall.second % 2 == 1) {
            cell1 = {wall.first - 1, wall.second};
            cell2 = {wall.first + 1, wall.second};
        } // Left and right cells
        else if (wall.first % 2 == 1 && wall.second % 2 == 0) {
            cell1 = {wall.first, wall.second - 1};
            cell2 = {wall.first, wall.second + 1};
        } else {
            continue;
        }

        try {
            if (cells.find(cell1) != cells.find(cell2)) {
                cells.merge(cell1, cell2);
                mvwaddch(game_window_, wall.first, wall.second, ' ');
                wrefresh(game_window_);
                napms(3);
            }
        } catch (const std::out_of_range& e) {
            continue;
        }
    }
}

pair MazeGenerator::start_end_markers() {
    std::uniform_int_distribution<> height(0, GAME_HEIGHT);

    int s_mark, e_mark;

    do {
        s_mark = height(generator_);
        e_mark = height(generator_);
    } while (mvwinch(game_window_, s_mark, FIRST_COLUMN) != ' ' ||
             mvwinch(game_window_, e_mark, LAST_COLUMN) != ' ');

    wattron(game_window_, COLOR_PAIR(1));
    mvwaddch(game_window_, s_mark, FIRST_COLUMN, ' ');
    wattroff(game_window_, COLOR_PAIR(1));

    wattron(game_window_, COLOR_PAIR(2));
    mvwaddch(game_window_, e_mark, LAST_COLUMN, ' ');
    wattroff(game_window_, COLOR_PAIR(2));

    wrefresh(game_window_);
    return pair(s_mark, e_mark);
}