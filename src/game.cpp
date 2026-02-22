#include <string>
#include "curses.h"
#include "game.hpp"
#include "utilities.hpp"

void game(const std::string & current_player) {
    WINDOW * game_window = new_boxed_window(GAME_HEIGHT, GAME_WIDTH);

    wgetch(game_window);
    /*
    std::vector<bool> walls = gen_walls();
    show_walls(walls);
    coordinates player_coordinates = gen_player();
    time_start = clock::now();
    while (true) {
        if (check_win() = true) break;

        direction dir = get_input();    // timed input
        check_wall(dir, player_coordinates, walls);
        show_player(dir);
        time_header(game_window);
        score = time_played();
    }
    */

    // update_ranking(current_player, score);
    wclear(game_window);
    wrefresh(game_window);
    delwin(game_window);
}