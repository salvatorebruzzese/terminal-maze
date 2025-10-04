#ifndef RANKING_H
#define RANKING_H

#include <string>
#include "curses.h"
#include "json.hpp"

// Creates a window that shows the data in data.json.
void show_ranking();

// Creates a pop-up window that shows the error string.
void show_error(const std::string & error);

// Prints the ten players with fastest times.
void print_top_ten(WINDOW * ranking_window, const nlohmann::json & object);

// Updates the data.json file to add a new clear time.
void update_ranking(const std::string & current_player, int time);

#endif // RANKING_H