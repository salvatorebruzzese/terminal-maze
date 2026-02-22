#include <cstdio>
#include <cstdlib>
#include <string>
#include "curses.h"
#include "game.hpp"
#include "maze.hpp"
#include "utilities.hpp"

void game(const std::string & current_player) {
    WINDOW * game_window = new_boxed_window(GAME_HEIGHT, GAME_WIDTH);

    if (!game_window) {
        endwin();
        fprintf(stderr, "Unable to create game window\n");
        exit(4);
    };

    gridify(game_window);
    start_end_markers(game_window);
    wgetch(game_window);
    /*
    show_walls(walls);
    coordinates player_coordinates = gen_player();
    starting_time = clock::now();
    while (true) {
        if (check_win() = true) break;

        direction dir = get_input();    // timed input
        check_wall(dir, player_coordinates, walls);
        show_player(dir);
        time_header(game_window, starting_time);
        score = time_played();
    }
    */

    // update_ranking(current_player, score);
    wclear(game_window);
    wrefresh(game_window);
    delwin(game_window);
}