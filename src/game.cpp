#include "game.hpp"
#include "curses.h"
#include "maze.hpp"
#include "utilities.hpp"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <time.h>

#define CLOCK_X (GAME_WIDTH - 10)
#define CLOCK_Y 0

void timer(WINDOW* game_window, std::time_t start) {
    double elapsed = difftime(std::time(nullptr), start);

    std::string elapsed_str = std::to_string((int)elapsed);

    mvwprintw(game_window, CLOCK_Y, CLOCK_X, "Time:   %s", elapsed_str.c_str());
}

void game(const std::string& current_player) {
    WINDOW* game_window = new_boxed_window(GAME_HEIGHT, GAME_WIDTH);

    if (!game_window) {
        endwin();
        fprintf(stderr, "Unable to create game window\n");
        exit(4);
    };

    maze(game_window);

    // coordinates player_coordinates = gen_player();
    std::time_t start = std::time(nullptr);
    while (true) {
        // if (check_win() = true)
        //    score = time_played();
        //            break;

        // direction dir = get_input(); // timed input
        //  check_wall(dir, player_coordinates, walls);
        //   show_player(dir);
        timer(game_window, start);
        break;
    }

    // update_ranking(current_player, score);
    wgetch(game_window);
    wclear(game_window);
    wrefresh(game_window);
    delwin(game_window);
}