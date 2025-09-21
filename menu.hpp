#include <iostream>
#include <string>
#include "curses.h"
using std::string;

/**
 *  Wrapper function that contains menu logic.
 */
void menu();

/**
 * Function to select one of the options on the menu.
 * 
 * @param current_selection     The current selected option on the menu.
 * @param menu_window           Pointer to the menu window.
 * @return                      Index of the current selected option in 
 *                              the anchors[] array in visualize_menu().
 */
int menu_selection(int current_selection, WINDOW * menu_window);

/**
 * Function to visualize the menu on the terminal.
 * 
 * @param current_selection     The current selected option on the menu.
 * @param menu_window           Pointer to the menu window.
 */
void visualize_menu(int current_selection, WINDOW * menu_window);