#include <iostream>
#include <string>
using std::string;
#include "curses.h"

constexpr int POPUP_HEIGHT = 5;
constexpr int POPUP_WIDTH = 20;
constexpr int MAX_USERNAME_LENGTH = 14;

// Function to call at the start of main.
void init();

/**
 * Creates a new curses window of given size, draws the border, and refresh.
 *
 * @return WINDOW * on success, or nullptr on failure.
 */
WINDOW * new_boxed_window(int height, int width);