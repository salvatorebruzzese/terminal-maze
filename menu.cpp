#include "menu.hpp"
#include "utilities.hpp"

void menu() {

    int current_selection = 0;
    bool exit = false;
    WINDOW * menu_window = new_boxed_window(MENU_HEIGHT, MENU_WIDTH);

    if (menu_window == nullptr) return;
    
    while (!exit) {
        current_selection = menu_selection(current_selection);

        visualize_menu(current_selection, menu_window);

        switch (current_selection)
        {
        case 0:
            
            break;
        
        case 1:
        
            break;

        case 2:
            exit = true;
            break;
        }
    }
}

int menu_selection(int current_selection) {
    chtype new_selection = getch();

    switch (new_selection)
    {
    case KEY_UP:
        if (current_selection <= 0)
            current_selection = 2;
        else --current_selection; 
        break;
    case KEY_DOWN:
        if (current_selection >= 2)
            current_selection = 0;
        else ++current_selection; 
        break;
    case KEY_ENTER:
        return current_selection;
        break;
    }

    return current_selection;
}

void visualize_menu(int current_selection, WINDOW * menu_window) {

    string anchors[3] = {"New maze", "Rankings", "Exit"};

    int y_position = MENU_HEIGHT/5;
    int x_position = MENU_WIDTH/2;

    for (int i = 1; i < 4; i++) {
        if (current_selection == i-1)
            wattr_on(menu_window, A_REVERSE, nullptr);

        mvprintw(y_position * i, x_position - (int) anchors[i-1].length(), "%s", anchors[i-1]);
        
        wattr_off(menu_window, A_REVERSE, nullptr);
    }

    wrefresh(menu_window);
}