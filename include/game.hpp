#ifndef GAME_H
#define GAME_H

#include <string>
#include "curses.h"

using string = std::string;

/**
 * The game cycle function.
 * @param the name of the current player.
 */
void game(const string & current_player);

#endif // GAME_H