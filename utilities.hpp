#include <iostream>
#include "curses.h"

const int MENU_HEIGHT = 15;
const int MENU_WIDTH = 30;
const int POPUP_HEIGHT = 5;
const int POPUP_WIDTH = 20;
const int MAX_USERNAME_LENGTH = 14;

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