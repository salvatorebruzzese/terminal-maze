#ifndef MENU_H
#define MENU_H

#include <string>
#include "curses.h"

// Wrapper function that contains menu logic.
void menu(std::string current_player);

/**
 * @brief Function to select one of the options on the menu.
 * 
 * @param current_selection     The index of the current selected
 *                              option in the anchors[] array.
 * @param menu_window           Pointer to the menu window.
 * @return                      Index of the current selected option in 
 *                              the anchors[] array in visualize_menu().
 */
int menu_selection(int current_selection, WINDOW * menu_window);

/**
 * @brief Function to visualize the menu on the terminal.
 * 
 * @param current_selection     The index of the current selected
 *                              option in the anchors[] array.
 * @param menu_window           Pointer to the menu window.
 */
void visualize_menu(int current_selection, WINDOW * menu_window);

#endif  // MENU_H