#include <iostream>
#include "curses.h"

const int MENU_HEIGHT = 30;
const int MENU_WIDTH = 60 * 16/9;

/**
 * Function to call at the start of the main.
 */
void init();

/**
 * Creates a new curses window, boxes it and refreshes the screen.
 *
 * @param height    Number of rows for the window.
 * @param width     Number of columns for the window.
 * @return          Pointer to the new WINDOW, or nullptr on failure.
 */
WINDOW * new_boxed_window(int height, int width);