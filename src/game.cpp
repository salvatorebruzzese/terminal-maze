#include "game.hpp"
#include "curses.h"
#include "maze.hpp"
#include "menu.hpp"
#include "ranking.hpp"
#include "username.hpp"
#include "utilities.hpp"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <time.h>

#define CLOCK_X (GAME_WIDTH - 10)
#define CLOCK_Y 0

int timer(WINDOW* game_window, std::time_t start) {
    int elapsed = difftime(std::time(nullptr), start);

    std::string elapsed_str = std::to_string(elapsed);

    mvwprintw(game_window, CLOCK_Y, CLOCK_X, "Time: %s", elapsed_str.c_str());
    wrefresh(game_window);
    return elapsed;
}

int get_input(WINDOW* game_window) {
    int input = wgetch(game_window);
    if (input == KEY_UP || input == KEY_DOWN || input == KEY_LEFT ||
        input == KEY_RIGHT)
        return input;
    else if (input == 'p' || input == 'P')
        return 'p';
    else
        return ERR;
}

void update_window(WINDOW* game_window, int dir, pair& player) {
    int next_y = player.first;
    int next_x = player.second;

    switch (dir) {
    case KEY_UP:
        next_y -= 1;
        break;
    case KEY_DOWN:
        next_y += 1;
        break;
    case KEY_LEFT:
        next_x -= 1;
        break;
    case KEY_RIGHT:
        next_x += 1;
        break;
    default:
        return;
    }

    chtype extracted = mvwinch(game_window, next_y, next_x);

    if ((extracted & A_REVERSE) == 0) {
        mvwaddch(game_window, player.first, player.second, ' ');
        player = {next_y, next_x};
        wattron(game_window, COLOR_PAIR(1));
        mvwaddch(game_window, player.first, player.second, ' ');
        wattroff(game_window, COLOR_PAIR(1));
    }

    wrefresh(game_window);
}

bool pause_menu() {

    PauseMenu pause(9, 14);
    return pause.run();
}

void game() {
    const std::string current_player = ask_username();

    WINDOW* game_window = new_boxed_window(GAME_HEIGHT, GAME_WIDTH);

    if (!game_window) {
        endwin();
        fprintf(stderr, "Unable to create game window\n");
        exit(4);
    };

    MazeGenerator maze(game_window);
    pair markers = maze.generate();
    pair player = {markers.first, FIRST_COLUMN};

    std::time_t start = std::time(nullptr);
    int score;

    keypad(game_window, true);

    wtimeout(game_window, 200);
    while (true) {
        if (player.first == markers.second && player.second == LAST_COLUMN) {
            update_ranking(current_player, score);
            break;
        }

        score = timer(game_window, start);

        int input = get_input(game_window);
        if (input != ERR && input != 'p')
            update_window(game_window, input, player);
        else if (input == 'p' && pause_menu() == true)
            break;
        else
            continue;
    }

    keypad(game_window, false);
    wgetch(game_window);
    wclear(game_window);
    wrefresh(game_window);
    delwin(game_window);
}