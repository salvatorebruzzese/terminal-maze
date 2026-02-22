#ifndef UTILITIES_H
#define UTILITIES_H

#include <filesystem>
#include "curses.h"

constexpr int POPUP_HEIGHT          = 7;    // Height of popup window.
constexpr int POPUP_WIDTH           = 20;   // Width of popup window.
constexpr int GAME_HEIGHT           = 20;   // Height of popup window.
constexpr int GAME_WIDTH            = 60;   // Width of popup window.
constexpr int MAX_USERNAME_LENGTH   = 14;   // Maximum permitted username length.

// Returns the starting x-coordinate to center a string.
int calculate_starting_x(int width, const char * str);

// Function to initialize curses.
void init_curses();

/**
 * @brief Creates a new curses window of given size, draws the border, and refresh.
 *
 * @return WINDOW * on success, or nullptr on failure.
 */
WINDOW * new_boxed_window(int height, int width);

// Get the absolute path of the data.json file.
std::filesystem::path get_data_path();

#endif // UTILITIES_H