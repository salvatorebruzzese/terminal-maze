#include "menu.hpp"
#include "utilities.hpp"

void menu() {

    int current_selection = 0;
    WINDOW * menu_window = new_boxed_window(MENU_HEIGHT, MENU_WIDTH);

    if (menu_window == nullptr) return;

    keypad(menu_window, true);

    while (true) {
        current_selection = menu_selection(current_selection, menu_window);
        switch (current_selection)
        {
        case 2:
            return;
            break;
        }
    }
    
}

int menu_selection(int current_selection, WINDOW * menu_window) {
    
    while (true)
    {
        visualize_menu(current_selection, menu_window);
        chtype new_selection = wgetch(menu_window);

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
        // The implementation of KEY_ENTER is unreliable in PDCurses 3.9
        case 10:
            return current_selection;
        }
    }
}

void visualize_menu(int current_selection, WINDOW * menu_window) {

    string anchors[3] = {"New maze", "Rankings", "Exit"};

    int y_position = MENU_HEIGHT/5;
    int x_position = MENU_WIDTH/2;

    for (int i = 1; i < 4; i++) {
        if (current_selection == i-1)
            wattr_on(menu_window, A_REVERSE, nullptr);

        wmove(menu_window, y_position * i + 1, x_position - (int) anchors[i-1].length()/2);
        wprintw(menu_window, "%s", anchors[i-1].c_str());
        
        wattr_off(menu_window, A_REVERSE, nullptr);
    }

    wrefresh(menu_window);
}