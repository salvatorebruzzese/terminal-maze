#include <iostream>
#include <string>
#include "curses.h"
using std::string;

void menu();

int menu_selection(int current_selection, WINDOW * menu_window);

void visualize_menu(int current_selection, WINDOW * menu_window);